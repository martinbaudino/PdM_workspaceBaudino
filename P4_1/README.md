# Práctica 4 - Punto 1

* Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.

* Implementar una MEF anti-rebote que permita leer el estado del pulsador de la placa NUCLEO-F429ZI y generar acciones o eventos ante un flanco descendente o ascendente, de acuerdo al siguiente diagrama:

[MEF filtro anti-rebotes](MEF.png)

* El estado inicial de la MEF debe ser BUTTON_UP.

* Implementar dentro de main.c, las funciones:

```
void debounceFSM_init();        // debe cargar el estado inicial
void debounceFSM_update();    	// debe leer las entradas, resolver la lógica de
                    		// transición de estados y actualizar las salidas
void buttonPressed();           // debe togglear el LED1
void buttonReleased();        	// debe togglear el LED3
```

* El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante como los implementados en la práctica 3.

* La función debounceFSM_update() debe llamarse periódicamente.

```
typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t
```
