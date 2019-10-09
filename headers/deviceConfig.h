#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include "pinManager.h"
#include "adc.h"
#include "rtc.h"
#include "eusart.h"
#include "interruptManager.h"

#define _XTAL_FREQ      20000000    //Cristal de 20 MHz
#define true            1
#define false           0

#define _REFRESH_RTC            0
#define _TURN_ON_LIGHTS         1
#define _TURN_OFF_LIGHTS        2
#define _OPEN_WINDOW            3
#define _CLOSE_WINDOW           4
#define _TURN_HEAT_ON           5
#define _TURN_COLD_ON           6
#define _TURN_OFF               7

typedef unsigned char uint8;

typedef struct {                                //Estructura para determinar estados del sistema
    uint16 ConfigRTCRequest         : 1;        //Indicador de que se quiere configurar el RTC
    uint16 RealTimeSet              : 1;        //Indicador de que el RTC fue configurado
    uint16 RTCRefresh               : 1;        //Indicador de que el RTC cambio
    uint16 WaitingForTime           : 1;        //Indicador de que se esta esperando la hora
    uint16 TimeToOpenWindow         : 1;        //Indicador de que es el horario programado para abrir la ventana
    uint16 MotionDetected           : 1;        //Indicador de que alguien entro
    uint16 LightsOn                 : 1;        //Indicador de luces
    uint16 TurnOnHeat               : 1;        //Indicador de encendido de calefaccion
    uint16 TurnOnCold               : 1;        //Indicador de encendido de enfriamiento
    uint16 Heating                  : 1;        //Indicador de que se esta calentando la habitacion
    uint16 Cooling                  : 1;        //Indicador de que se esta enfriando la habitacion
    uint16 WindowOpened             : 1;        //Indicador de que la ventana esta abierta
} flag;

flag estado;

void Oscillator_Init(void);
void System_Init(void);
uint8 CheckCondition(void);

#endif