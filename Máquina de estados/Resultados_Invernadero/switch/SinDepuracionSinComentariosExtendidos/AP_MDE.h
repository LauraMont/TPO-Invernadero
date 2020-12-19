/**
*	\file       AP_MDE.h
*	\brief      Prototipos, defines, etc. de las diferentes la M de E
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/

#ifndef INC_AP_MDEE_H_
#define INC_AP_MDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/

/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
extern int F_NuevaPlanta ;
extern int F_LeerDatos ;
extern int F_DatosListos ;
extern int ControlRiego ;
extern int ControlHumedad ;
extern int AmbienteMedido ;
extern int AmbienteMax ;
extern int AmbienteMin ;
extern int HumedadMedida ;
extern int HumedadMin ;
extern int Control ;
extern int TempMedida ;
extern int TempMax ;
extern int TempMin ;
extern int TempBajaMin ;
extern int TempBajaMax ;
extern int TempAltaMin ;
extern int TempAltaMax ;
extern int Dato_rx ;
extern int F_RecibiDatos ;
extern int DataValid ;

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
void MaquinaDeEstados ( void );

#endif /* INC_AP_MDEE_H_ */
