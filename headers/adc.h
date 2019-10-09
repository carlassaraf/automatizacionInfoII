#ifndef ADC_H
#define ADC_H

#include <xc.h>

#define ADC_SetChannel(ch)  ADCON0bits.CHS=ch
#define ADC_Start()         ADCON0bits.GO=1
#define ADC_Busy()          ADCON0bits.GO

#define dTMax               1.5
#define dTMin               -1.5

typedef unsigned int uint16;

float tempVal, setpointVal, dT;

void ADC_Init(void);
void ADC_StartConvertion(unsigned char channel);
uint16 ADC_Read(unsigned char channel);
void ADC_RefreshVal(void);
void ADC_ConvertToTemperature(void);
//void ADC_ISR(void);

#endif
