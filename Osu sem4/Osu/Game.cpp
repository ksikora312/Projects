#include "Game.h"

void Game::playBackgroundMusic() {
	using namespace std::literals::chrono_literals;

	if (background_music.openFromFile("sounds/background.wav"))
	background_music.setLoop(true);
	background_music.play();
	bool pom = true;
	while (pom) {
		if (!isRunning) {
			background_music.stop();
			pom = false;
		}
		std::this_thread::sleep_for(500ms);
	}
}

Game::Game(std::string name) :window(sf::VideoMode(1920, 1080), name, sf::Style::Fullscreen), generator(1, 7, 50, window.getSize().x - 80, 50, window.getSize().y - 80), player(window.getSize()), scores(0, player.getHp()),
	music_thread(&Game::playBackgroundMusic, this){

	//"Easy (1 target at once)", "Normal (2 targets at once)", "Hard (3 targets at once)", "Highscores", "Exit"

	lost = false;

	texts.push_back("Easy (1 target at once)");
	texts.push_back("Normal (2 targets at once)");
	texts.push_back("Hard (3 targets at once)");
	texts.push_back("Highscores");
	texts.push_back("Exit");


	Scores::fetchHighscores(highscores);
	highscores_menu.setSettings(highscores, false);

	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	
	menu.setSettings(texts);

	isRunning = true;

	int difficulty = -1;
	while (difficulty < 0 && isRunning) {
		switch (menu.drawMenuStartGame(window)) { 
		case 0:
			difficulty = 1;
			break;
		case 1:
			difficulty = 2;
			break;
		case 2:
			difficulty = 3;
			break;
		case 3:
			highscores_menu.drawMenuStartGame(window);
			break;
		case 4:
			isRunning = false;
			window.close();
			music_thread.join();
			break;
		default:
			break;
		}
	}

	//load sounds
	if (!(buffer_hit.loadFromFile("sounds/hit.wav") || buffer_miss.loadFromFile("sounds/miss.wav")))
		window.close();
	//set sounds
	buffer_miss.loadFromFile("sounds/miss.wav");
	sound_hit.setBuffer(buffer_hit);
	sound_miss.setBuffer(buffer_miss);

	
	score = 0;
	in_row = false;
	in_row_counter = 0;

	for (int i = 0; i < difficulty; i++) {
		double choice = generator.targetType();
		if (choice < 0.05)
			targets.push_back(new HealingTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
		else if(choice < 0.07)
			targets.push_back(new BonusAimTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
		else
			targets.push_back(new NormalTarget(generator.generate(), generator.generate_x(), generator.generate_y(), generator.generate_wsp()));	
	}

	//start game clock, and set the whole game time
	game_session_time = sf::seconds(100);
	clock.restart();

}



void Game::play() {
	while (isRunning) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				isRunning = false;
				window.close();
				music_thread.join();
				break;
			case sf::Event::MouseMoved:
				player.move();
				//std::cout << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << std::endl;
				break;
			case sf::Event::MouseButtonReleased:
				switch (event.key.code) {
				case sf::Mouse::Left:
					checkForCollisions();
					break;
				}
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					isRunning = false;   // poki co konczy gre, do zmiany w przyszlosci
					window.close();
					music_thread.join();
					break;
				}
			}
		}
		window.clear();
		for (int i = 0; i < targets.size(); i++) {
			if (targets[i]->timed()) {
				sound_miss.play();
				delete targets[i];
				targets.erase(targets.begin() + i);

				//generowanie nowego obiektu
				double choice = generator.targetType();
				if (choice < 0.05)
					targets.push_back(new HealingTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				else if (choice < 0.07)
					targets.push_back(new BonusAimTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				else
					targets.push_back(new NormalTarget(generator.generate(), generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				//koniec generowania

				in_row = false; //zmienna mowi o tym, czy klikamy w serii - jesli tak, to wieksza ilosc punktow za klik
				in_row_counter = 0;
				if (player.miss()) {
					lost = true;
					break;
				}
				continue;
			}
			else if (targets[i]->isHit()) {
				sound_hit.play();
				delete targets[i];
				targets.erase(targets.begin() + i);

				//generowanie nowego obiektu
				double choice = generator.targetType();
				if (choice < 0.05)
					targets.push_back(new HealingTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				else if (choice < 0.07)
					targets.push_back(new BonusAimTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				else
					targets.push_back(new NormalTarget(generator.generate(), generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
				//koniec generowania

				continue;
			}
			window.draw(targets[i]->drawTarget(window));  //target + border
		}
		if (lost || (game_session_time - clock.getElapsedTime()).asMilliseconds() <= 0) {
			bool resp = true;
			if (score > highscores[9].score) {
				if (!menu.endGameWithSave(window, highscores, score, !lost)) {
					window.close();
					isRunning = false;
					resp = false;
					music_thread.join();
				}
				else
					newGame();
			}
			else {
				if (!menu.endGameWithoutSave(window, score, !lost)) {
					window.close();
					isRunning = false;
					resp = false;
					music_thread.join();
				}
				else
					newGame();
			}
		}

		if (player.isAimBonus())
			player.bonusSet(targets[0]->getPosition());
		scores.setAimBonusTime(player.getBonusTimeLeft());
		scores.setGameTimeLeft(game_session_time - clock.getElapsedTime());
		scores.setScore(score);
		scores.setHp(player.getHp());
		scores.drawScores(window);
		window.draw(player);
		window.display();
		//sf::sleep(sf::milliseconds(50));
	}
}


Game::~Game() {
	int t1 = 0;
	for (int i = 0; i < targets.size(); i++) {
		delete targets[i];
		t1++;
	}
}


void Game::checkForCollisions() {
	int player_x = player.getPosition().x;
	int player_y = player.getPosition().y;
	int player_radius = player.getDiameter() / 2;
	player_x += player_radius;
	player_y += player_radius;
	for (int i = 0; i < targets.size(); i++) {
		int target_radius = targets[i]->getRadius();
		int target_x = targets[i]->getPosition().x + target_radius;
		int target_y = targets[i]->getPosition().y + target_radius;
		if (CircleCollisionDetector::check(player_x, player_y, player_radius, target_x, target_y, target_radius)) {
			in_row = true;
			in_row_counter++;
			targets[i]->hit(player);
			//player.hit(); zmiana - polimorfizm
			if (in_row) {
				score = score + in_row_counter * 1;
			}
			else {
				score++;
			}
		}
	}
	scores.setScore(score);
}

void Game::newGame() {
	//clear targers from last game
	for (int i = targets.size() - 1; i >= 0; i--) {
		delete targets[i];
		targets.erase(targets.begin() + i);
	}

	highscores_menu.setSettings(highscores, false);
	int difficulty = -1;
	while (difficulty < 0 && isRunning) {
		switch (menu.drawMenuStartGame(window)) {
		case 0:
			difficulty = 1;
			break;
		case 1:
			difficulty = 2;
			break;
		case 2:
			difficulty = 3;
			break;
		case 3:
			highscores_menu.drawMenuStartGame(window);
			break;
		case 4:
			isRunning = false;
			window.close();
			music_thread.join();
			break;
		default:
			break;
		}
	}

	score = 0;
	in_row = false;
	in_row_counter = 0;
	lost = false;

	for (int i = 0; i < difficulty; i++) {
		double choice = generator.targetType();
		if (choice < 0.05)
			targets.push_back(new HealingTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
		else if (choice < 0.07)
			targets.push_back(new BonusAimTarget(generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
		else
			targets.push_back(new NormalTarget(generator.generate(), generator.generate_x(), generator.generate_y(), generator.generate_wsp()));
	}

	player.reset();
	//restart clock from last game
	clock.restart();
}