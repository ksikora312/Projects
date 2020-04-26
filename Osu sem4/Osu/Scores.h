#ifndef SCORES_H
#define SCORES_H
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>



struct scor {
	std::string name;
	int score;
};



class Scores
{
	int score;
	const int max_hp = 100;
	int hp;

	bool draw_bonus_time;

	sf::Font font;
	sf::Text text_score;
	sf::Text text_aim_bonus;
	sf::Text text_game_time_left;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarOutline;

	std::vector <std::string> highscores;

public:
	
	Scores(int score, int hp);
	void drawScores(sf::RenderWindow &window);
	void setHp(int hp_);
	void setScore(int s);
	void setAimBonusTime(int32_t t);
	void setGameTimeLeft(sf::Time t);

	static bool comp(scor &s1, scor &s2);

	static void fetchHighscores(std::vector <scor> &tab);
	static void saveHighscores(std::vector <scor> &tab);
};

#endif

