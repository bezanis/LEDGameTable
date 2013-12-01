#ifndef Snake_h
#define Snake_h

#include "Game.h"
#include <EEPROM.h>
#include "SnakeSegment.h"

class Snake : public Game{
public:
	Snake(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn);
	~Snake();
	void newGame();
	void run();
	void resume();
private:
	void increaseScore(unsigned long amount);
	void saveHighScore();
	void moveSnake();
	void redrawBoard();
	void addFood();
	void deleteSnake();
	void updateDisplay();
	void setGameOver();
	unsigned long score;
	unsigned long highScore;
	char highInitials[3];
	bool gameOver;
	char initials[3];
	int initialsPos;
	long lastMoveTime;
	enum Directions { UP, DOWN, LEFT, RIGHT };
	Directions moveDirection;
	SnakeSegment * segments;
	Point foodPosition;
	int growing;
};
#endif
