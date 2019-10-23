/*  Libreria de interrupciones del uC.  */

#ifndef INTERRUPT_MANAGER_H
#define INTERRUPT_MANAGER_H

#include <xc.h>
#include "deviceConfig.h"

/*  Macros de bits relacionados con algunas interrupciones  */

#define GlobalInt()                 INTCONbits.GIE          //Etiqueta para bit de interrupciones globales
#define GlobalIntEnable()           INTCONbits.GIE=1        //Habilita las interrupciones globales

#define PeripherialInt()            INTCONbits.PEIE         //Etiqueta para el bit de interrupciones de perifericos
#define PeripherialIntEnable()      INTCONbits.PEIE=1       //Habilita las interrupciones de perifericos

#define PriorityIntDisable()        RCONbits.IPEN=0         //Deshabilita las prioridades en las interrupciones

/*  Macros relacionadas con la interrupcion externa asociada al sensor de movimiento  */

#define MotionDetectorInt()         INTCONbits.INT0IE       //Etiqueta para el bit de habilitacion de interrupcion del sensor de movimiento
#define MotionDetectorIntEnable()   INTCONbits.INT0IE=1     //Habilita la interrupcion para el pin RB0 conectado al sensor de movimiento
#define PullUpDisable()             INTCON2bits.RBPU=1      //Deshabilita las resistencias de pullup del puerto B
#define RisingEdgeInt()             INTCON2bits.INTEDG2=1   //La interrupcion del sensor de movimiento se da con flanco ascendente
#define FallingEdgeInt()            INTCON2bits.INTEDG2=0   //La interrupcion del sensor de movimiento se da con flanco descendente
#define MotionDetectedFlag()        INTCONbits.INT0IF       //Flag de interrupcion asociada al sensor de movimiento
#define MotionDetectedClearFlag()   INTCONbits.INT0IF=0     //Hago un clear en el flag de interrupcion

/*  Macros relacionadas con la interrupcion por overflow del Timer1 que funcionara como RTC  */

#define RTCOverflowInt()            PIE1bits.TMR1IE         //Etiqueta para el bit de habilitacion de interrupcion de overflow del RTC
#define RTCOverflowIntEnable()      PIE1bits.TMR1IE=1       //Habilita la interrupcion del overflow del RTC
#define RTCOverflow()               PIR1bits.TMR1IF         //Flag de overflow del RTC
#define RTCClearFlag()              PIR1bits.TMR1IF=0       //Hago un clear en el flag de interrupcion

/*  Macros relacionadas con la interrupcion por recepcion de comunicacion serial  */

#define EUSARTReceiveInt()          PIE1bits.RCIE
#define EUSARTReceiveIntEnable()    PIE1bits.RCIE=1
#define EUSARTReceiveDone()         PIR1bits.RCIF

/*  Protitipos de funciones  */

void Interrupt_Init(void);

#endif /* INTERRUPT_MANAGER_H */