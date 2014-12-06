#include <Rainbow.h>

Rainbow::Rainbow(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	resume();
	red=128;
	green=255;
	blue=0;
	colorMode=0;
}

Rainbow::~Rainbow(){
}

void Rainbow::run(){
	if(controller->buttonPressed(controller->BUTTON_LEFT) && !controller->buttonHandled(controller->BUTTON_LEFT)){
		controller->handleButton(controller->BUTTON_LEFT);
		colorMode--;
		if(colorMode<0){
			colorMode=2;
		}
	}
	if(controller->buttonPressed(controller->BUTTON_RIGHT) && !controller->buttonHandled(controller->BUTTON_RIGHT)){
		controller->handleButton(controller->BUTTON_RIGHT);
		colorMode++;
		if(colorMode>2){
			colorMode=0;
		}
	}
	if(colorMode==0){
		if(blue==255 && green==0 && red<255){
			red = min(255,red+1);
		}else if(green==255 && red>0 && blue==0){
			red = max(0,red-1);
		}else if(red==255 && blue==0 && green<255){
			green = min(255,green+1);
		}else if(blue==255 && green>0 && red==0){
			green = max(0,green-1);
		}else if(green==255 && red==0 && blue<255){
			blue = min(255,blue+1);
		}else if(red==255 && blue>0 && green==0){
			blue = max(0,blue-1);
		}
		for(int i=0;i<20;i++){
			for(int j=0;j<10;j++){
				uint32_t pixelColor = ((uint32_t)red)*0x10000+((uint32_t)green)*0x100+((uint32_t)blue)*0x1;
				strip->setPixelColor(j,i,pixelColor);
			}
		}
	}else if(colorMode==1){
		if(blue==255 && green==0 && red<255){
			red = min(255,red+5);
		}else if(green==255 && red>0 && blue==0){
			red = max(0,red-5);
		}else if(red==255 && blue==0 && green<255){
			green = min(255,green+5);
		}else if(blue==255 && green>0 && red==0){
			green = max(0,green-5);
		}else if(green==255 && red==0 && blue<255){
			blue = min(255,blue+5);
		}else if(red==255 && blue>0 && green==0){
			blue = max(0,blue-5);
		}
		int redTemp = red;
		int greenTemp = green;
		int blueTemp = blue;
		for(int i=0;i<20;i++){
			for(int j=0;j<10;j++){
				if(blueTemp==255 && greenTemp==0 && redTemp<255){
					redTemp = min(255,redTemp+5);
				}else if(greenTemp==255 && redTemp>0 && blueTemp==0){
					redTemp = max(0,redTemp-5);
				}else if(redTemp==255 && blueTemp==0 && greenTemp<255){
					greenTemp = min(255,greenTemp+5);
				}else if(blueTemp==255 && greenTemp>0 && redTemp==0){
					greenTemp = max(0,greenTemp-5);
				}else if(greenTemp==255 && redTemp==0 && blueTemp<255){
					blueTemp = min(255,blueTemp+5);
				}else if(redTemp==255 && blueTemp>0 && greenTemp==0){
					blueTemp = max(0,blueTemp-5);
				}
				uint32_t pixelColor = ((uint32_t)redTemp)*0x10000+((uint32_t)greenTemp)*0x100+((uint32_t)blueTemp);
				strip->setPixelColor(j,i,pixelColor);
			}
		}
	}else if(colorMode==2){
		if(blue==255 && green==0 && red<255){
			red = min(255,red+15);
		}else if(green==255 && red>0 && blue==0){
			red = max(0,red-15);
		}else if(red==255 && blue==0 && green<255){
			green = min(255,green+15);
		}else if(blue==255 && green>0 && red==0){
			green = max(0,green-15);
		}else if(green==255 && red==0 && blue<255){
			blue = min(255,blue+15);
		}else if(red==255 && blue>0 && green==0){
			blue = max(0,blue-15);
		}
		int redTemp = red;
		int greenTemp = green;
		int blueTemp = blue;
		for(int i=0;i<20;i++){
			for(int j=0;j<10;j++){
				if(blueTemp==255 && greenTemp==0 && redTemp<255){
					redTemp = min(255,redTemp+15);
				}else if(greenTemp==255 && redTemp>0 && blueTemp==0){
					redTemp = max(0,redTemp-15);
				}else if(redTemp==255 && blueTemp==0 && greenTemp<255){
					greenTemp = min(255,greenTemp+15);
				}else if(blueTemp==255 && greenTemp>0 && redTemp==0){
					greenTemp = max(0,greenTemp-15);
				}else if(greenTemp==255 && redTemp==0 && blueTemp<255){
					blueTemp = min(255,blueTemp+15);
				}else if(redTemp==255 && blueTemp>0 && greenTemp==0){
					blueTemp = max(0,blueTemp-15);
				}
				uint32_t pixelColor = ((uint32_t)redTemp)*0x10000+((uint32_t)greenTemp)*0x100+((uint32_t)blueTemp);
				strip->setPixelColor(j,i,pixelColor);
			}
		}
	}
	strip->show();
}

void Rainbow::resume(){
	//lcd->off(1);
}
