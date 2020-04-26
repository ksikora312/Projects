#ifndef WELCOME_H
#define WELCOME_H
#include "SFML/Graphics.hpp"
#include "Scores.h"
#include "Scores.h"

#include <regex>
class WelcomeScreen
{
	sf::Text *text;
	sf::Font font;
	sf::Texture background_tex;
	sf::Sprite background;

	int items;
	int selected_index;

	void moveUp();
	void moveDown();

	bool selectable;



public:
	WelcomeScreen() = default;
	WelcomeScreen(int items_, std::string texts[], bool selectable_ = true);
	int drawMenuStartGame(sf::RenderWindow &window);
	void setSettings(std::vector <std::string> texts, bool selectable_ = true);
	void setSettings(std::vector <scor> texts, bool selectable_ = true);
	bool endGameWithoutSave(sf::RenderWindow &window, int score, bool timed);
	bool endGameWithSave(sf::RenderWindow &window, std::vector <scor> &highscores, int score, bool timed);
};


#endif

