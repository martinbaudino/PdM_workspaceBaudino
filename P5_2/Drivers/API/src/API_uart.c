/*
 * API_uart.c
 *
 *  Created on: 20 sep 2022
 *      Author: marti
 */
#include "API_uart.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
static UART_HandleTypeDef UartHandle;

/* Private define ------------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
 resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

#define MAX_TIMEOUT 0xFFFF
#define INIT_BUFF 10U

/* Private function prototypes -----------------------------------------------*/


/**
 * @fn bool_t uartInit(void)
 * @brief Inicialización de módulo UART que utiliza VirtualCOM port
 *
 * Configura la USART3 del STM32F429ZI, que en la placa NUCLEO está conectada
 * al VirtualCOM port y actúa como backchannel de comunicación entre la placa
 * y la PC utilizando el mismo cable USB con el que se programa el
 * microcontrolador.
 * Por defecto configura la comunicación como  7O1 @ 9600bps
 *
 *
 * Envía sus parámetros de configuración utilizando funciones propias del
 * módulo
 *
 * @return **true** si la configuración fue exitosa y **flase** si falló.
 */
bool_t uartInit(void) {
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = ODD parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance = USARTx;

	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		/* Initialization Error */
		return false;
	}
	char sendBuff[INIT_BUFF] = {0};

	uartsendString((uint8_t *)"BaudRate: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.BaudRate, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nWordLength: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.WordLength, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nStopBits: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.StopBits, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nParity: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.Parity, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nHwFlowCtl: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.HwFlowCtl, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nMode: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.Mode, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\nOverSampling: ");
	uartsendString((uint8_t *)itoa(UartHandle.Init.OverSampling, sendBuff, INIT_BUFF));
	uartsendString((uint8_t *)"\r\n");
	return true;
}

/**
 * @fn void uartsendString(uint8_t*)
 * @brief Transmite cadenas de caracteres de tamaño variable terminadas en '\0'
 *
 * Función insegura. Aunque chequea que el buffer tenga espacio reservado,
 * puede producir un buffer overflow si la cadena no está terminada en '\0'.
 *
 * @param pstring Cadena de caracteres válida a transmitir.
 */
void uartsendString(uint8_t *pstring) {
	uint8_t buff_size;

	if (pstring != NULL) {
		buff_size = strlen((char*) pstring);
		HAL_UART_Transmit(&UartHandle, pstring, buff_size, MAX_TIMEOUT);
	}
}

/**
 * @fn void uartSendStringSize(uint8_t*, uint16_t)
 * @brief Transmite una cantidad solicitada de caracteres de un buffer
 *
 * Función segura. Solo transmitirá la cantidad de caracteres del solicitados.
 *
 * @param pstring Buffer de caracteres a transmitir
 * @param size Cantidad de caracteres del buffer a transmitir
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size) {

	if (sizeof(pstring) >= size) {
		HAL_UART_Transmit(&UartHandle, pstring, size, MAX_TIMEOUT);
	}
}

/**
 * @fn void uartReceiveStringSize(uint8_t*, uint16_t)
 * @brief Recibe una cantidad solicitada de caracteres y guarda en buffer
 *
 * No realiza ningún tipo de procesamiento sobre los datos recibidos
 *
 * @param pstring Buffer de caracteres para guardar datos
 * @param size Cantidad de datos a guardar
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Receive(&UartHandle, pstring, size, MAX_TIMEOUT);
}

