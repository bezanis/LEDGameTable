#ifndef SNAKESEGMENT_H_
#define SNAKESEGMENT_H_

class SnakeSegment {
public:
	SnakeSegment(int inX, int inY, SnakeSegment * nextSegmentIn);
	SnakeSegment * getNextSegment();
	void setNextSegment(SnakeSegment * nextSegmentIn);
	int getX();
	int getY();
	void setPosition(int x, int y);
	void setX(int x);
	void setY(int y);
private:
	int x;
	int y;
	SnakeSegment * nextSegment;
};

#endif /* SNAKESEGMENT_H_ */
