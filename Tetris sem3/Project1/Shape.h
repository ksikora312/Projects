#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <SFML\Graphics.hpp>

class Shape
{
public:
	int r, g, b;
	int angle;
	int x;
	int y;
	inline int getX() {
		return x;
	}
	inline int getY() {
		return y;
	}
	inline int getR() {
		return r;
	}
	inline int getG() {
		return g;
	}
	inline int getB() {
		return b;
	}
	void move(int dx, int dy);
	void rotate();
	virtual Shape* clone() = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual bool isShape(int x, int y) = 0;
	Shape();
	virtual ~Shape();
};

#endif