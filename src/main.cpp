#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#include "peripherals.h"

#include "controlers/Sensors.h"
#include "controlers/Sensors.cpp"
//
#include "controlers/Kinetics.h"
#include "controlers/Kinetics.cpp"
//#include "peripherals/LedRGB.h"
//#include "peripherals/LedRGB.cpp"

Controler::Kinetics kinetics;
Peripheral::LedRGB ledRGB;
Peripheral::Encoders encoders;
Peripheral::Motors motors;
Peripheral::Switches switches;

#define moveForward

int main(void){

	SysTick_Config((uint32_t)(72000000/20));// ustawienie 100 razy na sekunde (nie można mniej niż 10ps)
	encoders.clearLeft();
	encoders.clearRight();
	int tmp = 0;

	while(tmp<1000)
		tmp = switches.check() == 4 ? tmp + 1 : 0;
	ledRGB.setCyan();
	while(switches.check()!=0);

	ledRGB.setGreen();
	for(volatile int i=0;i<5000000;i++);
	ledRGB.clear();

	while(1==1){
//		motors.setSpeedRight(100);
		kinetics.goForward(70.0);
//		kinetics.turnRight(90.0);
//		kinetics.goForward(18.0);
//		kinetics.turnRight(180.0);
//		kinetics.goForward(18.0);
//		kinetics.turnRight(90);
		kinetics.goBack(70.0);
		ledRGB.setGreen();
		for(volatile int i=0;i<8000000;i++);
		ledRGB.clear();
	}
	return 0;
}

extern "C" void SysTick_Handler(void)  {
	Controler::Kinetics::setFlag();

}
