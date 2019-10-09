#include "interruptManager.h"
#include "rtc.h"
#include "adc.h"
#include "pinManager.h"
#include "eusart.h"

void Interrupt_Init(void) {

    GlobalIntEnable();
    PriorityIntDisable();
    MotionDetectorIntEnable();
    PullUpDisable();
    RisingEdgeInt();
    //ADConvertionDoneIntEnable();
    RTCOverflowIntEnable();
    EUSARTReceiveIntEnable();
}

void __interrupt() Interrupt_Handler(void) {
   
    if( GlobalInt() && PeripherialInt() ) {
        if( MotionDetectorInt() && MotionDetectedFlag() ) {             //Si se produjo interrupcion externa      
            INT0_ISR();
        }
    /*    if( ADConvertionDoneInt() && ADConvertionDone() ) {         //Si se produjo interrupcion por ADC
            ADC_ISR();
        }*/
        if( RTCOverflowInt() && RTCOverflow() ) {                       //Si se produjo interrupcion por RTC
            RTC_ISR();
        }
        if( EUSARTReceiveInt() && EUSARTReceiveDone() ) {               //Si se produjo interrupcion por EUSART
            EUSART_RX_ISR();
        }
    }
}