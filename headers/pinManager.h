#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include <xc.h>

#define OUTPUT  0
#define INPUT   1

#define false   0
#define true    1

#define HEAT                    LATDbits.LD0
#define HEAT_ON()               LATDbits.LD0=1
#define HEAT_OFF()              LATDbits.LD0=0

#define COLD                    LATDbits.LD1
#define COLD_ON()               LATDbits.LD1=1
#define COLD_OFF()              LATDbits.LD1=0

#define WINDOWUP                LATDbits.LD2

#define WINDOWDOWN              LATDbits.LD3

#define LIGHTS                  LATDbits.LD4
#define LIGHTS_OFF()            LATDbits.LD4=0
#define LIGHTS_ON()             LATDbits.LD4=1

void pinManager_Init(void);
void TurnOnLights(void);
void TurnOffLights(void);
void TurnOnHeat(void);
void TurnOnCold(void);
void TurnOff(void);
void CloseWindow(void);
void OpenWindow(void);
void INT0_ISR(void);

#endif