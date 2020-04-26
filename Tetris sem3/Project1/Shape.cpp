#include "Shape.h"


void Shape::move(int dx, int dy) {
	x += dx;
	y += dy;
}

void Shape::rotate() {
	if (angle < 3) {
		angle += 1;
	}
	else {
		angle = 0;
	}
}




Shape::Shape()
{
	x = (10 / 2) - (4 / 2);
	y = 0;
	angle = 0;
}


Shape::~Shape()
{
}
