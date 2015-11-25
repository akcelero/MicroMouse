#ifndef SENSORS_H
#define SENSORS_H

namespace Controler{
	class Sensors{
		Peripheral::Transmiters transmiters;
		Peripheral::Receivers receivers;
	public:
		Sensors();
		int measureLeftDistance();
		int measureRightDistance();
		int measureFrontLeftDistance();
		int measureFrontRightDistance();
	};
}
#endif
