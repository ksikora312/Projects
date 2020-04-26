#include "T_Shape.h"




bool T_Shape::isShape(int x, int y) {
	return shape[angle][x + y * 4] == '*';
}

void T_Shape::draw(sf::RenderWindow &window) {
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


T_Shape::T_Shape() :Shape()
{
	r = 192;
	g = 192;
	b = 192;
}


T_Shape::~T_Shape()
{
}

T_Shape* T_Shape::clone() {
	return new T_Shape(*this);
}
