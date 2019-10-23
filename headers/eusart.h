/*  Libreria de EUSART para el uC. Contiene funciones de configuracion y comunicacion serial y algunas funciones relacionadas
    con el pedido de datos para configurar el RTC   */

#ifndef EUSART_H
#define EUSART_H

#include <xc.h>
#include <string.h>
#include <stdlib.h>

/*  Macros relacionadas con registros y bits pertinentes al periferico EUSART  */

#define EUSARTFramingErr()          RCSTAbits.FERR
#define EUSARTOverRunErr()          RCSTAbits.OERR
#define EUSARTTransmitBusy()        !TXSTAbits.TRMT

#define EUSARTClearFlag()           PIR1bits.RCIF=0

#define EUSART_Wait()               while(EUSARTTransmitBusy())

#define EUSART_TxBuffer             TXREG
#define EUSART_RxBuffer             RCREG

char *wordRx;   //Variable global de buffer de datos de entrada

/*  Prototipos de funciones  */

void EUSART_Init(void);
void EUSART_SendString(char *str);
void EUSART_CheckWord(void);
void EUSART_ConfigRTCRequest(void);
void EUSART_RX_ISR(void);

#endif /* EUSART_H */