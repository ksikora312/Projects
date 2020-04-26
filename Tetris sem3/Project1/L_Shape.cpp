#include "L_Shape.h"


bool L_Shape::isShape(int x, int y) {
	return shape[angle][x + y * 4] == '*';
}

void L_Shape::draw(sf::RenderWindow &window) {
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


L_Shape::L_Shape() :Shape()
{
	r = 255;
	g = 255;
	b = 0;
}


L_Shape::~L_Shape()
{
}

L_Shape* L_Shape::clone() {
	return new L_Shape(*this);
}
