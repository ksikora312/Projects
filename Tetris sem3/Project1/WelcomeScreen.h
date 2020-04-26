#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "List.h"
#define ITEMS 4

class WelcomeScreen
{
	sf::String filename;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[ITEMS];
	sf::Text score[10];
	List highscores;
	//std::vector <player> highscores;

public:

	int highscoresMenu(sf::RenderWindow &window);
	static bool compare(player p1, player p2);
	void addHighscore(std::string nam, int scor);
	bool endGame(sf::RenderWindow &window, int score);
	bool checkIfGoodEnough(int scor);
	void moveUp();
	void moveDown();
	int drawMenu(sf::RenderWindow &window);
	WelcomeScreen(float width = 720/2, float height = 720);
	~WelcomeScreen();
};

#endif