#include "Bit_Operations.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Std_Types.h"
#define NVIC_ISER0 (*(uint32 *)0xE000E100)

typedef struct {
	uint32 IMR;
	uint32 EMR;
	uint32 RTSR;
	uint32 FTSR;
	uint32 SWIER;
	uint32 PR;
} ExtiType;

#define EXTI ((ExtiType *)0x40013C00)

int main() {
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_SYSCFG);

	SET_BIT(EXTI->IMR, 0);  // enable exti0

	SET_BIT(NVIC_ISER0, 6);  // enable line 0 on nvic

	SET_BIT(EXTI->FTSR, 0);  // falling edge dectection

	Gpio_ConfigPin(GPIO_A, 0, GPIO_INPUT, GPIO_PULL_UP);

	Gpio_ConfigPin(GPIO_B, 0, GPIO_OUTPUT, GPIO_PUSH_PULL);
	while (1) {
	}

	return 0;
}

void EXTI0_IRQHandler(void) {
	Gpio_WritePin(GPIO_B, 0, HIGH);
	for (int i = 0; i < 1000000; i++) {
	}
	Gpio_WritePin(GPIO_B, 0, LOW);
	for (int i = 0; i < 1000000; i++) {
	}

	//clear pending flag
	SET_BIT(EXTI->PR, 0);
}
