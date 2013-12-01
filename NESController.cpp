#include "NESController.h"

int latchPin; // controller latch pin - Orange
int clockPin; // controller clock pin - Red
int dataPin;  // controller data in pin - Yellow

byte handled;
byte controllerData;;
byte controllerDataLast;

NESController::NESController(){
}

NESController::NESController(int controllerLatchPin,int controllerClockPin,int controllerDataPin){
	latchPin = controllerLatchPin;
	clockPin = controllerClockPin;
	dataPin = controllerDataPin;
	handled=255;
	controllerData=255;
	controllerDataLast=255;
}

bool NESController::buttonPressed(byte button) {
	return (controllerData & button) ? false : true;
}


bool NESController::buttonHandled(byte button){
	return (handled & button) ? true : false;
}

void NESController::handleButton(byte button){
	handled = handled|button;
}

void NESController::controllerRead() {
	controllerDataLast = controllerData;
	controllerData = 0;
	digitalWrite(latchPin, LOW);
	digitalWrite(clockPin, LOW);
	digitalWrite(latchPin, HIGH);
	delayMicroseconds(2);
	digitalWrite(latchPin, LOW);
	controllerData = digitalRead(dataPin);
	for (int i = 1; i <= 7; i++) {
		digitalWrite(clockPin, HIGH);
		delayMicroseconds(2);
		controllerData = controllerData << 1;
		controllerData = controllerData + digitalRead(dataPin);
		delayMicroseconds(4);
		digitalWrite(clockPin, LOW);
	}
	handled = (handled & (~((~controllerData)&controllerDataLast))) | controllerData ;
}
