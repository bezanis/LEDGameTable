#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point();
	Point(int inX, int inY);
	void setPosition(int inX, int inY);
	void setX(int inX);
	void setY(int inY);
	int getX();
	int getY();
private:
	int x;
	int y;
};

#endif
