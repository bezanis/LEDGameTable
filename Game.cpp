#include <Game.h>

Game::Game(NESController *controllerIn, Adafruit_WS2801 *stripIn, LCD *lcdIn){
	controller = controllerIn;
	strip = stripIn;
	lcd = lcdIn;
	curPos.setPosition(5,0);
}

Game::~Game(){
};

void Game::run(){};
void Game::resume(){};
