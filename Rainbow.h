#ifndef Rainbow_h
#define Rainbow_h

#include "Game.h"
#include "ffft.h"

class Rainbow : public Game{
public:
	Rainbow(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~Rainbow();
	void run();
	void resume();
private:
	int red;
	int green;
	int blue;
	int colorMode;
};
#endif
