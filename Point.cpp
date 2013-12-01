#include "Point.h"

Point::Point() {
	x=0;
	y=0;
}

Point::Point(int inX, int inY) {
	x=inX;
	y=inY;
}

int Point::getX(){
	return x;
}

int Point::getY(){
	return y;
}

void Point::setPosition(int inX, int inY){
	x = inX;
	y = inY;
}

void Point::setX(int inX){
	x = inX;
}

void Point::setY(int inY){
	y = inY;
}
