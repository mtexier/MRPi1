#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include "Board.h"



static void Delay_ms(uint32_t Milliseconde);



int main(void)
{

	schedulerInit();

	Board_init();

	ComRPI_init();

	ChargeManagement_Put500mACharge();

	Speaker_init();


	IRremote_init();

	Motors_init();

	Usart3_init(115200, UART_MODE_TX_RX, UART_PARITY_NONE, UART_STOPBITS_1, UART_WORDLENGTH_8B);

	encoder_init();

	Usart_Send_String(UART4, "START ROBOT MRPi1");
	Usart_Send_String(USART3, "HELLO");

	Accelerometer_init();


    while(1)
    {
      schedulerManage();

    }

}


static void Delay_ms(uint32_t Milliseconde)
{
uint32_t Count=0;

  while(Count < 168000*Milliseconde)
  {
    Count++;
  }
  Count = 0;
}


