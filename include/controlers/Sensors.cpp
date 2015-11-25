#include "peripherals.h"
#include "Sensors.h"

Controler::Sensors::Sensors(){}

int Controler::Sensors::measureFrontLeftDistance(){
	transmiters.turnOnFront();
	int result = receivers.getFrontLeft();
	transmiters.turnOff();
	return result;
}

int Controler::Sensors::measureFrontRightDistance(){
	transmiters.turnOnFront();
	int result = receivers.getFrontRight();
	transmiters.turnOff();
	return result;
}

int Controler::Sensors::measureRightDistance(){
	transmiters.turnOnRight();
	int result = receivers.getRight();
	transmiters.turnOff();
	return result;
}

int Controler::Sensors::measureLeftDistance(){
	transmiters.turnOnLeft();
	int result = receivers.getLeft();
	transmiters.turnOff();
	return result;
}
