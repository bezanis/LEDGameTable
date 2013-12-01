#include "Color.h"

Color::Color() {
	color = 0;
}

byte Color::getRed(){
	return (color>>16);
}

byte Color::getGreen(){
	return (color>>8)%0x100;
}

byte Color::getBlue(){
	return color%0x100;
}

uint32_t Color::getColor(){
	return color;
}

void Color::setRed(byte inColor){
	color = (((uint32_t)inColor)<<16)+(color%0x10000);
}

void Color::setGreen(byte inColor){
	color = (((color>>16)<<8)+inColor)<<(color%0x100);
}

void Color::setBlue(byte inColor){
	color = ((color>>8)<<8)+inColor;

}

void Color::setColor(uint32_t inColor){
	color = inColor;
}


void Color::setColor(byte red, byte green, byte blue){
	color = (((((uint32_t)red)<<8)+green)<<8)+blue;
}

// Create a 24 bit color value from R,G,B
/*uint32_t Color(byte r, byte g, byte b) {
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;
	c |= b;
	return c;
}*/
