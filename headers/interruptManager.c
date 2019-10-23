/*  Libreria de interrupciones del uC.  */

#include "interruptManager.h"
#include "rtc.h"
#include "adc.h"
#include "pinManager.h"
#include "eusart.h"

/*  Interrupt_Init  :  Inicializa las interrupciones de los perifericos necesarios  */

void Interrupt_Init(void) {

    GlobalIntEnable();
    PriorityIntDisable();
    MotionDetectorIntEnable();
    PullUpDisable();
    RisingEdgeInt();
    RTCOverflowIntEnable();
    EUSARTReceiveIntEnable();
}

/*  Interrupt_Handler  :  Rutina de atencion general de interrupciones  */

void __interrupt() Interrupt_Handler(void) {
   
    if( GlobalInt() && PeripherialInt() ) {
        if( MotionDetectorInt() && MotionDetectedFlag() ) {             //Si se produjo interrupcion externa      
            INT0_ISR();
        }
        if( RTCOverflowInt() && RTCOverflow() ) {                       //Si se produjo interrupcion por RTC
            RTC_ISR();
        }
        if( EUSARTReceiveInt() && EUSARTReceiveDone() ) {               //Si se produjo interrupcion por EUSART
            EUSART_RX_ISR();
        }
    }
}