#include "GameOfLife.h"
#include "Rainbow.h"
#include "DrMario.h"
#include "MegaMaze.h"
#include "Tetris.h"
#include "Snake.h"
#include "ConnectFour.h"
#include "Visualizer.h"
#include "Flashlight.h"
#include "LCD.h"

const int controllerLatchPin = 2; // set the controller latch pin - Orange
const int controllerClockPin = 3; // set the controller clock pin - Red
const int controllerDataPin = 4; // set the controller data in pin - Yellow
const int pixelsDataPin = 10; // Yellow wire on Adafruit Pixels
const int pixelsClockPin = 11; // Green wire on Adafruit Pixels
const int lcd1Pin = 8;
const int lcd2Pin = 9;

Adafruit_WS2801 *strip;
NESController *controller;
LCD *lcd;
int curGame=0;
int displayedGame=0;
Game *currentGame = NULL;
bool paused = true;
String gameNames[] = {"    Tetris    ","  Mega Maze   ","    Snake     "," Connect Four "," Game of Life ","  Visualizer  ","  Flashlight  ","   Rainbow   "};

int main(void) {
	init();
	setup();
	while (true) {
		loop();
	}
}

// The setup() method runs once, when the sketch starts
void setup() {
	// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
	strip = new Adafruit_WS2801(10,20, pixelsDataPin, pixelsClockPin,0);
	controller = new NESController(controllerLatchPin,controllerClockPin,controllerDataPin);
	//lcd = new LCD(new SoftwareSerial(255,lcd1Pin),new SoftwareSerial(255,lcd2Pin));
	lcd = new LCD(lcd1Pin,lcd2Pin);
	pinMode(controllerLatchPin, OUTPUT);
	pinMode(controllerClockPin, OUTPUT);
	pinMode(controllerDataPin, INPUT);
	digitalWrite(controllerLatchPin, HIGH);
	digitalWrite(controllerClockPin, HIGH);
	strip->begin();
	strip->show();
	pinMode(lcd1Pin, OUTPUT);
	digitalWrite(lcd1Pin, HIGH);
	pinMode(lcd2Pin, OUTPUT);
	digitalWrite(lcd2Pin, HIGH);
	lcd->begin(9600);
	lcd->setLCD(1);
	lcd->print(" Select a Game  ");
	lcd->print("<"+gameNames[curGame]+">");

	lcd->write(209); // 1/32 note
	lcd->write(216); // 4th scale
	lcd->write(223); // C note
	lcd->write(224); // C# note
	lcd->write(225); // D note
	lcd->write(226); // D# note
	lcd->write(227); // E note
	lcd->write(228); // F note
	lcd->write(210);
	lcd->write(223);
	lcd->write(217); // 5th scale
	lcd->write(211);
	lcd->write(223);
	lcd->write(218); // 6th scale
	lcd->write(211);
	lcd->write(223);

}

void loop() {
	controller->controllerRead();
	if(paused && controller->buttonPressed(controller->BUTTON_LEFT) &&
			!controller->buttonHandled(controller->BUTTON_LEFT)){
		controller->handleButton(controller->BUTTON_LEFT);
		lcd->setLCD(1);
		lcd->write(209); // 1/32 note
		lcd->write(216); // 4th scale
		lcd->write(223); // C note
		if(displayedGame==0){
			displayedGame = (sizeof(gameNames)/sizeof(String)) - 1;
		}else{
			displayedGame=(displayedGame-1)%(sizeof(gameNames)/sizeof(String));
		}
		lcd->print(displayedGame);
		lcd->write(12); // Clear
		lcd->print("Select / Unpause");
		lcd->print("<"+gameNames[displayedGame]+">");
	}
	if(paused && controller->buttonPressed(controller->BUTTON_RIGHT) &&
			!controller->buttonHandled(controller->BUTTON_RIGHT)){
		controller->handleButton(controller->BUTTON_RIGHT);
		lcd->setLCD(1);
		lcd->write(209); // 1/32 note
		lcd->write(216); // 4th scale
		lcd->write(223); // C note
		displayedGame=(displayedGame+1)%(sizeof(gameNames)/sizeof(String));
		lcd->print(displayedGame);
		lcd->write(12); // Clear
		lcd->print("Select / Unpause");
		lcd->print("<"+gameNames[displayedGame]+">");
	}
	if(controller->buttonPressed(controller->BUTTON_START) && !controller->buttonHandled(controller->BUTTON_START)){
		lcd->setLCD(1);
		controller->handleButton(controller->BUTTON_START);
		paused = !paused;
		if(!paused){
			if(displayedGame!=curGame || currentGame==NULL){
				curGame = displayedGame;
				delete currentGame;
				switch(displayedGame){
				case 0:
					currentGame = new Tetris(controller,strip,lcd);
					break;
				case 1:
					currentGame = new MegaMaze(controller,strip,lcd);
					break;
				case 2:
					currentGame = new Snake(controller,strip,lcd);
					break;
				case 3:
					currentGame = new ConnectFour(controller,strip,lcd);
					break;
				case 4:
					currentGame = new GameOfLife(controller,strip,lcd);
					break;
				case 5:
					currentGame = new Visualizer(controller,strip,lcd);
					break;
				case 6:
					currentGame = new Flashlight(controller,strip,lcd);
					break;
				case 7:
					currentGame = new Rainbow(controller,strip,lcd);
					break;
				}
			}else{
				currentGame->resume();
			}
		}
		if(paused){
			lcd->print("Select / Unpause");
			lcd->print("<"+gameNames[curGame]+">");
		}
	}
	if(paused){
		for(int i=0;i<200;i++){
			strip->setPixelColor(i, 0x0);
		}
		int redPixels[] = {11,12,13,14,15,27,33,47,51,52,53,54,55};
		for(int i=0;i<((int)sizeof(redPixels)/2);i++){
			strip->setPixelColor(redPixels[i],0xFF0000);
		}
		int greenPixels[] = {64,65,66,67,68,71,73,75,84,86,88,91,93,95};
		for(int i=0;i<((int)sizeof(greenPixels)/2);i++){
			strip->setPixelColor(greenPixels[i],0x00FF00);
		}
		int bluePixels[] = {104,105,106,107,108,112,126,134,144,145,146,147,148};
		for(int i=0;i<((int)sizeof(bluePixels)/2);i++){
			strip->setPixelColor(bluePixels[i],0x0000FF);
		}
		int yellowPixels[] = {151,152,153,154,164,175,185,186,187,188};
		for(int i=0;i<((int)sizeof(yellowPixels)/2);i++){
			strip->setPixelColor(yellowPixels[i],0xFFFF00);
		}
		int whitePixels[] = {17,22,37,42,57,62,77,82,97,98,99,100,101,102,117,122,137,142,157,162,177,182};
		for(int i=0;i<((int)sizeof(whitePixels)/2);i++){
			strip->setPixelColor(whitePixels[i],0xFFFFFF);
		}
		strip->show();
	}else{
		currentGame->run();
	}
}
