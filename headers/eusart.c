#include "eusart.h"
#include "deviceConfig.h"

void EUSART_Init(void) {
    
    TRISC|=0xC0;                    //Configuro pines RC6 y RC7 como entrada
    TXSTA=0x24;                     // 8 bit transmition ; Asynchronous mode ; Tx enable ; High speed
    RCSTA=0x90;                     // 8 bit reception ; Serial port enabled ; Receiver enabled 
    BAUDCON=0x00;                   // Tx, Rx and Clock not inverted
    SPBRG=129;                      //BAUD=9615
}

void EUSART_SendString(char *str) {
    
    while(*str) {
        EUSART_TxBuffer=*str;
        EUSART_Wait();
        str++;
    }
}

void EUSART_CheckWord(void) {
    
    static char i=0, *auxWord;
    if( estado.WaitingForTime ) {           //La orden de configurar el RTC ya se recibio
        while(*wordRx) {                    //Copio el valor del buffer en una variable auxiliar
            if(*wordRx!='/') {
                *auxWord=*wordRx;
                auxWord++;
                i++;
            }
            wordRx++;
        }
        if(i>7) {                           //Obtuve los ocho numeros que conforman la fecha sin los '/'
            long time;
            char hour, min, sec;
            time=strtol(auxWord,NULL,10);   //Convierto los caracteres a enteros
            hour=time/10000;
            min=time/100-hour*100;
            sec=time-hour*10000;
            sec-=min*100;
            RTC_SetTime(hour,min,sec);          //Obtengo las horas, minutos y segundos por separado y condiguro el RTC
        }
    }
    else {
        if(!strcmp(wordRx,"rtcconfig"))     estado.ConfigRTCRequest=1;          //Todavia no recibio la orden de configurar el RTC
        else                                estado.ConfigRTCRequest=0;
    }
}

void EUSART_ConfigRTCRequest(void) {
    
    EUSART_SendString("Indique la hora de la siguiente manera: (HH/MM/SS)\n");
    wordRx[0]='\0';                     //Borro lo que haya recibido
    estado.WaitingForTime=1;
}

void EUSART_RX_ISR(void) {
    
    *wordRx=EUSART_RxBuffer;
    wordRx++;
}
