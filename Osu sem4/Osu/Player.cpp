#include "Player.h"


Player::Player(sf::Vector2u s) {
	texture.loadFromFile("sprites/circumference.png");
	setTexture(texture);
	setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	windowSize.x = s.x;
	windowSize.y = s.y;
	float scale = 0.5;
	setScale(scale, scale);

	texture_size_x = (texture.getSize().x / (1 / scale));
	texture_size_y = (texture.getSize().y / (1 / scale));

	health = 100;

	aim_bonus = false;

}

sf::Vector2f Player::getCoordinates() {
	sf::CircleShape crc;
	return sf::Vector2f(x_pos, y_pos);
}

int Player::getDiameter() {
	return texture_size_x;
}

void Player::move() {
	sf::Vector2i m_pos = sf::Mouse::getPosition();

	//jezeli wspolrzedna myszka x jest pomiedzy bokami (lewy, prawy) ekranu, to ustawiamy wsp x gracza
	if (m_pos.x + texture_size_x <= windowSize.x &&
		m_pos.x >= 0)
	{
		setPosition(sf::Mouse::getPosition().x, getPosition().y);
	}

	//jezeli wspolrzedna myszki y jest miedzy gora, a dolem ekranu, to ustawiamy wspolrzednia y gracza
	if (m_pos.y >= 0 &&
		m_pos.y + texture_size_y <= windowSize.y) {
		setPosition(getPosition().x, sf::Mouse::getPosition().y);
	}
}

bool Player::miss() {
	health -= 5;
	if (health <= 0) {
		return true;
	}
	return false;
}

int Player::getHp() {
	return health;
}

void Player::hit(int val) {
	health += val;
	if (health > 100) {
		health = 100;
	}
	else if (health < 0) {
		health = 0;
	}
}

bool Player::isAimBonus() {
	if (aim_bonus) {
		sf::Time temp = clock.getElapsedTime();
		if (temp >= sf::milliseconds(5000))
			aim_bonus = false;
	}
	return aim_bonus;
}

void Player::setAimBonus() {
	aim_bonus = true;
	clock.restart();
}

void Player::bonusSet(sf::Vector2f pos) {
	setPosition(pos.x + 12, pos.y + 12);
	sf::Mouse::setPosition(sf::Vector2i((int)pos.x, (int)pos.y));
}

int32_t Player::getBonusTimeLeft() {
	int32_t temp;
	if (aim_bonus) {
		temp = sf::milliseconds(5000).asMilliseconds() - clock.getElapsedTime().asMilliseconds();
	}
	else {
		temp = 0;
	}
	return temp;
}


void Player::reset() {
	health = 100;
	aim_bonus = false;
}