/*  Libreria de EUSART para el uC. Contiene funciones de configuracion y comunicacion serial y algunas funciones relacionadas
    con el pedido de datos para configurar el RTC   */

#include "eusart.h"
#include "deviceConfig.h"
#include "interruptManager.h"

/*  EUSART_Init  :  Configura los registros de la comunicacion serial  */

void EUSART_Init(void) {
    
    TRISC|=0xC0;                    //Configuro pines RC6 y RC7 como entrada
    TXSTA=0x24;                     // 8 bit transmition ; Asynchronous mode ; Tx enable ; High speed
    RCSTA=0x90;                     // 8 bit reception ; Serial port enabled ; Receiver enabled 
    BAUDCON=0x00;                   // Tx, Rx and Clock not inverted
    SPBRG=129;                      //BAUD=9615
}

/*  EUSART_SendString  :  Envia una cadena de caracteres a traves desl puerto serial  */

void EUSART_SendString(char *str) {
    
    while(*str) {
        EUSART_TxBuffer=*str;
        EUSART_Wait();
        str++;
    }
}

/*  EUSART_CheckWord  :  Revisa el buffer de entrada para ver si llego la orden para configurar el RTC */

void EUSART_CheckWord(void) {
    
    static char i=0, *auxWord;

    if( estado.WaitingForTime ) {           //La orden de configurar el RTC ya se recibio
        while(*wordRx) {                    //Copio el valor del buffer en una variable auxiliar
            if(*wordRx!=':') {              //Espero el caracter que separa hora, minuto y segundo
                *auxWord=*wordRx;           //Y guardo todos los caracteres menos los separadores
                auxWord++;
                i++;
            }
            wordRx++;
        }
        if(i>7) {                           //Obtuve los ocho numeros que conforman la fecha sin los ':'
            long time;
            char hour, min, sec;
            time=strtol(auxWord,NULL,10);   //Convierto los caracteres a enteros
            hour=time/10000;
            min=time/100-hour*100;
            sec=time-hour*10000;
            sec-=min*100;
            RTC_SetTime(hour,min,sec);          //Obtengo las horas, minutos y segundos por separado y configuro el RTC
        }
    }
    else {                                      //Todavia no recibio la orden de configurar el RTC
        if(!strcmp(wordRx,"rtcconfig"))     estado.ConfigRTCRequest=1;          
        else                                estado.ConfigRTCRequest=0;
    }
}

/*  EUSART_ConfigRTCRequest  :  Envia un mensaje al usuario pidiendo que configure el RTC  */

void EUSART_ConfigRTCRequest(void) {
    
    EUSART_SendString("Indique la hora de la siguiente manera: (HH:MM:SS)\n");
    wordRx[0]='\0';                     //Borro lo que haya recibido
    estado.WaitingForTime=1;
}

/*  EUSART_RX_ISR  :  Rutina de atencion de interrupcion por recepcion de dato por comunicacion serie  */

void EUSART_RX_ISR(void) {
    
    *wordRx=EUSART_RxBuffer;
    wordRx++;
    EUSARTClearFlag();
}
