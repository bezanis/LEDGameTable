/*
 Parts of this code were taken from Piccolo
 https://github.com/adafruit/piccolo/blob/master/Piccolo/Piccolo.pde
 */

#include <Visualizer.h>
#define MIC_PIN   A1  // Microphone is attached to this analog pin

Visualizer::Visualizer(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	visualizerType=0;
	volumeCurPos=0;
	for(int i=0;i<20;i++){
		volumePositions[i]=0;
	}
}

Visualizer::~Visualizer(){
}

void Visualizer::run(){
	const unsigned int sampleWindow = 10; // Sample window width in mS (50 mS = 20Hz)
	const unsigned int visualizerTypes=2; //2 Total visualizer types

	controller->controllerRead();
	if(controller->buttonPressed(controller->BUTTON_LEFT) &&
			!controller->buttonHandled(controller->BUTTON_LEFT)){
		controller->handleButton(controller->BUTTON_LEFT);
		if(visualizerType==0){
			visualizerType = visualizerTypes - 1;
		}else{
			visualizerType=(visualizerType-1)%visualizerTypes;
		}
	}
	if(controller->buttonPressed(controller->BUTTON_RIGHT) &&
			!controller->buttonHandled(controller->BUTTON_RIGHT)){
		controller->handleButton(controller->BUTTON_RIGHT);
		visualizerType=(visualizerType+1)%visualizerTypes;
	}

	unsigned int sample;
	unsigned long startMillis= millis();  // Start of sample window
	unsigned int peakToPeak = 0;   // peak-to-peak level
	unsigned int signalMax = 0;
	unsigned int signalMin = 1024;
	// collect data for 50 mS
	while (millis() - startMillis < sampleWindow){
		sample = analogRead(MIC_PIN);
		if (sample < 1024){  // toss out spurious readings
			if (sample > signalMax){
				signalMax = sample;  // save just the max levels
			}else if (sample < signalMin){
				signalMin = sample;  // save just the min levels
			}
		}
	}
	peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
	volumePositions[volumeCurPos] = (int) ((peakToPeak * 11.0) / 1024);  // convert to volts

	const unsigned long colors[10] ={0x3d01a4,0x0247fe,0x0392ce,0x66b032,0xd0ea2b,0xfefe33,0xfabc02,0xfb9902,0xfd5308,0xfe2712};

	switch(visualizerType){
	case 0:
		//Color Visualizer
		for(int i=0;i<20;i++){
			for(int j=0;j<10;j++){
				strip->setPixelColor(j,i,colors[volumePositions[volumeCurPos]]);
			}
		}
		break;
	case 1:
		//Timeline visualizer
		for(int i=0;i<20;i++){
			for(int j=0;j<10;j++){
				if(volumePositions[i]>j){
					strip->setPixelColor(j,(19+i-volumeCurPos)%20,colors[j]);
				}else{
					strip->setPixelColor(j,(19+i-volumeCurPos)%20,0x000000);
				}
			}
		}
		break;
	}

	strip->show();
	updateDisplay();
	volumeCurPos=(volumeCurPos+1)%20;
}

void Visualizer::resume(){
}

void Visualizer::updateDisplay(){
	lcd->write(12); // Clear
	lcd->print(volumePositions[volumeCurPos]);
}
