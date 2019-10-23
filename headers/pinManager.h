/*  Libreria de puertos digitales.  */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

/*  Macros relacionadas con la configuracion de los puertos digitales y con algunos procesos de la maquina de estados  */

#define OFF     0
#define ON      1    
#define false   0
#define true    1

/*  Macros para el control del sistema frio/calor  */

#define HEAT                    LATDbits.LD0
#define HEAT_OFF()              HEAT=OFF
#define HEAT_ON()               HEAT=ON
#define COLD                    LATDbits.LD1
#define COLD_OFF()              COLD=OFF
#define COLD_ON()               COLD=ON

/*  Macros para el control de las ventanas  */

#define WINDOW_UP                LATDbits.LD2
#define WINDOW_DOWN              LATDbits.LD3

/*  Macros para el control de las luces  */

#define LIGHTS                  LATDbits.LD4
#define LIGHTS_OFF()            LIGHTS=OFF
#define LIGHTS_ON()             LIGHTS=ON

/*  Prototipos de funciones  */

void pinManager_Init(void);
void TurnOnLights(void);
void TurnOffLights(void);
void TurnOnHeat(void);
void TurnOnCold(void);
void TurnOff(void);
void CloseWindow(void);
void OpenWindow(void);
void INT0_ISR(void);

#endif /* PIN_MANAGER_H */