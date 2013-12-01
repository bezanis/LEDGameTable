#ifndef MEGAMAZE_h
#define MEGAMAZE_h

#include "Game.h"
#include <EEPROM.h>

class MegaMaze : public Game{
public:
	MegaMaze(NESController *controller, Adafruit_WS2801 *strip, LCD *lcdIn);
	~MegaMaze();
	void newGame();
	void run();
	void resume();
private:
	void updateDisplay();
	void updateLevelDisplay();
	bool moveCheck(int xmove, int ymove);
	void winLevel();
	int * curLevel();
	int getX(int pos);
	int getY(int pos);
	int getLevelSize();
	int xpos;
	int ypos;
	int level;
	const static int centerX;
	const static int centerY;
	const static int levels[];
	const static int levelSizes[];
	const static long levelColors[];
	const static int levelCount;
};

#endif
