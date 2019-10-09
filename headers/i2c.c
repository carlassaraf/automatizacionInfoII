#include <xc.h>
#include "i2c.h"

void I2C_Init(void) {

    TRISB|=0x03;                    //RB0 y RB1 son entradas
    I2CEnable();                    //Habilita SDA y SCL (RB0 y RB1)
    I2CMode(I2CMaster);             //Elige el modo de operación
    SSPSTATbits.SMP=1;              //Slew Rate deshabilitado para velocidades estandard
    SSPSTATbits.CKE=0;              //Deshabilita entradas especificas de SMBus
    I2CSpeedKHz(100);               //Configuro la velocidad de la comunicacion
}

unsigned char I2C_Send(i2c_buffer buffer) {

    if( !I2CTransmiting() && !I2CBufferFull() ) {       //Solo voy a enviar si no estoy transmitiendo ya y el buffer está vacío

        I2CStart();
        I2CWrite(buffer.address<<1);                    //Corro el address en 1 bit y el cero que queda es para dar la instruccion de escribir
        if( I2CColitionDetected() ) {
            I2CStop();
            return I2CErrColition;
        }
        I2CWait();
        while(*(buffer.data)) {
            I2CWrite(buffer.data);
            if( I2CColitionDetected() ) {
                I2CStop();
                return I2CErrColition;
            }
            I2CWait();
        }
        I2CStop();
        return I2CTransmitOK;
    }
    else return I2CBusy;
}