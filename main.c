/*
 * File:   main.c
 * Author: carlassaraf
 *
 * Created on September 16, 2019, 9:05 PM
 */

#include <xc.h>
#include "headers/deviceConfig.h"

void main(void) {
    
    System_Init();      //Inicializacion de registros
    
    void (*func_ptr[])(void) = { RTC_Refresh, TurnOnLights, TurnOffLights, OpenWindow, CloseWindow, TurnOnHeat, TurnOnCold, TurnOff };
    
    while(!estado.RealTimeSet) {    //No continuo con el programa hasta que se haya configurado el RTC
        RTC_WaitingConfiguration();
    }
    
    while(1) {
        (*func_ptr[CheckCondition()]);
    }
    return;
}
