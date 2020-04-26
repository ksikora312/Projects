#include "S_Shape.h"


bool S_Shape::isShape(int x, int y) {
	return shape[angle][x + y * 4] == '*';
}

void S_Shape::draw(sf::RenderWindow &window) {
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


S_Shape::S_Shape() :Shape()
{
	r = 0;
	g = 0;
	b = 255;
}


S_Shape::~S_Shape()
{
}

S_Shape* S_Shape::clone() {
	return new S_Shape(*this);
}
