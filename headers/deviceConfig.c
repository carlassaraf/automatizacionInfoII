#include "deviceConfig.h"

void Oscillator_Init(void) {
    
    OSCCONbits.SCS=0;               //Fuente de clock es el bloque primario definido por CONFIG1H OSC (HS - High Speed Crystal Resonator)
}

void System_Init(void) {

    Oscillator_Init();              //Inicializo el clock del sistema
    pinManager_Init();              //Inicializo los GPIO
    ADC_Init();                     //Inicializo el modulo ADC
    RTC_Init();                     //Inicializo el RTC
    EUSART_Init();                  //Inicializo la comunicacion serial
    Interrupt_Init();               //Inicializo las interrupciones
    while(!estado.RealTimeSet)     //No continuo con el programa hasta que se haya configurado el RTC
        RTC_WaitingConfiguration();    
}

uint8 CheckLights(void) {
    
    if( estado.MotionDetected && !estado.LightsOn ) {
        return _TURN_ON_LIGHTS;
    }
    else if( !estado.MotionDetected && estado.LightsOn ) {
        return _TURN_OFF_LIGHTS;
    }
}
uint8 CheckWindow(void) {
    
    if( estado.TimeToOpenWindow && !estado.WindowOpened ) {
        return _OPEN_WINDOW;
    }
    else if( !estado.TimeToOpenWindow && estado.WindowOpened ) {
        return _CLOSE_WINDOW;
    }
}

uint8 CheckHeatSys(void) {
    
    if( estado.TurnOnHeat && !estado.TurnOnCold && !estado.Heating ) {
        return _TURN_HEAT_ON;
    }
    if( estado.TurnOnCold && !estado.TurnOnHeat && !estado.Cooling ) {
        return _TURN_COLD_ON;
    }
    if( !estado.TurnOnCold && !estado.TurnOnHeat && ( estado.Cooling || estado.Heating ) ) {
        return _TURN_OFF;
    }
}

void Lights(void) {
    
    LightsProcess[CheckLights()];
}

void Window(void) {
    
    WindowProcess[CheckWindow()];
}

void HeatSys(void) {
    
    HeatSysProcess[CheckHeatSys()];
}