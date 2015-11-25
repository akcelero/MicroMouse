#ifndef RECEIVERS_H
#define RECEIVERS_H

namespace Peripheral{
	class Receivers{
		int frontRight = 10;
		int frontLeft = 11;
		int right = 12;
		int left = 13;
		int getADC(int ADCin);
	public:
			Receivers();
			int getRight();
			int getLeft();
			int getFrontRight();
			int getFrontLeft();
			int getFront();
	};
}
#endif
