#ifndef GameOfLife_h
#define GameOfLife_h

#include "Game.h"

class GameOfLife : public Game{
public:
	GameOfLife(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~GameOfLife();
	void newGame();
	void run();
	void resume();
private:
	void nextFrame();
	void updateDisplay();
	boolean currentFrame[10][20];
	long lastFrame;
};
#endif
