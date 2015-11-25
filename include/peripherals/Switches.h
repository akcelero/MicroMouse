#ifndef SWITCH_H
#define SWITCH_H

namespace Peripheral{
	class Switches{
		uint32_t pin1 = 13;
		uint32_t pin2 = 14;
		uint32_t pin3 = 15;
	public:
		Switches();
		uint32_t check();
	};
}
#endif
