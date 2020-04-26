#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "NormalTarget.h"
#include "HealingTarget.h"
#include "BonusAimTarget.h"
#include <iostream>
#include "Generator.h"
#include "Scores.h"
#include "CircleCollisionDetector.h"
#include "WelcomeScreen.h"
#include <vector>
#include <thread>
class Game
{
	sf::RenderWindow window;
	bool isRunning = true;
	bool lost;


	sf::Time game_session_time;
	sf::Clock clock;

	Player player;
	Generator generator;
	Scores scores;
	WelcomeScreen menu;
	WelcomeScreen highscores_menu;

	sf::SoundBuffer buffer_hit;
	sf::Sound sound_hit;
	sf::SoundBuffer buffer_miss;
	sf::Sound sound_miss;

	sf::Music background_music;

	std::thread music_thread;

	std::vector <Target*> targets;

	int radius;

	int score;
	bool in_row;
	int in_row_counter;

	std::vector <std::string> texts;
	std::vector <scor> highscores;

	void playBackgroundMusic();

	void checkForCollisions();

	void newGame();

public:
	Game(std::string name);
	void play();
	~Game();
};


#endif