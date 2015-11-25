#ifndef TRANSMITTER_H
#define TRANSMITTER_H

namespace Peripheral{
	class Transmiters{
		const int left			=	2;
		const int right			=	5;
		const int front			=	3;
		const int none			=	-1;
		void turn(int number);
	public:
		Transmiters();
		void turnOnFront();
		void turnOnLeft();
		void turnOnRight();
		void turnOff();
	};
}

#endif
