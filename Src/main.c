#include "stm32g431xx.h"

#define GPIOA_EN	(1U<<0)
#define GPIOC_EN	(1U<<2)

#define PIN5		(1U<<5)
#define PIN13		(1U<<13)

#define LED_PIN		PIN5
#define BTN_PIN		PIN13

int main(void)
{
	RCC->AHB2ENR |= GPIOA_EN;
	RCC->AHB2ENR |= GPIOC_EN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);
    /* Loop forever */
	while(1){

		if(GPIOC->IDR & BTN_PIN){
			GPIOA->BSRR |= LED_PIN;
//			for(int i = 0; i<10000000; i++);
		}else{
			GPIOA->BSRR |= (1U<<21);
		}

	}
}
