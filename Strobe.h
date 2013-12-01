#ifndef STROBE_H_
#define STROBE_H_

#include "Game.h"

class Strobe : public Game {
public:
	Strobe(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~Strobe();
	void run();
	void resume();
private:
	unsigned int strobeSpeed;
};


#endif
