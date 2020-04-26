#include "Z_Shape.h"


bool Z_Shape::isShape(int x, int y) {
	return shape[angle][x + y * 4] == '*';
}

void Z_Shape::draw(sf::RenderWindow &window) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (isShape(i, j)) {
				sf::RectangleShape rect(sf::Vector2f(720 / 20 - 1, 720 / 20 - 1));
				rect.setFillColor(sf::Color(r, g, b));
				rect.setPosition(sf::Vector2f((i + x) * 720 / 2 / 10 + 1, (j + y) * 720 / 2 / 10 + 1));
				window.draw(rect);
			}
		}
	}
}


Z_Shape::Z_Shape() :Shape()
{
	r = 124;
	g = 252;
	b = 0;
}


Z_Shape::~Z_Shape()
{
}

Z_Shape* Z_Shape::clone() {
	return new Z_Shape(*this);
}
