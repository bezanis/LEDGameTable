#include "LCD.h"

LCD::LCD(int lcd1Pin, int lcd2Pin) {
	lcd1 = new SoftwareSerial(255,lcd1Pin);
	lcd2 = new SoftwareSerial(255,lcd2Pin);
	curLCD = 1;
	this->setLCD(curLCD);
}

void LCD::begin(int baud){
	lcd1->begin(baud);
	lcd2->begin(baud);
}

void LCD::write(int c){
	if(curLCD==1){
		lcd1->write(c);
	}else if(curLCD==2){
		lcd2->write(c);
	}
}

void LCD::print(String s){
	if(curLCD==1){
		lcd1->print(s);
	}else if(curLCD==2){
		lcd2->print(s);
	}
}

void LCD::print(int i){
	if(curLCD==1){
		lcd1->print(i);
	}else if(curLCD==2){
		lcd2->print(i);
	}
}

void LCD::print(unsigned long l){
	if(curLCD==1){
		lcd1->print(l);
	}else if(curLCD==2){
		lcd2->print(l);
	}
}

void LCD::print(char c){
	if(curLCD==1){
		lcd1->print(c);
	}else if(curLCD==2){
		lcd2->print(c);
	}
}

void LCD::setLCD(int i){
	curLCD = i;
	lcd1->write(12); // Clear
	lcd2->write(12); // Clear
	lcd1->write(22); // Hide cursor
	lcd2->write(22); // Hide cursor

	if(curLCD==1){
		lcd1->write(17); // Turn backlight on
		lcd2->write(18); // Turn backlight off
	}else if(curLCD==2){
		lcd1->write(18); // Turn backlight off
		lcd2->write(17); // Turn backlight on
	}
}
