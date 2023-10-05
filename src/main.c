#include "Bit_Operations.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Spi.h"
#include "Std_Types.h"
#include "Tc72.h"
#include "Usart.h"
#include "Utils.h"
#include "Gpio.h"

#define Lab9_USART

#define TC72_SELECT() (Gpio_WritePin(GPIO_B, 0, 1))
#define TC72_UNSELECT() (Gpio_WritePin(GPIO_B, 0, 0))

void floatToStr(float val, char data[]);

int main() {
#if defined(Lab9_USART)
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_USART2);
	Usart2_Init();
	uint8 data = 0;
	while(1){
		data = Usart2_RecieveByte();
		if(data == '1'){
			Usart2_TransmitString("Hello\r\n");
		}
		if(data == '2'){
			Usart2_TransmitString("Welcome\r\n");
		}
	}
#else // Clear line 11 to enable Spi code
	char usart2Data[] = { '-', ' ', ' ', '.', ' ', ' ', '\r', '\n', '\0' };
	uint8 spiData = 0;
	float32 temperature = 0;

	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_SPI1);
	Rcc_Enable(RCC_USART2);

	/* Slave Select */
	Gpio_ConfigPin(GPIO_B, 0, GPIO_OUTPUT , GPIO_PUSH_PULL);
	Gpio_WritePin(GPIO_B, 0, 0);


	Usart2_Init();
	Spi1_Init(SPI_MASTER, SPI_IDLE_LOW, SPI_SAMPLE_SOCAND_TRANSITION);

	TC72_SELECT();
	Tc72_Init(0x00);
	TC72_UNSELECT();

	while (1) {
		temperature = 0.0f;
		TC72_SELECT();
		Tc72_RegisterRead(0x01, &spiData);
		TC72_UNSELECT();

		if (spiData & (1 << 7)) {
			temperature += 0.5f;
		}
		if (spiData & (1 << 6)) {
			temperature += 0.25f;
		}

		TC72_SELECT();
		Tc72_RegisterRead(0x02, &spiData);
		TC72_UNSELECT();

		temperature += (signed char) spiData;


		floatToStr(temperature, usart2Data);   // we want to printf "13.5" how??

		Usart2_TransmitString(usart2Data);

		for(int i= 0; i < 100000; i++);

	}
#endif
	return 0;
}

void floatToStr(float val, char data[]) {
	if (val < 0) {
		*data = '-';
		data++;
		val *= -1;
	}
	int intVal = val * 100;
	data[4] = (intVal % 10) + '0';
	intVal /= 10;
	data[3] = (intVal % 10) + '0';
	data[2] = '.';
	intVal /= 10;
	data[1] = (intVal % 10) + '0';
	intVal /= 10;
	data[0] = (intVal % 10) + '0';

	data[5] = '\r';
	data[6] = '\n';
	data[7] = '\0';
}



