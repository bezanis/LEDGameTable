#include "Flashlight.h"
//Rainbow color code grabbed from http://forum.arduino.cc/index.php/topic,8498.0.html

Flashlight::Flashlight(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	lightType = 0;
	lightColor = 0;
	phase = 0;
}

Flashlight::~Flashlight(){
}

void Flashlight::run(){
	const unsigned int lightTypes=4;

	controller->controllerRead();
	if(controller->buttonPressed(controller->BUTTON_LEFT) &&
			!controller->buttonHandled(controller->BUTTON_LEFT)){
		controller->handleButton(controller->BUTTON_LEFT);
		if(lightType==0){
			lightType = lightTypes - 1;
		}else{
			lightType=(lightType-1)%lightTypes;
		}
	}
	if(controller->buttonPressed(controller->BUTTON_RIGHT) &&
			!controller->buttonHandled(controller->BUTTON_RIGHT)){
		controller->handleButton(controller->BUTTON_RIGHT);
		lightType=(lightType+1)%lightTypes;
	}

	if(lightType==0){
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				strip->setPixelColor(j,i,0xFFFFFF);
			}
		}
		strip->show();
	}else if(lightType==1){
		phase=(phase+1)%2;
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				strip->setPixelColor(j,i,(phase==0x0?0:0xFFFFFF));
			}
		}
		strip->show();
	}else if(lightType==2){
		lightColor=(lightColor+2)%255;
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				strip->setPixelColor(j,i,lightColor*255*255 + lightColor*255 + lightColor);
			}
		}
		strip->show();
	}else if(lightType==3){
		lightColor=lightColor+8;
		if(lightColor>255){
			lightColor=lightColor%255;
			phase=(phase+1)%2;
		}
		int phaseColor = ((phase==0)?lightColor:(255-lightColor));
		long frameColor = ((long) phaseColor)*256*256 + ((long) phaseColor)*256 + ((long) phaseColor);
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				strip->setPixelColor(j,i,frameColor);
			}
		}
		strip->show();
	}
}

void Flashlight::resume(){
	lightColor=0;
}
