#ifndef NESController_h
#define NESController_h

#include <stdint.h>
#include <Arduino.h>

typedef uint8_t byte;

class NESController{
public:
	NESController();
	NESController(int controllerLatchPin, int controllerClockPin, int controllerDataPin);
	void controllerRead();
	bool buttonPressed(byte button);
	bool buttonHandled(byte button);
	void handleButton(byte button);
	const static byte BUTTON_RIGHT  = 0b00000001;
	const static byte BUTTON_LEFT   = 0b00000010;
	const static byte BUTTON_DOWN   = 0b00000100;
	const static byte BUTTON_UP     = 0b00001000;
	const static byte BUTTON_START  = 0b00010000;
	const static byte BUTTON_SELECT = 0b00100000;
	const static byte BUTTON_B      = 0b01000000;
	const static byte BUTTON_A      = 0b10000000;
private:
	//byte controllerData;
	//byte controllerDataLast;
	//byte handled;
};
#endif
