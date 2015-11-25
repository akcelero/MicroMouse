#include "stm32f10x.h"
#include "Receivers.h"

Peripheral::Receivers::Receivers(){
	RCC	->	APB2ENR	|=	RCC_APB2ENR_ADC1EN;
	GPIOC	->	CRL	|=	 ((1<<3)	|	(1<<7)	|	(1<<11)	|	(1<<15)	|	(1<<19)	|	(1<<23));
	GPIOC	->	CRL	&=	 ~((1<<2)	|	(1<<6)	|	(1<<10)	|	(1<<14)	|	(1<<18)	|	(1<<22));
	GPIOC	->	CRL	&=	 ~((1<<1)	|	(1<<5)	|	(1<<9)	|	(1<<13)	|	(1<<17)	|	(1<<21));
	GPIOC	->	CRL	&=	 ~((1<<0)	|	(1<<4)	|	(1<<8)	|	(1<<12)	|	(1<<16)	|	(1<<20));

	GPIOC	->	ODR	&=	~((1<<5)	|	(1<<4)	|	(1<<3)	|	(1<<2)	|	(1<<1)	|	(1<<0));

	ADC1->CR2 |= ADC_CR2_ADON; // Turn on ADC, enable single mode

	// one channel in sequence
	ADC1->SQR1 = (0<<20);//(ADC_SQR1_L_0 | ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3);

	// sample time select:
	/*ADC1->SMPR1 =
			 (ADC_SMPR1_SMP15_0 | ADC_SMPR1_SMP15_1 | ADC_SMPR1_SMP15_2)
			| (ADC_SMPR1_SMP14_0 | ADC_SMPR1_SMP14_1 | ADC_SMPR1_SMP14_2)
			| (ADC_SMPR1_SMP13_0 | ADC_SMPR1_SMP13_1 | ADC_SMPR1_SMP13_2)
			| (ADC_SMPR1_SMP12_0 | ADC_SMPR1_SMP12_1 | ADC_SMPR1_SMP12_2)
			| (ADC_SMPR1_SMP11_0 | ADC_SMPR1_SMP11_1 | ADC_SMPR1_SMP11_2)
			| (ADC_SMPR1_SMP10_0 | ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_2);
	*/
}

int Peripheral::Receivers::getADC(int ADCin){
	ADC1->SQR3 = (ADCin<<0); // ADC channel 12 is first in sequence
	ADC1->CR2 |= ADC_CR2_ADON; // Turn on conversion
	while(!(ADC1->SR & ADC_SR_EOC));
	ADC1->SR &= ~ADC_SR_EOC;
	return ADC1->DR;
}


int Peripheral::Receivers::getRight(){
	return this->getADC(right);
}
int Peripheral::Receivers::getLeft(){
	return this->getADC(left);
}
int Peripheral::Receivers::getFrontRight(){
	return this->getADC(frontRight);
}
int Peripheral::Receivers::getFrontLeft(){
	return this->getADC(frontLeft);
}
