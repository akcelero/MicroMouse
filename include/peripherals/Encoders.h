#ifndef ENCODERS_H
#define ENCODERS_H

namespace Peripheral{
	class Encoders{
	public:
		Encoders();
		long long getLeft();
		long long getRight();

		void clearLeft();
		void clearRight();
	};
}

#endif
