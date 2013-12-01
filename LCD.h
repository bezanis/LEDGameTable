#ifndef LCD_H_
#define LCD_H_

#include "SoftwareSerial.h"

class LCD {
public:
	LCD(int lcd1Pin, int lcd2Pin);
	void begin(int baud);
	void write(int code);
	void print(String s);
	void print(int i);
	void print(unsigned long l);
	void print(char c);
	void setLCD(int i);
private:
	SoftwareSerial * lcd1;
	SoftwareSerial * lcd2;
	int curLCD;
};

#endif
