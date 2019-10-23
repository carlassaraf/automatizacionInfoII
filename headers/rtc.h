/*  Libreria de Timer1 que cumple el rol de Real Time Clock. Tiene funciones relacionadas con la configuracion del RTC, variables
    pertinentes a su uso, rutina de atencion de interrupcion por desborde (cada segundo) y llamadas a funciones de otros perifericos
    que estan controlados periodicamente por este modulo. El RTC se configura por comunicacion serial con la palabra "rtcconfig"  */

#ifndef RTC_H
#define RTC_H

#include <xc.h>
#include "interruptManager.h"

/*  Constantes de tiempo para abrir o cerrar las ventanas  */

#define OpenWindowTime      6
#define CloseWindowTime     22

/*  Prototipos de funciones  */

void RTC_Init(void);
void RTC_WaitingConfiguration(void);
void RTC_SetTime(char hour, char min, char secs);
void RTC_ISR(void);
void RTC_Refresh(void);

#endif /* RTC_H */