#include <xc.h>
#include "headers/deviceConfig.h"

void main(void) {
    
    System_Init();      //Inicializacion de registros
   
    void (*Process[])(void) = { RTC_Refresh, HeatSys, Window, Lights }; //Puntero que llama a las tres maquinas de estado
    
    while(1) {
        for(uint8 c=0; c<4; c++) {
            *Process[c];
        }
    }
    return;
}
