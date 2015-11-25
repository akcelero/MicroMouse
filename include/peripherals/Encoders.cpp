#include "stm32f10x.h"
#include "Encoders.h"

Peripheral::Encoders::Encoders(){
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPAEN;
	GPIOA->CRL		|=	GPIO_CRL_CNF7_1 | GPIO_CRL_CNF6_1;
	GPIOA->CRL		&=	~((GPIO_CRL_CNF7_0)|(GPIO_CRL_CNF6_0));
	GPIOA->CRL		&=	~((GPIO_CRL_MODE7_1)|(GPIO_CRL_MODE6_1));
	GPIOA->CRL		&=	~((GPIO_CRL_MODE7_0)|(GPIO_CRL_MODE6_0));
	GPIOA->ODR		|= (1<<7) | (1<<6);

	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
	GPIOA->CRL		|=	GPIO_CRL_CNF7_1 | GPIO_CRL_CNF6_1;
	GPIOA->CRL		&=	~((GPIO_CRL_CNF7_0)|(GPIO_CRL_CNF6_0));
	GPIOA->CRL		&=	~((GPIO_CRL_MODE7_1)|(GPIO_CRL_MODE6_1));
	GPIOA->CRL		&=	~((GPIO_CRL_MODE7_0)|(GPIO_CRL_MODE6_0));
	GPIOB->ODR		|= (1<<7) | (1<<6);

	RCC->APB1ENR	|= RCC_APB1ENR_TIM4EN;
	TIM4->SMCR		|= TIM_SMCR_SMS_1;
	TIM4->ARR		=  65535;
	TIM4->CCMR1		|= TIM_CCMR1_CC1S_1 | TIM_CCMR1_CC2S_0;
	TIM4->CCER		|= TIM_CCER_CC1P;
	TIM4->CR1		|= TIM_CR1_CEN;

	RCC->APB1ENR	|=	RCC_APB1ENR_TIM3EN;
	TIM3->SMCR		|=	TIM_SMCR_SMS_1;
	TIM3->ARR		=	65535;
	TIM3->CCMR1		=	TIM_CCMR1_CC1S_1 | TIM_CCMR1_CC2S_0;
	TIM3->CR1		=	TIM_CR1_CEN;

}

long long Peripheral::Encoders::getLeft(){
	return (long long)(static_cast<int16_t>(TIM4->CNT));
}

long long Peripheral::Encoders::getRight(){
	return (long long)(static_cast<int16_t>(TIM3->CNT));
}

void Peripheral::Encoders::clearLeft(){
	TIM4->CNT = 0;
}

void Peripheral::Encoders::clearRight(){
	TIM3->CNT = 0;
}
