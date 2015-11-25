#include "stm32f10x.h"
#include "Motors.h"

Peripheral::Motors::Motors(){
	// konfiguracja PWM
	RCC	->	APB2ENR	|=		RCC_APB2ENR_AFIOEN;
	RCC ->	APB2ENR	|=	 	RCC_APB2ENR_TIM1EN;

	TIM1->PSC =  500;
	TIM1->ARR =  1000;
	TIM1->CCR1 = 300;
	TIM1->CCR2 = 300;

	TIM1->CCMR1	=	TIM_CCMR1_OC2M_1	|	TIM_CCMR1_OC2M_2; // PWM mode on channel 1 & 2
	TIM1->CCMR1	|=	TIM_CCMR1_OC1M_1	|	TIM_CCMR1_OC1M_2;

	TIM1->CCER	=	TIM_CCER_CC1E		|	TIM_CCER_CC2E; // Enable compare on channel 1 & 2
	TIM1->CR1	=	TIM_CR1_CEN;	// Enable timer
	TIM1->BDTR	=	TIM_BDTR_MOE;

	GPIOA	->	CRH		|=	((1<<0) | (1<<3) | (1<<4) | (1<<7));
	GPIOA	->	CRH		&=	~((1<<2)	|	(1<<6));

	GPIOA	->	ODR		|=	(1<<8)		|	(1<<9);

	// konfiguracja pinów enable
	RCC		->	APB2ENR	|=	RCC_APB2ENR_IOPAEN;
	RCC		->	APB2ENR	|=	RCC_APB2ENR_IOPCEN;
	GPIOC	->	CRL		|=	(1<<29)		|	(1<<25);
	GPIOC	->	CRL		&=	~((1<<30) | (1<<26));

	GPIOC	->	CRH		|=	((1<<1)		|	(1<<5));
	GPIOC	->	CRH		&=	~((1<<2) | (1<<6));

	GPIOC	->	ODR		&=	 ~((1<<6)	|	(1<<7)	|	(1<<8)	|	(1<<9));
}

void Peripheral::Motors::setSpeedLeft(int speed){
	if(speed>=0){
		leftForward();
		TIM1->CCR1 = speed;
	} else {
		leftBack();
		TIM1->CCR1 = -speed;
	}
}
void Peripheral::Motors::setSpeedRight(int speed){
	if(speed>=0){
		rightForward();
		TIM1->CCR2 = speed;
	} else {
		rightBack();
		TIM1->CCR2 = -speed;
	}
}

void Peripheral::Motors::leftForward(){
	GPIOC	->	ODR		&=	 ~(1<<6);
	GPIOC	->	ODR		|=	 (1<<7);
}
void Peripheral::Motors::rightForward(){
	GPIOC	->	ODR		&=	 ~(1<<8);
	GPIOC	->	ODR		|=	 (1<<9);
}
void Peripheral::Motors::leftBack(){
	GPIOC	->	ODR		|=	 (1<<6);
	GPIOC	->	ODR		&=	 ~(1<<7);
}
void Peripheral::Motors::rightBack(){
	GPIOC	->	ODR		|=	 (1<<8);
	GPIOC	->	ODR		&=	 ~(1<<9);
}
void Peripheral::Motors::bothStop(){
	GPIOC	->	ODR		|=	(1<<6) | (1<<7) | (1<<8) | (1<<9);
}
void Peripheral::Motors::rightStop(){
	GPIOC	->	ODR		|=	((1<<8)	|	(1<<9));
}
void Peripheral::Motors::leftStop(){
	GPIOC	->	ODR		|=	((1<<6)	|	(1<<7));
}
