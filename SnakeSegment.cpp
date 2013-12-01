#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int inX, int inY, SnakeSegment * nextSegmentIn){
	x = inX;
	y = inY;
	nextSegment = nextSegmentIn;
}
SnakeSegment * SnakeSegment::getNextSegment(){
	return nextSegment;
}
void SnakeSegment::setNextSegment(SnakeSegment * nextSegmentIn){
	nextSegment = nextSegmentIn;
}
int SnakeSegment::getX(){
	return x;
}
int SnakeSegment::getY(){
	return y;
}
void SnakeSegment::setPosition(int inX, int inY){
	x = inX;
	y = inY;
}
void SnakeSegment::setX(int inX){
	x = inX;
}
void SnakeSegment::setY(int inY){
	y = inY;
}
