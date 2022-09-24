# PdM_workspaceBaudino
STM32CubeIDE workspace para Programación de microcontroladores - CESE - FIUBA
Resolución de Trabajos Prácticos de Martín Sebastián Baudino

## Práctica 1
* Punto 1: Carpeta P1_1. Implementa un generador de secuencia LED1-LED2-LED3 en placa NUCLEO-F429ZI.
* Punto 2: Carpeta P1_2. Implementa un generador de secuencia LED1-LED2-LED3 y su inversa al pulsar el botón USER_BUTTON en placa NUCLEO-F429ZI.

## Práctica 2
* Punto 1: Carpeta P2_1. Implementa funciones auxiliares para retardos no bloqueantes.
* Punto 2: Carpeta P2_1. Implementa un programa con retardos no bloqueantes que hace titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI.
  * LED1: 100 ms.
  * LED2: 500 ms.
  * LED3: 1000 ms.

## Práctica 3
* Punto 1: Carpeta P3. Mueve las declaraciones de las funciones del temporizador a los archivos "API_delay.h" y las definiciones a "API_delay.c", ambas dentro de la carpeta "Drivers/API".
* Punto 2: Carpeta P3. Implementa un un programa que genera secuencias aleatorias para conmutación utilizando un vector de LEDs y retardos no bloqueantes en la NUCLEO-F429ZI.

## Práctica 4:
* Punto 1: Carpeta **P4_1** - Implementa la MEF para filtro anti-rebotes en la aplicación principal. Ver README.md en carpeta correspondiente.
* Punto 2: Carpeta **P4_2** - Mueve la MEF a **API_debounce** e implementa conmutación de **LED2** a frecuencia variable persionanro el pulsador **USER**. Ver README.md en carpeta correspondiente.

## Práctica 5:
* Punto 1: Carpeta **P5_1** - Implementa el módulo **API_uart** con interfaz pública en **API_uart.h** e implementación utilizando miembros privados en **API_uart.c**. Si la UART es inicializada correctamente envía sus parámetros de configuración y lee caracteres conmutando un LED. De esta manera se prueban todas las funciones del módulo. Ver README.md en carpeta correspondiente.
* Punto 2: Carpeta **P5_2** - Utiliza dentro del archivo **API_debounce.c** el módulo **API_uart** para imprimir desde de las funciones privadas **buttonPressed** y **buttonReleased** que se ejecutan cada vez que se produce un flanco efectivo. Ver README.md en carpeta correspondiente.
