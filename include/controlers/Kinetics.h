#ifndef KINETICS_H
#define KINETICS_H

namespace Controler{
	class Kinetics{
		Controler::Sensors sensors;
		Peripheral::Encoders encoders;
		Peripheral::Motors motors;
		Peripheral::LedRGB ledRGB;

		volatile static bool flag;

		long long targetDistance = 0.0;

		long long leftDirection = 0;
		long long rightDirection = 0;

		long long timeOfAcceleration = 100;

		long long maxPeriodDistance = 50;//35;
		long long minPeriodDistance = 3;

		long double globalLeftDistance = 0;
		long double globalRightDistance = 0;

		long long globalSetDistance = 0;

		long double periodLeftDistance = 0;
		long double periodRightDistance = 0;

		long double periodSetDistance = 0;


		long double rotationPDLastError = 0.0;
		long double leftPDLastError = 0.0;
		long double rightPDLastError = 0.0;

		long double vpL = .2;//.5;
		long double vpR = .2;//.5;

		long double vdL = .7;
		long double vdR = .7;//6.

		long double rp = .5;//2.0;
		long double rd = 2.;//21.;


		long long centisecond = 0;

		bool busy = false;

		void countPeriodSetDistance();

		void countPeriodLeftDistance();
		void countPeriodRightDistance();

		void countAndSetPD();

	public:
		Kinetics();
		void calibrate();

		void setDistance(long double mm);
		void setLeftForward();
		void setLeftBack();
		void setRightForward();
		void setRightBack();
		void start();

		void changeKPD();

		void goForward(long double mm);
		void goBack(long double mm);
		void turnLeft(long double angle);
		void turnRight(long double angle);

		static void setFlag();
	};
}

#endif
