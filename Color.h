#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>
#include <Arduino.h>

class Color {
public:
	Color();
	uint32_t getColor();
	byte getRed();
	byte getGreen();
	byte getBlue();
	void setColor(uint32_t color);
	void setColor(byte red, byte green, byte blue);
	void setRed(byte color);
	void setGreen(byte color);
	void setBlue(byte color);
private:
	uint32_t color;
};

#endif
