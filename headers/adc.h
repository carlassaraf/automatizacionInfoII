/*  Libreria para el periferico de ADC del PIC18F4550  */

#ifndef ADC_H
#define ADC_H

#include <xc.h>

/*  Macros para algunos registros y operaciones simples del ADC  */

#define ADC_SetChannel(ch)  ADCON0bits.CHS=ch
#define ADC_Start()         ADCON0bits.GO=1
#define ADC_Busy()          ADCON0bits.GO

/*  Constantes para comparar  */

#define dTMax               1.5
#define dTMin               -1.5

/*  Variables para esta libreria  */

typedef unsigned int uint16;

float tempVal, setpointVal;

/*  Prototipos de funciones  */

void ADC_Init(void);
void ADC_StartConvertion(unsigned char channel);
uint16 ADC_Read(unsigned char channel);
void ADC_RefreshVal(void);
void ADC_ConvertToTemperature(void);

#endif /* ADC_H */
