#ifndef Visualizer_h
#define Visualizer_h

#include "Game.h"
#include "ffft.h"

class Visualizer : public Game{
public:
	Visualizer(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~Visualizer();
	void run();
	void resume();
private:
	void updateDisplay();
	void redrawBoard();
	int volumeCurPos;
	int visualizerType;
	int volumePositions[20];
};
#endif
