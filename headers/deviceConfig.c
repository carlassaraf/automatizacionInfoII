/*  Libreria general de configuracion del uC. Llama a las configuraciones de todos los perifericos y a las distintas
    maquinas de estado que tiene que atender.  */

#include "deviceConfig.h"

/*  Oscillator_Init  :  Inicializacion del clock  */

void Oscillator_Init(void) {
    
    OSCCONbits.SCS=0;               //Fuente de clock es el bloque primario definido por CONFIG1H OSC (HS - High Speed Crystal Resonator)
}

/*  System_Init  :  Llama a las configuraciones de todos los perifericos  */

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

/*  CheckLights : Rutina que revisa las variables de control de la maquina de estado que atiende las luces  */

uint8 CheckLights(void) {
    
    if( estado.MotionDetected && !estado.LightsOn ) {
        return _TURN_ON_LIGHTS;
    }
    else if( !estado.MotionDetected && estado.LightsOn ) {
        return _TURN_OFF_LIGHTS;
    }
}

/*  CheckWindow  :  Rutina que revisa las variables de control de la maquina de estado que atiende las ventanas  */

uint8 CheckWindow(void) {
    
    if( estado.TimeToOpenWindow && !estado.WindowOpened ) {
        return _OPEN_WINDOW;
    }
    else if( !estado.TimeToOpenWindow && estado.WindowOpened ) {
        return _CLOSE_WINDOW;
    }
}

/*  CheckHeatSys  :  Rutina que revisa las variables de control de la maquina de estado que atiende el sistema de frio/calor  */

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

/*  Lights  :  Maquina de estado de las luces  */

void Lights(void) {
    
    LightsProcess[CheckLights()];
}

/*  Window  :  Maquina de estado de las ventanas  */

void Window(void) {
    
    WindowProcess[CheckWindow()];
}

/*  HeatSys  :  Maquina de estado del sistema de frio/calor  */

void HeatSys(void) {
    
    HeatSysProcess[CheckHeatSys()];
}