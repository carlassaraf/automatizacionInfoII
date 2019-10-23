/*  Libreria de Timer1 que cumple el rol de Real Time Clock. Tiene funciones relacionadas con la configuracion del RTC, variables
    pertinentes a su uso, rutina de atencion de interrupcion por desborde (cada segundo) y llamadas a funciones de otros perifericos
    que estan controlados periodicamente por este modulo. El RTC se configura por comunicacion serial con la palabra "rtcconfig" */

#include "rtc.h"

/*  Variables pertinetes al RTC  */

typedef struct {
    uint8 sec;
    uint8 min;
    uint8 hour;
} RTC;

RTC rtc;
uint8 secs=0;
extern char *wordRx;

/*  RTC_Init  :  Inicializacion del Timer1 para funcionar como RTC  */

void RTC_Init(void) {
    
    TMR1H=0x80;                 //Precargo el Timer seteando el Msb para que los overflow sean cada 1 seg
    RTCOverflowIntEnable();     //Habilito la interrupcion por overflow
    T1CON=0x8E;                 // 16 bit mode ; Prescaler 1:1 ; Asynchronized ; External clock from T1OSI and T1OSO : 32.768KHz ; Timer not running
}

/*  RTC_WaitingConfiguration  :  Rutina de espera para setear la hora  */

void RTC_WaitingConfiguration(void) {
            
    if( EUSARTReceiveDone() ) {         //Si se recibio algun dato por puerto serie
        EUSART_CheckWord();             //reviso si es un pedido de configuracion de RTC
        EUSARTClearFlag();
    }
    
    if( estado.ConfigRTCRequest && !estado.WaitingForTime ) {   //Si ya llego el pedido de configuracion
        EUSART_ConfigRTCRequest();
    }
    else {
       wordRx[0]='\0';      //Elimino cualquier basura que quede en el buffer de entrada
    }
}

/*  RTC_SetTime  :  Confugura la hora del RTC y lo habilita  */

void RTC_SetTime(char hour, char min, char secs) {
    
    rtc.hour=hour;
    rtc.min=min;
    rtc.sec=secs;
    estado.RealTimeSet=true;
    estado.ConfigRTCRequest=false;
    estado.WaitingForTime=false;
    T1CONbits.TMR1ON=true;         //Enciendo el Timer para que empiece a contar    
}

/*  RTC_ISR  :  Atencion de interrupcion que se produce cada segundo  */

void RTC_ISR(void) {
    
    TMR1H=0x80;                 //Precargo el Timer seteando el Msb para que los overflow sean cada 1 seg
    rtc.sec++;
    estado.RTCRefresh=true;
    RTCClearFlag();
}

/*  RTC_Refresh  :  Actualizo la hora y llamo a otras funciones periodicamente  */

void RTC_Refresh(void) {
    
    if( estado.RTCRefresh ) {
        secs++;
    
        if(secs==5) {                           //Si ya pasaron 5 segundos
            ADC_RefreshVal();                   //Vuelvo a hacer las lecturas analogicas
            estado.ConfigRTCRequest=0;          //Borro, si la hubo, la orden de configurar el RTC
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
}