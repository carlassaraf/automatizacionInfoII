![Caratula](/home/carlassaraf/repos/automatizacionInfoII/complementosInforme/Caratula.jpg)











### **Objetivo**

Se quiere hacer el control de ciertos parámetros en una habitación cualquiera a través de un microcontrolador y hardware adicional. 
Los procesos que se quieren medir y controlar son :

- Luces: se prenderán o apagarán dependiendo de la presencia de alguien en el cuarto.
- Temperatura: con un sensor la temperatura se mide la temperatura ambiente y se compara con un setpoint. Dependiendo de la diferencia entre ambos, con un sistema on/off se controla la temperatura del cuarto con un sistema frío/calor. 
- Ventanas: con la ayuda de un RTC (Real Time Clock), se abren o cierran a determinado horario del día. 



### **Diagrama de estados y transiciones**

Para resolver esta situación, se plantean tres máquinas de estado actuando intercaladamente que controlen los tres procesos que se mencionan de la siguiente forma:

![Diagrama de Estados](/home/carlassaraf/repos/automatizacionInfoII/complementosInforme/diagramaDeEstados.png)

En el diagrama de estados y transiciones que se observa arriba se muestran, luego de que se pase por el estado de inicialización, las tres máquinas (**Frío/Calor**, **Ventanas** y **Luces**) que están constantemente alternándose en el procesamiento. En el orden que aparecen ahí, cada una observa las variables que las controlan y cambia al estado que le corresponde.

En el caso de la primer máquina, estará en el estado **Calor** siempre que la temperatura ambiente sea menor a la deseada (dT<-cteT) y en **Frío** siempre que la temperatura ambiente sea mayor a la deseada (dT>cteT). Sin embargo, si la diferencia de temperaturas es muy pequeña, el estado será **Apagado** (-cteT<dT<cteT). 

La segunda variable observará una variable que depende del RTC y eso es la hora. Si la hora actual coincide con el horario predefinido para levantar las ventanas (TimeToOpen), entonces el estado será **Levantadas** hasta que se haga el horario de que se cierren (!TimeToOpen) y el estado pase a **Bajas**.

Por último, en el caso de la máquina de luces, la variable que controla el encendido y apagado es un sensor de movimiento. Si el sensor detecta la presencia de alguien en la habitación (Motion), el estado será **Encendido**. Luego de que transcurra un tiempo sin que se detecte movimiento (!Motion), el estado pasa a **Apagado**.



### **Descripción del código**

Se tuvo que hacer uso de varios periódicos del microcontrolador. Esto requirió que se construyeran varias librerías para organizar y estructurar mejor el código:

| Nombre del archivo                     | Descripción y contenido                                      |
| -------------------------------------- | ------------------------------------------------------------ |
| main.c                                 | Archivo principal con llamada a las distintas máquinas de estado. |
| deviceConfig.c/ deviceConfig.h         | Configuración de fusibles, macros, funciones para las máquinas de estado, de configuración y definición de algunas variables de uso global. |
| pinManager.c/ pinManager.h             | Macros y funciones para configuración y manipulación de pines de entrada y salida. Contiene funciones para controlar el sistema de frío/calor y las luces. |
| interruptManager.c/ interruptManager.h | Macros y llamada a rutinas de atención de interrupciones. Las interrupciones que se atienden son: la del RTC que sincroniza todos los demás eventos, la del sensor de movimiento y la de recepción de datos por EUSART para configurar el RTC. |
| rtc.c/rtc.h                            | Macros, funciones y variables pertinentes a la configuración y trabajo del Timer1 que opera como RTC con un cristal de 32.768KHz. |
| adc.c/adc.h                            | Configuración y funciones que controlan las lecturas analógicas y las comparan para manipular el sistema de frío/calor. |
| eusart.c/eusart.h                      | Configuración y funciones que atienden la comunicación inicial que permitirá configurar el RTC. |