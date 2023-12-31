/*
 * ADC.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Administrator
 */
#include "ADC.h";
#include "stm32g431xx.h"

#define GPIOA_EN	(1U<<0)
#define ADC12_EN	(1U<<13)

#define ADCRDY		(1U<<0)
#define ADCRDYIE	(1U<<0)
#define ADCEN		(1U<<0)
#define JADSTART	(1U<<3)
#define ADSTART		(1U<<2)
#define ADCIS		(1U<<1)
#define ADCSTART	(1U<<2)

#define ISR_EOC		(1U<<2)

void init_ADC1_2(void){
	/*En AHB2 for GPIOA*/
	RCC->AHB2ENR |= GPIOA_EN;
	//Set GPIOA to Analog mode
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER |= (1U<<1);
	//En RCC clck for ADC
	RCC->AHB2ENR |= ADC12_EN;
	//Set ADC 12 register

	//Reset the addc
	ADC1->ISR |= ADCRDY;

	ADC1->SQR1 &= ~(1U<<6);
	ADC1->SQR1 |= (1U<<7);
	ADC1->SQR1 &= ~(1U<<8);
	ADC1->SQR1 &= ~(1U<<9);
	ADC1->SQR1 &= ~(1U<<10);

	ADC1->SQR1 |= (1U<<0);

	//Set ADCEN
	ADC1->CR |= ADCEN;

	//Wait until ADCRDY Interrupt is en
	while(!(ADC1->IER & ADCRDYIE));
}

void ADC1_2_start_conversion(void){
	ADC1->CR |= ADCSTART;
}

uint32_t ADC1_2_read_data(){

	while(!(ADC1->ISR & ISR_EOC));

	return ADC1->DR;
}



int ADC_12_disable(void){

	while((ADC1->CR & ADSTART) || (ADC1->CR & JADSTART));

	ADC1->CR |= ADCIS;

	while((ADC1->CR & ADCEN));

	return 1;
}

int ADC_12_force_disable(void){

	while((ADC1->CR & ADSTART) || (ADC1->CR & JADSTART));

	ADC1->CR |= ADCIS;

	while((ADC1->CR & ADCEN));

	return 1;
}
