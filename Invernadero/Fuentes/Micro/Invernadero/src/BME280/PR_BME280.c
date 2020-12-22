/*******************************************************************************************************************************//**
 *
 * @file		PR_BME280.c
 * @brief		Descripcion del modulo
 * @date		23 nov. 2020
 * @author		Taurozzi, Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_BME280.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
extern volatile uint8_t I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];

extern volatile uint32_t I2CReadLength[I2C_PORT_NUM];
extern volatile uint32_t I2CWriteLength[I2C_PORT_NUM];

extern volatile uint32_t Temp;
extern volatile uint32_t Pres;
extern volatile uint32_t Hum;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint8_t calib_params_TP[CANT_CALIB_PARAMS_TP];
volatile uint8_t calib_params_H[CANT_CALIB_PARAMS_H];
static uint8_t meas_data[CANT_DATA_REGS];

static struct bme280_dev dev;
volatile struct bme280_uncomp_data uncomp_data;

static uint32_t hum;
static uint32_t pres;
static int32_t temp;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/*
 * \fn  	void BME280_init(uint32_t portNum)
 * \@brief  Guarda en MasterBuffer las direcciones de los registros
 * 		    que se van a configurar y la configuracion de cada uno. Luego lee
 * 		    los parametros de calibracion y los deja configurados.
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \return	No hay retorno
 */

void BME280_init(uint32_t portNum)
{
	I2CWriteLength[portNum] = 8; //Cantidad de veces a escribir

	I2CReadLength[portNum] = CANT_CALIB_PARAMS_TP; //Cantidad de veces que voy a leer

	I2CMasterBuffer[portNum][0] = BME280_WR;//Dirección en modo de escritura

	//Configuración para las mediciones
	I2CMasterBuffer[portNum][1] = CTRL_MEAS;//Dirección del registro de configuracion de mediciones
	I2CMasterBuffer[portNum][2] = MIN_OSRS_T | MIN_OSRS_P | SLEEP_MODE; //Configuro sobremuestreo normal y modo normal

	I2CMasterBuffer[portNum][3] = CTRL_HUM;	 //Dirección del registro a escribir
	I2CMasterBuffer[portNum][4] = MIN_OSRS_H; //Configuro sobremuestreo normal

	I2CMasterBuffer[portNum][5] = CONFIG;	 //Dirección del registro de configuraciones
	I2CMasterBuffer[portNum][6] = T1MS | FILTER_OFF | SPI3E_OFF; //Configuración del registro

	//Lectura de los valores de calibracion de temperatura y presion
	I2CMasterBuffer[portNum][7] = 0x88; //Registro del que comenzar a leer
	I2CMasterBuffer[portNum][8] = BME280_RD;  //Dirección en modo de lectura

	I2CEngine(portNum); //Va a escribir y leer tantas veces como se configuro en las líneas anteriores

	for(int i=0; i < CANT_CALIB_PARAMS_TP; i++) //Guardo los parámetros de calibración
		{calib_params_TP[i] = I2CSlaveBuffer[1][i];}

	parse_temp_press_calib_data();

	//Lectura de los valores de calibracion de humedad
	I2CWriteLength[portNum] = 2; //Voy a enviar 6 datos de escritura

	I2CReadLength[portNum] = CANT_CALIB_PARAMS_H;

	I2CMasterBuffer[portNum][0] = BME280_WR;	 //Dirección en modo de escritura

	I2CMasterBuffer[portNum][1] = 0xE1; //Registro del que comenzar a leer

	I2CMasterBuffer[portNum][2] = BME280_RD;  //Dirección en modo de lectura

	I2CEngine(1); //Va a escribir y leer tantas veces como se configuro en las líneas anteriores

	for(int i=0; i < CANT_CALIB_PARAMS_H; i++) //Guardo los parámetros de calibración
		{calib_params_H[i] = I2CSlaveBuffer[1][i];}

	parse_humidity_calib_data();
}
/*
 * \fn     void parse_temp_press_calib_data(void)
 * \@brief This API is used to read the calibration parameters used
 *		   for calculating the compensated data. * \author Taurozzi, Nicolás
 * \date   24/11/20
 * \param  [in] uint32_t portNum: Numero de canal del I2C del micro
 * \return No hay retorno
 */
