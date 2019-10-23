/*  Libreria de puertos digitales.  */

#include "pinManager.h"
#include "interruptManager.h"

/*  pinManager_Init  :  Inicializacion de los puertos digitales  */

void pinManager_Init(void) {

    /*Registros de direccionamiento de pin*/
    TRISA=0x03;         //RA0 y RA1 son entradas
    TRISB=0xFF;         //Todos los pines de RB son entradas
    TRISD=0x00;         //Todos los pines de RD son salidas
    
    /*Registros de latch*/
    LATD=0x00;          //Dejo todas las salidas del puerto C en estado bajo
}

/*  TurnOnLights  :  Rutina de encendido de luces  */

void TurnOnLights(void) {
    
    LIGHTS_ON();
    estado.LightsOn=true;
}

/*  TurnOffLights  :  Rutina de apagado de luces  */

void TurnOffLights(void) {
    
    LIGHTS_OFF();
    estado.LightsOn=false;
}

/*  TurnOnHeat  :  Rutina de encendido de calefaccion  */

void TurnOnHeat(void) {
    
    COLD_OFF();
    HEAT_ON();
    estado.Heating=true;
    estado.Cooling=false;
}

/*  TurnOnCold  :  Rutina de encendido de refrigeracion  */

void TurnOnCold(void) {
    
    HEAT_OFF();
    COLD_ON();
    estado.Heating=false;
    estado.Cooling=true;
}

/*  TurnOff  :  Rutina de apagado del sistema frio/calor  */

void TurnOff(void) {
    
    HEAT_OFF();
    COLD_OFF();
    estado.Heating=false;
    estado.Cooling=false;
}

/*  CloseWindow  :  Rutina de cierre de ventana  */

void CloseWindow(void) {
    
    WINDOW_UP=false;
    WINDOW_DOWN=true;
    estado.WindowOpened=false;
}

/*  OpenWindow  :  Rutina de apertura de ventana  */

void OpenWindow(void) {
    
    WINDOW_DOWN=false;
    WINDOW_DOWN=true;
    estado.WindowOpened=true;
}

/*  INT0_ISR  :  Rutina de atencion de interrupcion externa por sensor de movimiento  */

void INT0_ISR(void) {
    
    if( !estado.MotionDetected )   {            //Si no hubo movimiento y ahora se detecto
        estado.MotionDetected=true;             //Actualizo el estado
        FallingEdgeInt();                       //Y cambio la interrupcion a flanco descendente para detectar cuando deje de haber movimiento
    }
    else {
        estado.MotionDetected=false;            
        RisingEdgeInt();
    }                           
    MotionDetectedClearFlag();                  //Hago un clear en el bit de interrupcion
}