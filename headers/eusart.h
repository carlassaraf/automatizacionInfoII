#ifndef EUSART_H
#define EUSART_H

#include <xc.h>
#include <string.h>
#include <stdlib.h>

#define EUSARTFramingErr()          RCSTAbits.FERR
#define EUSARTOverRunErr()          RCSTAbits.OERR
#define EUSARTTransmitBusy()        !TXSTAbits.TRMT

#define EUSARTTransmitInt()         PIE1bits.TXIE
#define EUSARTTransmitIntEnable()   PIE1bits.TXIE=1
#define EUSARTTransmitDone()        PIR1bits.TXIF

#define EUSARTReceiveInt()          PIE1bits.RCIE
#define EUSARTReceiveIntEnable()    PIE1bits.RCIE=1
#define EUSARTReceiveDone()         PIR1bits.RCIF
#define EUSARTClearFlag()           PIR1bits.RCIF=0

#define EUSART_Wait()               while(EUSARTTransmitBusy())

#define EUSART_TxBuffer             TXREG
#define EUSART_RxBuffer             RCREG

char *wordRx;

void EUSART_Init(void);
void EUSART_SendString(char *str);
void EUSART_CheckWord(void);
void EUSART_ConfigRTCRequest(void);
void EUSART_RX_ISR(void);

#endif /* EUSART_H */