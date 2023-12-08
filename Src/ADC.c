/*
 * ADC.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Administrator
 */
#include "ADC.h";

#define GPIOA_EN	(1U<<0)
#define ADC12_EN	(1U<<13)


void init_ADC_12(void){
	/*En AHB2 for GPIOA*/
	RCC->AHB2ENR |= GPIOA_EN;
	//Set GPIOA to Analog mode
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER |= (1U<<1);
	//En RCC clck for ADC
	RCC->AHB2ENR |= ADC12_EN;
	//Set ADC 12 register
}

