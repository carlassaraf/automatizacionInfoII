#ifndef I2C_H
#define I2C_H

#include "deviceConfig.h"

#define I2CTransmitBuffer       SSPBUF
#define I2CReceiveBuffer        SSPBUF

#define I2CStopDetected()       SSPSTATbits.P                   //Se detecto un bit de stop
#define I2CStartDetected()      SSPSTATbits.S                   //Se detecto un bit de start
#define I2CTransmiting()        SSPSTATbits.NOT_W               //El modulo esta transmitiendo
#define I2CBufferFull()         SSPSTATbits.BF                  //Buffer lleno
#define I2CColitionDetected()   SSPCON1bits.WCOL                //Se intento transmitir cuando las condiciones no eran validas

#define I2CWrite(DATA)          SSPBUF=DATA
#define I2CWait()               while( I2CTransmiting() && I2CBufferFull() )        //Rutina de espera a que el I2C este desocupado

#define I2CTransmitOK           0
#define I2CErrColition          1
#define I2CBusy                 2

#define I2CEnable()             SSPCON1bits.SSPEN=1
#define I2CMode(MODE)           SSPCON1bits.SSPM=MODE
#define I2CSpeedKHz(KHz)        SSPADD=((_XTAL_FREQ/(4*KHz))-1) //Calculo el valor del registro para la velocidad que quiero

#define I2CACK()                SSPCON2bits.ACKSTAT             //No se recibio el bit de ack del slave
#define I2CStartAckSequence()   SSPCON2bits.ACKEN=1             //Iniciar secuencia de ack
#define I2CStart()              SSPCON2bits.SEN=1               //Iniciar condiciones de start
#define I2CStop()               SSPCON2bits.PEN=1               //Iniciar condiciones de stop
#define I2CContinuousStart()    SSPCON2bits.RSEN=1              //Iniciar repetidas condiciones de start
#define I2CMaster               0x8

typedef struct {
    
    unsigned char address : 7;
    unsigned char *data;
} i2c_buffer;

void I2C_Init(void);
unsigned char I2C_Send(i2c_buffer buffer);

#endif