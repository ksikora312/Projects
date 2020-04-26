#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
class Player :public sf::Sprite
{

	int health;
	int x_pos;
	int y_pos;
	int texture_size_x;
	int texture_size_y;

	sf::Vector2f windowSize;
	sf::Texture texture;

	bool aim_bonus;

	sf::Clock clock;


public:
	Player(sf::Vector2u s);
	sf::Vector2f getCoordinates();
	int getDiameter();
	int getHp();
	void move();
	bool miss();
	void hit(int val);
	bool isAimBonus();
	void setAimBonus();

	int32_t getBonusTimeLeft();

	void bonusSet(sf::Vector2f pos);
	
	void reset();
};


#endif

