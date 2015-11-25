#ifndef LEDRGB_H
#define LEDRGB_H

namespace Peripheral{
	class LedRGB {
	private:
		uint32_t off = 0;
		uint32_t green = 1;
		uint32_t blue = 2;
		uint32_t cyan = 3;
		uint32_t red = 4;
		uint32_t yellow = 5;
		uint32_t purple = 6;
		uint32_t white = 7;
		void set(uint32_t color);
	public:
		LedRGB();
		// settery używają funkcji set() i podają do niej adekwatne do nazwy zmienne
		void setGreen();
		void setBlue();
		void setCyan();
		void setRed();
		void setYellow();
		void setPurple();
		void setWhite();
		void clear();
	};
}
#endif
