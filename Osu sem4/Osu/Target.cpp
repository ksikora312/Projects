#include "Target.h"


Target::Target(int color_number, int target_pos_x, int target_pos_y, float wsp) {


	pos_x = target_pos_x;
	pos_y = target_pos_y;
	factor = wsp;

	// zmienna mowiaca o tym, czy target zostal trafiony
	scored = false;
	// zmienna mowiaca o tym, czy czas sie nie skonczyl (na trafienie poszczegolnego targetu
	timed_down = false;

	//factor should be 1.0 - 2.0
	border_radius = factor * (texture_width / 2);

	setPosition(pos_x, pos_y);

	border.setPosition(pos_x + texture_width / 4, pos_y + texture_height / 4);
	border.setOrigin(border_radius, border_radius);

	border.setRadius(border_radius);
	border.setFillColor(sf::Color(0, 0, 0, 0));
	border.setOutlineThickness(2);







	int number = color_number;

	switch (number) {
	case 1:
		red.loadFromFile("sprites/red.png");
		setTexture(red);
		border.setOutlineColor(sf::Color::Red);
		break;
	case 2:
		blue.loadFromFile("sprites/blue.png");
		setTexture(blue);
		border.setOutlineColor(sf::Color::Blue);
		break;
	case 3:
		green.loadFromFile("sprites/green.png");
		setTexture(green);
		border.setOutlineColor(sf::Color::Green);
		break;
	case 4:
		yellow.loadFromFile("sprites/yellow.png");
		setTexture(yellow);
		border.setOutlineColor(sf::Color::Yellow);
		break;
	case 5:
		cyan.loadFromFile("sprites/cyan.png");
		setTexture(cyan);
		border.setOutlineColor(sf::Color::Cyan);
		break;
	case 6:
		orange.loadFromFile("sprites/orange.png");
		setTexture(orange);
		border.setOutlineColor(sf::Color(255, 165, 0, 255));
		break;
	case 7:
		violet.loadFromFile("sprites/violet.png");
		setTexture(violet);
		border.setOutlineColor(sf::Color(138, 43, 226, 255));
		break;
	case 100:
		heart.loadFromFile("sprites/heart.png");
		setTexture(heart);
		border.setOutlineColor(sf::Color::Red);
		break;
	case -1:
		aim.loadFromFile("sprites/aim.png");
		setTexture(aim);
		border.setOutlineColor(sf::Color(245, 245, 245, 255));
		break;
	}

	setScale(1 / float(scale), 1 / float(scale));

}

sf::Sprite Target::drawTarget(sf::RenderWindow &window) {

	if (border_radius == texture_width / 4) {
		timed_down = true;
	}
	//std::cout << texture_width << " <- tex width     border radius -> " << border_radius << std::endl;
	setPosition(pos_x, pos_y);
	window.draw(border);
	border_radius -= 1;
	border.setRadius(border_radius);
	border.setOrigin(border_radius, border_radius);
	return *this;
}



/*
void Target::hit() {
	scored = true;
}

bool Target::isHit() {
	return scored;
}

bool Target::timed() {
	return timed_down;
}

*/

int Target::getRadius() {
	return texture_width / scale / 2;
}
