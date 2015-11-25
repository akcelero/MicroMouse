#include "stm32f10x.h"
#include "Switches.h"


Peripheral::Switches::Switches(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= ( 1 <<23 );
	GPIOC->CRH |= ( 1 <<27 );
	GPIOC->CRH |= ( 1 <<31 );

	GPIOC->CRH &= ~( 1<<23 );
	GPIOC->CRH &= ~( 1<<27 );
	GPIOC->CRH &= ~( 1<<31 );

	GPIOC->ODR |= (1<<13)|(1<<14)|(1<<15);

}
uint32_t Peripheral::Switches::check(){
	return		(!(GPIOC->IDR & (1 << pin1))<<0)
			|	(!(GPIOC->IDR & (1 << pin2))<<1)
			| 	(!(GPIOC->IDR & (1 << pin3))<<2);
}
