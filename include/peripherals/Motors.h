#ifndef MOTORS_H
#define MOTORS_H

namespace Peripheral{
	class Motors{
		int setLeftSpeed = 0;
		int setRightSpeed = 0;
		int setLeftDirection = 0;
		int setRightDirection = 0;

		void leftForward();
		void rightForward();

		void leftBack();
		void rightBack();

	public:
		// w konstruktorze konfigurowane są PWMy i piny do mostka
		Motors();
		// metody przyjmują wartość od 0 do 1000
		void setSpeedLeft(int speed);
		void setSpeedRight(int speed);

		void bothStop();
		void rightStop();
		void leftStop();
	};
}
#endif
