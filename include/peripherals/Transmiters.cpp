#include "stm32f10x.h"
#include "Transmiters.h"

Peripheral::Transmiters::Transmiters(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~((1<<23) | (1<<19) | (1<<15) | (1<<11) | (1<<7));
	GPIOA->CRL &= ~((1<<22) | (1<<18) | (1<<14) | (1<<10) | (1<<6)); // must be
	GPIOA->CRL |=  ((1<<21) | (1<<17) | (1<<13) | (1<<9) | (1<<5));
	GPIOA->CRL &= ~((1<<20) | (1<<16) | (1<<12) | (1<<8) | (1<<4));

	GPIOA	->	ODR	&=	~((1<<5)	|	(1<<1)	|	(1<<2)	|	(1<<3)	|	(1<<4));
}
void Peripheral::Transmiters::turn(int number){
	GPIOA	->	ODR	&=	~((1<<1)	|	(1<<2)	|	(1<<3)	|	(1<<4)	|	(1<<5));
	if(1 <= number && number <= 5){
		GPIOA	->	ODR	|=	(1<<number);
	}
}
void Peripheral::Transmiters::turnOnFront(){
	this->turn(front);
}

void Peripheral::Transmiters::turnOnRight(){
	this->turn(right);
}

void Peripheral::Transmiters::turnOnLeft(){
	this->turn(left);
}

void Peripheral::Transmiters::turnOff(){
	this->turn(none);
}
