#include "adc.h"
#include "interruptManager.h"
#include "pinManager.h"

void ADC_Init(void) {

    ADCON1=0x0D;                // VREF- es Vss ; VREF+ es Vdd ; RA0 y RA1 son analogicas
    ADCON2=0x88;                //Justificado a la derecha ; 2 TAD de precarga ; Clock es Fosc/2
    ADCON0|=1;                  //ADC encendido
}

void ADC_StartConvertion(unsigned char channel) {

    ADC_SetChannel(channel);    //Elijo el canal que voy a convertir
    ADC_Start();                //Seteo el bit GO del ADCON0
}

uint16 ADC_Read(unsigned char channel) {

    ADC_StartConvertion(channel);        //Inicio la conversion
    while(ADC_Busy());              //Espero a que la conversion termine
    return ADRESL+(ADRESH<<8);      //Devuelvo la parte alta dle resultado corrida en 8 y le sumo la parte baja
}

void ADC_RefreshVal(void) {
    
    enum sensors   { LM50 , SETPOINT };
    enum sensors sensor;
    
    for(sensor=LM50 ; sensor<=SETPOINT ; sensor++ ) {
        if(sensor==LM50)    tempVal=ADC_Read(sensor);
        else                setpointVal=ADC_Read(sensor);
    }
    ADC_ConvertToTemperature();
}

void ADC_ConvertToTemperature(void) {
    
    /* Conversiones necesarias para llegar al valor real de temperatura ambiente y setpoint */
    dT=tempVal-setpointVal;
    if( dT<dTMin ) {                        //Si la temperatura ambiente esta por debajo del setpoint
        estado.TurnOnHeat=1;
        estado.TurnOnCold=0;
    }
    else if( dT>dTMax ) {                   //Si la temperatura ambiente esta por arriba del setpoint
        estado.TurnOnHeat=0;
        estado.TurnOnCold=1;
    }
    else if( dT>dTMin && dT<dTMax ) {       //Si la temperatura ambiente se encuentra dentro de un margen aceptable
        estado.TurnOnHeat=0;
        estado.TurnOnCold=0;
    }
}
