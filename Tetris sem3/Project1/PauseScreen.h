#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H
#include <SFML/Graphics.hpp>
#include <string>
#define ITEMS 3
class PauseScreen
{
	sf::String filename;
	sf::Text filenameText;
	sf::Text prompt;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[ITEMS];
	sf::Text score;
public:
	void showScore(sf::RenderWindow &win, int sc);
	sf::String saveScreen(sf::RenderWindow &win);
	void moveUp();
	void moveDown();
	int drawMenu(sf::RenderWindow &window);
	PauseScreen(float width = 720 / 2, float height = 720);
	~PauseScreen();
};

#endif