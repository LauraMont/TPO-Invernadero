/*******************************************************************************************************************************//**
 *
 * @file		DR_GPIO.c
 * @brief		Funciones de GPIO
 * @date		09-09-20
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_GPIO.h"

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

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
    \fn     void SetPINSEL (uint8_t port , uint8_t bit , uint8_t modo )
    \brief  Seleccion de funcionalidad del pin del puerto
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t modo: modo de funcionamiento
    \return void
*/
void SetPINSEL (uint8_t port , uint8_t bit , uint8_t modo )
{
    __RW uint32_t * PINSEL = (__RW uint32_t *) 0x4002C000UL;
    uint32_t mascara ;

    // Limpiar poner 00 en el lugar a escribir
    mascara = (uint32_t) ~(3 << (( bit % 16) * 2));
    PINSEL[ port * 2 + bit / 16 ] = PINSEL[ port * 2 + bit / 16 ] & mascara;
    mascara = (uint32_t) ( modo << (( bit % 16) * 2));
    PINSEL[ port * 2 + bit / 16 ] = PINSEL[ port * 2 + bit / 16 ] | mascara;
}

/**
    \fn     SetDIR (uint8_t port , uint8_t bit , uint8_t dir )
    \brief  Seleccion de Entrada o Salida de la GPIO
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t dir: seleccion entre Entrada o Salida
    \return void
*/
void SetDIR (uint8_t port , uint8_t bit , uint8_t dir )
{
    __RW uint32_t * FIODIR = (__RW uint32_t *) 0x2009C000UL;

    if ( dir )
        FIODIR[ port * 8 ] = FIODIR[ port * 8 ] | ( 1 << bit);
    else
        FIODIR[ port * 8 ] = FIODIR[ port * 8 ] & ~( 1 << bit);
}

/**
    \fn     void SetPIN ( uint8_t port , uint8_t bit , uint8_t estado )
    \brief  Accion de escritura en un pin de un puerto
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t estado: accion a realizar
    \return void
*/
void SetPIN ( uint8_t port , uint8_t bit , uint8_t estado )
{
    __RW uint32_t * FIOSET = (__RW uint32_t *) 0x2009C018UL;
    __RW uint32_t * FIOCLEAR = (__RW uint32_t *) 0x2009C01CUL;

    if ( estado )
        FIOSET[ port * 8 ] = FIOSET[ port * 8 ] | ( 1 << bit ) ;
    else
        FIOCLEAR[ port * 8 ] = FIOCLEAR[ port * 8 ] | ( 1 << bit ) ;
}

/**
    \fn     uint8_t GetPIN ( uint8_t port , uint8_t bit , uint8_t act )
    \brief  lectura de un pin de un puerto
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t act: actividad
    \return valor de la entrada normalizada
*/
uint8_t GetPIN ( uint8_t port , uint8_t bit , uint8_t act )
{
    __RW uint32_t * FIOPIN = (__RW uint32_t *) 0x2009C014UL;
    uint8_t pin;
    pin = ( FIOPIN[ port * 8 ] >> bit ) & 1 ;

    pin = ( act == ALTO ) ? pin : !pin;

    return pin;
}

/**
    \fn     void SetPINMODE (uint8_t port , uint8_t bit , uint8_t modo )
    \brief  Modo de trabajo de una GPIO cuando fue configurada como entrada
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t modo: modo de trabajo
    \return void
*/
void SetPINMODE (uint8_t port , uint8_t bit , uint8_t modo )
{
	__RW uint32_t * PINMODE = (__RW uint32_t *) 0x4002C040UL;
    uint32_t mascara ;

    // Limpiar poner 00 en el lugar a escribir
    mascara = (uint32_t) ~(3 << (( bit % 16) * 2));
    PINMODE[ port * 2 + bit / 16 ] = PINMODE[ port * 2 + bit / 16 ] & mascara;
    mascara = (uint32_t) ( modo << (( bit % 16) * 2));
    PINMODE[ port * 2 + bit / 16 ] = PINMODE[ port * 2 + bit / 16 ] | mascara;
}

/**
    \fn     void SetPINMODE_OD ( uint8_t port , uint8_t bit , uint8_t oc )
    \brief  Modo de trabago de una GPIO cuando fue configurada como salida
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \param  [in] uint8_t oc: modo de trabajo
    \return void
*/
void SetPINMODE_OD ( uint8_t port , uint8_t bit , uint8_t oc )
{
    __RW uint32_t * PINMODE_OD = (__RW uint32_t *) 0x4002C068UL;

    if ( oc )
        PINMODE_OD[ port ] = PINMODE_OD[ port ] | ( 1 << bit ) ;
    else
        PINMODE_OD[ port ] = PINMODE_OD[ port ] & ~( 1 << bit ) ;
}

/**
    \fn     void SetTOGGLE ( uint8_t port , uint8_t bit  )
    \brief  Invierte el valor que tiene el pin cuando fue configurado como salida
    \author Ing. Marcelo Trujillo
    \date   09-09-20
    \param  [in] uint8_t port: numero de puerto
    \param  [in] uint8_t bit: numero de bit del puerto
    \return void
*/
void SetTOGGLE ( uint8_t port , uint8_t bit  )
{
    uint8_t in;

    in = GetPIN( port , bit , ALTO );

    SetPIN( port , bit , !in);

    return;
}
