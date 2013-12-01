#ifndef DRMARIO_h
#define DRMARIO_h

#include "Game.h"
#include <EEPROM.h>

class DrMario : public Game{
public:
	DrMario(NESController *controller, Adafruit_WS2801 *strip, LCD *lcdIn);
	~DrMario();
	void newGame();
	void run();
	void resume();
private:
	void updateDisplay();
	void initializeBoard();
	/*void moveDown();
	void moveLeft();
	void moveRight();
	void spinClockwise();
	void spinCounterClockwise();
	void setPiece();
	void shiftPiecesDown(int row);
	bool clearRows();
	void increaseScore(unsigned long amount);
	void saveHighScore();
	const static int pieces[7][4][3][2];
	const static uint32_t pieceColors[7];
	const static int levelDropTimes[24];
	const static uint32_t blinkColor;
	int curLevel;
	int lines;
	int curPiece;
	int curRotation;
	long lastDropTime;
	bool clearingRows;
	unsigned long animateClearRowTimer;
	unsigned long score;
	unsigned long highScore;
	char highInitials[3];
	bool gameOver;
	int gameOverAnimation;
	char initials[3];
	int initialsPos;*/
};

#endif
