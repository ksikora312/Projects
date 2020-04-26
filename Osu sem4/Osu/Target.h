#ifndef TARGET_H
#define TARGET_H
#include "SFML/Graphics.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include "Player.h"
class  Target :public sf::Sprite
{
protected:
	int pos_x;
	int pos_y;
	int border_radius;
	float factor;


	sf::CircleShape border;

	sf::Texture red;
	sf::Texture blue;
	sf::Texture green;
	sf::Texture yellow;
	sf::Texture cyan;
	sf::Texture orange;
	sf::Texture violet;
	sf::Texture heart;
	sf::Texture aim;



	bool scored;
	bool timed_down;


	const static int scale = 2;
	const static int window_x = 1920;
	const static int window_y = 1080;
	const int texture_width = 100;
	const int texture_height = 100;



public:
	Target() = default;
	Target(int color_number, int target_pos_x, int target_pos_y, float wsp);
	sf::Sprite drawTarget(sf::RenderWindow &window);
	int getRadius();

	virtual void hit(Player &player) = 0;
	virtual bool isHit() = 0;
	virtual bool timed() = 0;
	
};

#endif
