#include "pinManager.h"
#include "interruptManager.h"

void pinManager_Init(void) {

    /*Registros de direccionamiento de pin*/
    TRISA=0x03;         //RA0 y RA1 son entradas
    TRISB=0xFF;         //Todos los pines de RB son entradas
    TRISD=0x00;         //Todos los pines de RD son salidas
    
    /*Registros de latch*/
    LATD=0x00;          //Dejo todas las salidas del puerto C en estado bajo
}

void TurnOnLights(void) {
    
    LIGHTS_ON();
    estado.LightsOn=true;
}

void TurnOffLights(void) {
    
    LIGHTS_OFF();
    estado.LightsOn=false;
}

void TurnOnHeat(void) {
    
    COLD_OFF();
    HEAT_ON();
    estado.Heating=true;
    estado.Cooling=false;
}

void TurnOnCold(void) {
    
    HEAT_OFF();
    COLD_ON();
    estado.Heating=false;
    estado.Cooling=true;
}

void TurnOff(void) {
    
    HEAT_OFF();
    COLD_OFF();
    estado.Heating=false;
    estado.Cooling=false;
}

void CloseWindow(void) {
    
    WINDOWUP=false;
    WINDOWDOWN=true;
    estado.WindowOpened=false;
}

void OpenWindow(void) {
    
    WINDOWDOWN=false;
    WINDOWDOWN=true;
    estado.WindowOpened=true;
}

void INT0_ISR(void) {
    
    if( !estado.MotionDetected )   {            //Si no hubo movimiento y ahora se detecto
        estado.MotionDetected=1;                //Actualizo el estado
        FallingEdgeInt();                       //Y cambio la interrupcion a flanco descendente para detectar cuando deje de haber movimiento
    }
    else {
        estado.MotionDetected=0;
        RisingEdgeInt();
    }                           
    MotionDetectedClearFlag();                  //Hago un clear en el bit de interrupcion
}