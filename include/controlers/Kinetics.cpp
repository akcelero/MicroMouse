#include "stm32f10x.h"
#include "Kinetics.h"

volatile bool Controler::Kinetics::flag = false;

Controler::Kinetics::Kinetics(){
}

void Controler::Kinetics::setFlag(){
	flag = true;
}
void Controler::Kinetics::countPeriodLeftDistance(){
	periodLeftDistance = abs(encoders.getLeft());
	periodLeftDistance *= 1.001; // korekcja błędu między enkoderami
	encoders.clearLeft();
	globalLeftDistance += periodLeftDistance;
}
void Controler::Kinetics::countPeriodRightDistance(){
	periodRightDistance = abs(encoders.getRight());
	encoders.clearRight();
	globalRightDistance += periodRightDistance;
}
void Controler::Kinetics::countPeriodSetDistance(){
//	if(centisecond * maxPeriodDistance >= targetDistance){
	if(targetDistance <= (2 * maxPeriodDistance * centisecond + maxPeriodDistance * timeOfAcceleration)/2.0){
		periodSetDistance = maxPeriodDistance -
				(maxPeriodDistance * (centisecond - targetDistance/maxPeriodDistance))
				/timeOfAcceleration;
//		if(periodSetDistance<=minPeriodDistance)
//					periodSetDistance = minPeriodDistance;
	} else
//	if(centisecond <= timeOfAcceleration){
//		periodSetDistance = (maxPeriodDistance * centisecond) / (1 * timeOfAcceleration);
//	} else
	{
		periodSetDistance = maxPeriodDistance;
	}
	if(periodSetDistance<=minPeriodDistance)
			periodSetDistance = minPeriodDistance;
	globalSetDistance += periodSetDistance;
}

void Controler::Kinetics::countAndSetPD(){
	long long leftDifferenceDistance = globalSetDistance - globalLeftDistance;
	long long rightDifferenceDistance = globalSetDistance - globalRightDistance;

	long long differentBetweenWheels = globalLeftDistance - globalRightDistance;

	uint32_t leftResult =
			+ ((long double)leftDifferenceDistance * vpL)
			+ (long double)(leftDifferenceDistance - leftPDLastError) * vdL
			- ((long double)differentBetweenWheels * rp)
			- (long double)(differentBetweenWheels - rotationPDLastError) * rd
			;

	uint32_t rightResult =
			+ ((long double)rightDifferenceDistance * vpR)
			+ (long double)(rightDifferenceDistance - rightPDLastError) * vdR
			+ ((long double)differentBetweenWheels * rp)
			+ (long double)(differentBetweenWheels - rotationPDLastError) * rd
			;

	rotationPDLastError = differentBetweenWheels;

	leftPDLastError = leftDifferenceDistance;
	rightPDLastError = rightDifferenceDistance;

	motors.setSpeedLeft(leftResult * leftDirection);
	motors.setSpeedRight(rightResult * rightDirection);
}

void Controler::Kinetics::start(){
	busy = true;
	centisecond = 0;
	ledRGB.setRed();

	periodLeftDistance = 0;
	periodRightDistance = 0;
	periodSetDistance = 0;

	globalLeftDistance = 0;
	globalRightDistance = 0;
	globalSetDistance = 0;

	rotationPDLastError = 0.0;
	leftPDLastError = 0.0;
	rightPDLastError = 0.0;

	encoders.clearLeft();
	encoders.clearRight();

	while(targetDistance - globalRightDistance > 0 && targetDistance - globalLeftDistance > 0){
		if(flag){
			flag = false;
			centisecond++;
			if(targetDistance <= (2 * maxPeriodDistance * centisecond + maxPeriodDistance * timeOfAcceleration)/2.0){
				ledRGB.setYellow();
			} else {
				ledRGB.setBlue();
			}
			countPeriodLeftDistance();
			countPeriodRightDistance();

			countPeriodSetDistance();
			countAndSetPD();
		}

	}
	motors.bothStop();
	for(volatile int i = 0; i<40000;i++);
}

// mm
void Controler::Kinetics::setDistance(long double mm){
	targetDistance = (mm * 30000.0)/1720.0;
}

void Controler::Kinetics::setRightForward(){
	rightDirection = 1;
}

void Controler::Kinetics::setRightBack(){
	rightDirection = -1;
}

void Controler::Kinetics::setLeftForward(){
	leftDirection = 1;
	if(vpL>vpR){
//		changeKPD();
	}
}

void Controler::Kinetics::setLeftBack(){
	leftDirection = -1;
	if(vpL<vpR){
//		changeKPD();
	}
}

void Controler::Kinetics::changeKPD(){
	long double tmp;
	tmp = vpL;
	vpL = vpR;
	vpR = tmp;

	tmp = vdL;
	vdL = vdR;
	vdR = tmp;
}

void Controler::Kinetics::turnLeft(long double angle){
	setDistance((angle * 8.74 * 3.14)/360.0);
	setLeftBack();
	setRightForward();
	start();
}

void Controler::Kinetics::turnRight(long double angle){
	setDistance((angle * 8.8 * 3.14)/360.0);
	setLeftForward();
	setRightBack();
	start();
}

void Controler::Kinetics::goForward(long double mm){
	setDistance(mm);
	setLeftForward();
	setRightForward();
	start();
}

void Controler::Kinetics::goBack(long double mm){
	setDistance(mm);
	setLeftBack();
	setRightBack();
	start();
}
