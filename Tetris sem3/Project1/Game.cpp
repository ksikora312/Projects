#include "Game.h"



Game::Game() :window(sf::VideoMode(720 / 2, 760), "Tetris")
{
	bool loaded = false;
	while (window.isOpen() && !running) {
		state_welcome = welcome.drawMenu(window);
		switch (state_welcome) {
		case 0:
			running = true;
			break;
		case 1:
			filename = pause.saveScreen(window);
			running = matrix.loadFromFile(filename, score);
			loaded = running;
			break;
		case 2:
			if (welcome.highscoresMenu(window) == 1)
				running = false;
			break;
		case 3:
			running = false;
			window.close();
			break;
		}
	}
	if(!loaded)
		score = 0;
	fallen = false;
	frameTime = sf::milliseconds(200);
	shape = new I_Shape();
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
	std::uniform_int_distribution<int> dist(0, INT_MAX);
	distribution = dist;
}


Game::~Game()
{
	window.close();
}

void Game::loadGame(sf::String name) {
	//needs to be addedd
}

bool Game::run() {

	if (fallen)
		clock.restart();

	window.clear();
	if (running) {
		matrix.drawMatrix(window);
		shape->draw(window);
		sf::Event event;
		while (window.pollEvent(event)) {
			bool shouldBeDeleted = false;
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				running = false;
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Left:
				{
					Shape *temp = shape->clone();
					shouldBeDeleted = true;
					temp->move(-1, 0);
					if (!matrix.collision(temp)) {
						delete shape;
						shape = temp;
						shouldBeDeleted = false;
					}
					if (shouldBeDeleted) {
						delete temp;
					}
					break;
				}
				case sf::Keyboard::Right:
				{
					Shape *temp = shape->clone();
					shouldBeDeleted = true;
					temp->move(1, 0);
					if (!matrix.collision(temp)) {
						delete shape;
						shape = temp;
						shouldBeDeleted = false;
					}
					if (shouldBeDeleted) {
						delete temp;
					}
						break;
				}
				case sf::Keyboard::Up:
				{
					Shape *temp = shape->clone();
					shouldBeDeleted = true;
					temp->rotate();
					if (!matrix.collision(temp)) {
						delete shape;
						shape = temp;
						shouldBeDeleted = false;
					}
					if (shouldBeDeleted) {
						delete temp;
					}
					break;
				}
				case sf::Keyboard::Down:
				{
					Shape *temp = shape->clone();
					shouldBeDeleted = true;
					temp->move(0, 1);
					if (!matrix.collision(temp)) {
						delete shape;
						shape = temp;
						shouldBeDeleted = false;
					}
					if (shouldBeDeleted) {
						delete temp;
					}
					break;
				}
				case sf::Keyboard::Escape:
					state_pause = pause.drawMenu(window);
					if (state_pause == 0) {
						window.display();
						break;
					}
					if (state_pause == 1) {
						filename = pause.saveScreen(window);
						matrix.saveToFile(filename, score);
						window.close();
						running = false;
						return false;
					}
					if (state_pause == 2) {
						window.close();
						running = false;
						return false;
					}
				}
			}
		}

		sf::Time t = clock.getElapsedTime();
		if (t.asMilliseconds() >= frameTime.asMilliseconds()) {
			Shape *temp = shape->clone();
			temp->move(0, 1);
			check(temp);
			fallen = true;
		}
		else
			fallen = false;
		pause.showScore(window, score);
		window.display();
	}

	return running;
	
}

void Game::check(Shape *sh) {
	if (matrix.collision(sh)) {
		matrix.joinAndScore(shape, score);
		delete sh;
		shape = chooseShape();
		if (matrix.collision(shape)) {
			running = welcome.endGame(window, score);
			if (running) {
				matrix = Matrixx();
				score = 0;
			}
		}
	}
	else {
		delete shape;
		shape = sh;
	}
}

Shape *Game::chooseShape() {

	Shape *shap = shape;
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::default_random_engine generator(seed);
	//std::uniform_int_distribution<int> distribution(0, INT_MAX);
	do {
	int number = distribution(generator);

		switch (number % 7) {
		case 0:
			shap = new I_Shape();
			break;
		case 1:
			shap = new J_Shape();
			break;
		case 2:
			shap = new L_Shape();
			break;
		case 3:
			shap = new O_Shape();
			break;
		case 4:
			shap = new S_Shape();
			break;
		case 5:
			shap = new T_Shape();
			break;
		case 6:
			shap = new Z_Shape();
			break;
		}
	} while (shap->r == shape->r && shap->g == shape->g && shap->b == shape->b);
	delete shape;
	return shap;
}