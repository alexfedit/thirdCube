/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main_init.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Private variables ---------------------------------------------------------*/
volatile int i = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE END 0 */
void Mode1() {
	HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin,
			GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin,
			GPIO_PIN_RESET);
	HAL_Delay(500);
}
void Mode2() {
	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD3_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD6_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD3_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD5_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOD, LD6_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
}
void Mode3() {
	HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOD, LD5_Pin | LD6_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOD, LD5_Pin | LD6_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
}

int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	USART2->CR1 |= USART_CR1_RXNEIE;

	/* USER CODE BEGIN 2 */

	while (1) {
		if (i == 0) {
			HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin,
					GPIO_PIN_SET);
		} else if (i == 1) {
			Mode1();
		} else if (i == 2) {
			Mode2();
		} else if (i == 3) {
			Mode3();
		} else {
			i = 0;
		}

	}
	/* USER CODE END 3 */

}

/** System Clock Configuration
 */
void send_to_uart(uint8_t data) {
	while (!(USART2->SR & USART_SR_TC))
		;
	USART2->DR = data;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_0) {
		i++;
	}
}
void USART2_IRQHandler(void) {
	char uart_data;
	if ((USART2->SR & USART_SR_RXNE) != RESET) {
		uart_data = USART2->DR;
		send_to_uart(uart_data);
		if (uart_data == '1') {
			i = 1;
		} else if (uart_data == '2') {
			i = 2;
		} else if (uart_data == '3') {
			i = 3;
		} else
			i = 0;
	}
}


#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */

}

#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
