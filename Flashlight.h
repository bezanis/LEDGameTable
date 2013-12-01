#ifndef FLASHLIGHT_H_
#define FLASHLIGHT_H_

#include "Game.h"

class Flashlight : public Game {
public:
	Flashlight(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~Flashlight();
	void run();
	void resume();
private:
	int lightType;
	int lightColor;
	int phase;
};


#endif
