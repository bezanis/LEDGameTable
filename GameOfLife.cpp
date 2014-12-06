#include <GameOfLife.h>

GameOfLife::GameOfLife(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	lastFrame=0;
	newGame();
}

GameOfLife::~GameOfLife(){
}

void GameOfLife::newGame(){
	updateDisplay();
	randomSeed(analogRead(0));
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			if(random(3)>=2){
				currentFrame[j][i] = false;
			}else{
				currentFrame[j][i] = true;
			}
		}
	}
}

void GameOfLife::run(){
	if(controller->buttonPressed(controller->BUTTON_SELECT) && !controller->buttonHandled(controller->BUTTON_SELECT)){
		controller->handleButton(controller->BUTTON_SELECT);
		newGame();
	}
	if(millis() > ((unsigned long)(lastFrame+300))){
			lastFrame = millis();
			nextFrame();
	}
}

void GameOfLife::nextFrame(){
	boolean nextFrame[10][20];
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			int neighbors = 0;
			if(j>0 && i>0 && currentFrame[j-1][i-1]){
				neighbors++;
			}
			if(i>0 && currentFrame[j][i-1]){
				neighbors++;
			}
			if(j<boardWidth-1 && i>0 && currentFrame[j+1][i-1]){
				neighbors++;
			}

			if(j>0 && currentFrame[j-1][i]){
				neighbors++;
			}
			if(j<boardWidth-1 && currentFrame[j+1][i]){
				neighbors++;
			}

			if(j>0 && i<boardHeight-1 && currentFrame[j-1][i+1]){
				neighbors++;
			}
			if(i<boardHeight-1 && currentFrame[j][i+1]){
				neighbors++;
			}
			if(j<boardWidth-1 && i<boardHeight-1 && currentFrame[j+1][i+1]){
				neighbors++;
			}

			if(neighbors<2 || neighbors>3){
				nextFrame[j][i] = false;
			}else if(neighbors==2){
				nextFrame[j][i] = currentFrame[j][i];
			}else if(neighbors==3){
				nextFrame[j][i] = true;
			}

		}
	}

	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			currentFrame[j][i] = nextFrame[j][i];
			if(currentFrame[j][i]){
				strip->setPixelColor(j,i,0xFFFFFF);
			}else{
				strip->setPixelColor(j,i,0x000000);
			}
		}
	}
	strip->show();
}

void GameOfLife::resume(){
	nextFrame();
	updateDisplay();
}

void GameOfLife::updateDisplay(){
	lcd->write(18); // Turn light off
}
