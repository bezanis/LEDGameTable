#ifndef ConnectFour_h
#define ConnectFour_h

#include "Game.h"

class ConnectFour : public Game{
public:
	ConnectFour(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~ConnectFour();
	void newGame();
	void run();
	void resume();
private:
	void updateDisplay();
	void redrawBoard();
	int dropPos;
	byte curPlayer;
	byte winner;
	Point winPos[4];
	long winTime;
	int dropHeight;
	byte droppedPieces[7][6];
	const static int xOffset;
};
#endif