void parse_temp_press_calib_data(void)
{
	struct bme280_calib_data *calib_data = &dev.calib_data;

	//Concateno la parte alta con la parte baja y la guardo en el digito que corresponde
    calib_data->dig_t1 = BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_T1_MSB_POS], calib_params_TP[BME280_DIG_T1_LSB_POS]);

    calib_data->dig_t2 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_T2_MSB_POS], calib_params_TP[BME280_DIG_T2_LSB_POS]);

    calib_data->dig_t3 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_T3_MSB_POS], calib_params_TP[BME280_DIG_T3_LSB_POS]);

    calib_data->dig_p1 = BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P1_MSB_POS], calib_params_TP[BME280_DIG_P1_LSB_POS]);

    calib_data->dig_p2 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P2_MSB_POS], calib_params_TP[BME280_DIG_P2_LSB_POS]);

    calib_data->dig_p3 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P3_MSB_POS], calib_params_TP[BME280_DIG_P3_LSB_POS]);

    calib_data->dig_p4 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P4_MSB_POS], calib_params_TP[BME280_DIG_P4_LSB_POS]);

    calib_data->dig_p5 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P5_MSB_POS], calib_params_TP[BME280_DIG_P5_LSB_POS]);

    calib_data->dig_p6 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P6_MSB_POS], calib_params_TP[BME280_DIG_P6_LSB_POS]);

    calib_data->dig_p7 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P7_MSB_POS], calib_params_TP[BME280_DIG_P7_LSB_POS]);

    calib_data->dig_p8 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P8_MSB_POS], calib_params_TP[BME280_DIG_P8_LSB_POS]);

    calib_data->dig_p9 = (int16_t)BME280_CONCAT_BYTES(calib_params_TP[BME280_DIG_P9_MSB_POS], calib_params_TP[BME280_DIG_P9_LSB_POS]);

    calib_data->dig_h1 = calib_params_TP[25];
}

/*
 * \fn      void parse_temp_press_calib_data(void)
 * \@brief  This internal API is used to parse the humidity calibration data
 *  		and store it in device structure.
 * \date    24/11/20
 * \return  No hay retorno
 */
void parse_humidity_calib_data(void)
{
    struct bme280_calib_data *calib_data = &dev.calib_data;
    int16_t dig_h4_lsb;
    int16_t dig_h4_msb;
    int16_t dig_h5_lsb;
    int16_t dig_h5_msb;

    calib_data->dig_h2 = (int16_t)BME280_CONCAT_BYTES(calib_params_H[1], calib_params_H[0]);
    calib_data->dig_h3 = calib_params_H[2];

    dig_h4_msb = (int16_t)(int8_t)calib_params_H[3] * 16;
    dig_h4_lsb = (int16_t)(calib_params_H[4] & 0x0F);
    calib_data->dig_h4 = dig_h4_msb | dig_h4_lsb;

    dig_h5_msb = (int16_t)(int8_t)calib_params_H[5] * 16;
    dig_h5_lsb = (int16_t)(calib_params_H[4] >> 4);
    calib_data->dig_h5 = dig_h5_msb | dig_h5_lsb;

    calib_data->dig_h6 = (int8_t)calib_params_H[6];
}

/*
 * \fn  	void BME280_get_meas_values(uint32_t portNum)
 * \@brief  Lee los 6 registros de datos, 3 son de presion,
 * 	 		3 son de temperatura y 2 son de humedad, luego
 * 	 		sepepara los valores y compensa las mediciones
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \return	No hay retorno
 */

void BME280_get_meas_values(uint32_t portNum)
{
	I2CWriteLength[portNum] = 4;

	I2CReadLength[portNum] = CANT_DATA_REGS;

	I2CMasterBuffer[portNum][0] = BME280_WR;	 //Dirección en modo de escritura

	I2CMasterBuffer[portNum][1] = CTRL_MEAS;//Dirección del registro de configuracion de mediciones

	I2CMasterBuffer[portNum][2] = MIN_OSRS_T | MIN_OSRS_P | FORCED_MODE; //Configuro sobremuestreo normal y modo forzado

	I2CMasterBuffer[portNum][3] = 0xF7; //Registro del que comenzar a leer

	I2CMasterBuffer[portNum][4] = BME280_RD;  //Dirección en modo de lectura

	I2CEngine(1);

	for(int i=0; i < CANT_DATA_REGS; i++) //Guardo los parámetros de las medidas
		{meas_data[i] = I2CSlaveBuffer[1][i];}

	bme280_get_uncomp_data(meas_data);

}

