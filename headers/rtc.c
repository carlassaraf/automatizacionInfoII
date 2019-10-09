#include "rtc.h"

typedef struct {
    uint8 sec;
    uint8 min;
    uint8 hour;
} RTC;

RTC rtc;
uint8 secs=0;
extern char *wordRx;

void RTC_Init(void) {
    
    TMR1H=0x80;                 //Precargo el Timer seteando el Msb para que los overflow sean cada 1 seg
    RTCOverflowIntEnable();     //Habilito la interrupcion por overflow
    T1CON=0x8E;                 // 16 bit mode ; Prescaler 1:1 ; Asynchronized ; External clock from T1OSI and T1OSO : 32.768KHz ; Timer not running
}

void RTC_WaitingConfiguration(void) {
            
    if( EUSARTReceiveDone() ) {
        EUSART_CheckWord();
        EUSARTClearFlag();
    }
    
    if( estado.ConfigRTCRequest && !estado.WaitingForTime ) {   
        EUSART_ConfigRTCRequest();
    }
    else {
       wordRx[0]='\0';
    }
}

void RTC_SetTime(char hour, char min, char secs) {
    
    rtc.hour=hour;
    rtc.min=min;
    rtc.sec=secs;
    estado.RealTimeSet=true;
    estado.ConfigRTCRequest=false;
    estado.WaitingForTime=false;
    T1CONbits.TMR1ON=true;         //Enciendo el Timer para que empiece a contar    
}

void RTC_ISR(void) {
    
    TMR1H=0x80;                 //Precargo el Timer seteando el Msb para que los overflow sean cada 1 seg
    rtc.sec++;
    estado.RTCRefresh=true;
    RTCClearFlag();
}

void RTC_Refresh(void) {
    
    secs++;
    
    if(secs==5) {
         ADC_RefreshVal();                  //Vuelvo a hacer las lecturas analogicas
         estado.ConfigRTCRequest=0;         //Borro, si la hubo, la orden de configurar el RTC
         secs=0;
    }
    if(rtc.sec>59) {
        rtc.sec=0;
        rtc.min++;
    }
    if(rtc.min>59) {
        rtc.min=0;
        rtc.hour++;
    }
    if(rtc.hour==OpenWindowTime) {
        estado.TimeToOpenWindow=true;
    }
    if(rtc.hour==CloseWindowTime) {
        estado.TimeToOpenWindow=false;
    }
    if(rtc.hour>23) 
        rtc.hour=false;
    
    estado.RTCRefresh=false;            //Limpio el bit de estado del refresh del RTC
}