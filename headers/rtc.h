#ifndef TIMERS_H
#define TIMERS_H

#include <xc.h>
#include "interruptManager.h"

#define OpenWindowTime      6
#define CloseWindowTime     22

void RTC_Init(void);
void RTC_WaitingConfiguration(void);
void RTC_SetTime(char hour, char min, char secs);
void RTC_ISR(void);
void RTC_Refresh(void);

#endif /* TIMERS_H */