/*
 * \fn  	void bme280_get_uncomp_data(uint8_t * data)
 * \@brief  This API reads the temperature and pressure data registers.
 * 			It gives the raw temperature and pressure data . * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint8_t * data: vector donde estan guardados los valores medidos
 * \return	No hay retorno
 */
void bme280_get_uncomp_data(uint8_t * data)
{
    /* Variables to store the sensor data */
    uint32_t data_xlsb;
    uint32_t data_lsb;
    uint32_t data_msb;

    data_msb = (uint32_t)data[0] << 12;
    data_lsb = (uint32_t)data[1] << 4;
    data_xlsb = (uint32_t)data[2] >> 4;
    uncomp_data.pressure = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for temperature data */
    data_msb = (uint32_t)data[3] << 12;
    data_lsb = (uint32_t)data[4] << 4;
    data_xlsb = (uint32_t)data[5] >> 4;
    uncomp_data.temperature = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for humidity data */
    data_msb = (uint32_t)data[6] << 8;
    data_lsb = (uint32_t)data[7];
    uncomp_data.humidity = data_msb | data_lsb;
}

/*
 * \fn  	MeasureBME280
 * \@brief  Toma todas las mediciones del sensor
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \param 	[out] Temp: valor de la temperatura que pasa a la aplicacion
 * \param 	[out] Pres: valor de la presion que pasa a la aplicacion
 * \param 	[out] Hum:  valor de la humedad que pasa a la aplicacion
 * \return	No hay retorno
 */
void MeasureBME280(uint32_t portNum)
{
	BME280_get_meas_values(portNum);
	compensate_temp(&temp, uncomp_data.temperature);
	compensate_pres(&pres, uncomp_data.pressure);
	compensate_hum(&hum, uncomp_data.humidity);

	Temp = temp;
	Pres = pres;
	Hum = hum;
}

/*
 * \fn  	int32_t get_temp(uint32_t portNum)
 * \@brief  Toma la medicion de la temperatura
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \return	int32_t temp: valor de temperatura medido
 */
int32_t get_temp(uint32_t portNum)
{
	BME280_get_meas_values(portNum);
	compensate_temp(&temp, uncomp_data.temperature);
	return temp; //Elimino los dos ultimos digitos asi queda sin comas
}


/*
 * \fn  	int32_t get_pres(uint32_t portNum)
 * \@brief  Toma la medicion de la presion
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \return	int32_t pres: valor de presion medido
 */
uint32_t get_pres(uint32_t portNum)
{
	BME280_get_meas_values(portNum);
	compensate_pres(&pres, uncomp_data.pressure);
	return pres/100; //Elimino los dos ultimos digitos asi queda sin comas
}

/*
 * \fn  	int32_t get_hum(uint32_t portNum)
 * \@brief  Toma la medicion de la humedad
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t portNum: Numero de canal del I2C del micro
 * \return	int32_t hum: valor de humedad medido
 */
uint32_t get_hum(uint32_t portNum)
{
	BME280_get_meas_values(portNum);
	compensate_hum(&hum, uncomp_data.humidity);
	return hum;	/* Write SLA(W), register configuration, SLA(R), and read one byte back. */
}

/*
 * \fn  	void compensate_temp(int32_t *comp_temp, int32_t uncomp_temp)
 * \@brief  This API is used to get the compensated temperature from
 * 			uncompensated temperature. This API uses 32 bit integers.
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] int32_t *comp_temp: puntero a la variable donde guardar la compensacion
 * \param 	[in] int32_t uncomp_temp: valor sin compensar de la temperatura
 * \return	No hay retorno
 */
