#include "Strobe.h"

Strobe::Strobe(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	strobeSpeed=25;
}

Strobe::~Strobe(){
}

void Strobe::run(){
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			strip->setPixelColor(j,i,(millis()%(strobeSpeed*2)>=strobeSpeed)?0xFFFFFF:0x000000);
		}
	}
	strip->show();
}

void Strobe::resume(){
}
