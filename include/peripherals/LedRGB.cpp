#include "stm32f10x.h"
#include "LedRGB.h"

Peripheral::LedRGB::LedRGB(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= ( 1 << ( ( 10 % 8 ) * 4 ) );
	GPIOC->CRH |= ( 1 << ( ( 11 % 8 ) * 4 ) );
	GPIOC->CRH |= ( 1 << ( ( 12 % 8 ) * 4 ) );
	this->clear();
}
void Peripheral::LedRGB::set(uint32_t color){
	this->clear();
	color <<= 10;
	GPIOC->ODR &= ~(color);
}

void Peripheral::LedRGB::setGreen(){
	this->set(green);
}

void Peripheral::LedRGB::setBlue(){
	this->set(blue);
}

void Peripheral::LedRGB::setCyan(){
	this->set(cyan);
}

void Peripheral::LedRGB::setRed(){
	this->set(red);
}

void Peripheral::LedRGB::setYellow(){
	this->set(yellow);
}

void Peripheral::LedRGB::setPurple(){
	this->set(purple);
}

void Peripheral::LedRGB::setWhite(){
	this->set(white);
}

void Peripheral::LedRGB::clear(){
	GPIOC->ODR |= (1<<10);
	GPIOC->ODR |= (1<<11);
	GPIOC->ODR |= (1<<12);
}