void compensate_temp(int32_t *comp_temp, int32_t uncomp_temp)
{
	double var1;
	double var2;
	double temperature_min = -40;
	double temperature_max = 85;

    var1 = uncomp_temp / 16384.0 - ((double) dev.calib_data.dig_t1) / 1024.0;
    var1 = var1 * ((double) dev.calib_data.dig_t2);
    var2 = (uncomp_temp / 131072.0 - ((double) dev.calib_data.dig_t1) / 8192.0);
    var2 = (var2 * var2) * ((int32_t) dev.calib_data.dig_t3);
    dev.calib_data.t_fine = (int32_t)(var1 + var2);
    *comp_temp = (var1 + var2) / 5120.0;

    if (*comp_temp < temperature_min)
    {
    	*comp_temp = temperature_min;
    }
    else if (*comp_temp > temperature_max)
    {
    	*comp_temp = temperature_max;
    }
}

/*
 * \fn  	void compensate_pres(uint32_t *comp_pres, uint32_t uncomp_pres)
 * \@brief  This API is used to get the compensated pressure from
 *			uncompensated pressure. This API uses 32 bit integers.
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t *comp_pres: puntero a la variable donde guardar la compensacion
 * \param 	[in] uint32_t uncomp_pres: valor sin compensar de la presion
 * \return	No hay retorno
 */
void compensate_pres(uint32_t *comp_pres, uint32_t uncomp_pres)
{
	double var1, var2, var3;
	double pressure_min = 30000;
	double pressure_max = 110000;

    var1 = ((double) dev.calib_data.t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double) dev.calib_data.dig_p6) / 32768.0;
    var2 = var2 + var1 * ((double) dev.calib_data.dig_p5) * 2.0;
    var2 = (var2 / 4.0) + (((double) dev.calib_data.dig_p4) * 65536.0);
    var3 = ((double) dev.calib_data.dig_p3) * var1 * var1 / 524288.0;
    var1 = (var3 + ((double) dev.calib_data.dig_p2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double) dev.calib_data.dig_p1);

    /* avoid exception caused by division by zero */
    if (var1 > (0.0))
    {
    	*comp_pres = 1048576.0 - uncomp_pres;
    	*comp_pres = (*comp_pres - (var2 / 4096.0)) * 6250.0 / var1;
        var1 = ((double) dev.calib_data.dig_p9) * *comp_pres * *comp_pres / 2147483648.0;
        var2 = *comp_pres * ((double) dev.calib_data.dig_p8) / 32768.0;
        *comp_pres = *comp_pres + (var1 + var2 + ((double) dev.calib_data.dig_p7)) / 16.0;

        if (*comp_pres < pressure_min)
        {
        	*comp_pres = pressure_min;
        }
        else if (*comp_pres > pressure_max)
        {
        	*comp_pres = pressure_max;
        }
    }
    else /* Invalid case */
    {
    	*comp_pres = pressure_min;
    }
}

/*
 * \fn  	void compensate_hum(uint32_t *comp_hum)
 * \@brief  This API is used to get the compensated humidity from
 *			uncompensated humidity. This API uses 32 bit integers.
 * \author  Taurozzi, Nicolás
 * \date 	24/11/20
 * \param 	[in] uint32_t *comp_hum: puntero a la variable donde guardar la compensacion
 * \param 	[in] uint32_t uncomp_hum: valor sin compensar de la humedad
 * \return	No hay retorno
 */
void compensate_hum(uint32_t *comp_hum,  uint32_t uncomp_hum)
{
    double humidity_min = 0.0;
    double humidity_max = 99.0; //Originalmente es 100.0 pero para el LCD es mejor 99
    double var1;
    double var2;
    double var3;
    double var4;
    double var5;
    double var6;

    var1 = ((double)dev.calib_data.t_fine) - 76800.0;
    var2 = (((double)dev.calib_data.dig_h4) * 64.0 + (((double)dev.calib_data.dig_h5) / 16384.0) * var1);
    var3 = uncomp_hum - var2;
    var4 = ((double)dev.calib_data.dig_h2) / 65536.0;
    var5 = (1.0 + (((double)dev.calib_data.dig_h3) / 67108864.0) * var1);
    var6 = 1.0 + (((double)dev.calib_data.dig_h6) / 67108864.0) * var1 * var5;
    var6 = var3 * var4 * (var5 * var6);
    *comp_hum = (var6) * (1.0 - ((double)dev.calib_data.dig_h1) * var6 / 524288.0);

    if (*comp_hum > humidity_max)
    {
    	*comp_hum = humidity_max;
    }
    else if (*comp_hum < humidity_min)
    {
    	*comp_hum = humidity_min;
    }
}
