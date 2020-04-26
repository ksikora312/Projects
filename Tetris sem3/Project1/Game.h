#ifndef GAME_H
#define GAME_H
#include "WelcomeScreen.h"
#include "PauseScreen.h"
#include "Matrixx.h"
#include "I_Shape.h"
#include "T_Shape.h"
#include "J_Shape.h"
#include "L_Shape.h"
#include "O_Shape.h"
#include "S_Shape.h"
#include "Z_Shape.h"
#include <random>
#include <chrono>
class Game
{
	Shape *shape;
	Matrixx matrix;
	WelcomeScreen welcome;
	PauseScreen pause;
	sf::RenderWindow window;
	std::string filename;
	bool running;
	int score;
	bool fallen;
	sf::Clock clock;
	sf::Time frameTime;

	//losowanie
	unsigned seed;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
	//koniec losowania

	Game(const Game &);
	Game &operator=(const Game &);

	Shape *chooseShape();
	void check(Shape *sh);
	int state_welcome, state_pause;
	void loadGame(sf::String name);
public:
	bool run();
	Game();
	~Game();
};

#endif