#include "WelcomeScreen.h"


int WelcomeScreen::drawMenu(sf::RenderWindow &window) {

	while (window.isOpen()) {
		window.clear();
		for (int i = 0; i < ITEMS; i++) {
			window.draw(menu[i]);
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					moveUp();
					break;
				case sf::Keyboard::Down:
					moveDown();
					break;
				case sf::Keyboard::Enter:
					window.clear();
					return selectedIndex;
					break;
				}
			}
		}
		window.display();
	}
	return selectedIndex;
}

void WelcomeScreen::moveUp() {
	if (selectedIndex > 0) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}

void WelcomeScreen::moveDown() {
	if (selectedIndex < ITEMS - 1) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}


WelcomeScreen::WelcomeScreen(float width, float height)
{
	if (!font.loadFromFile("orange.ttf")) {
		//error
	}

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Yellow);
		menu[0].setString("New game");
		menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, height / (ITEMS + 1) * 1));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Load game");
		menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, height / (ITEMS + 1) * 2));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Highscores");
		menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getLocalBounds().width / 2, height / (ITEMS + 1) * 3));

		menu[3].setFont(font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setString("Exit");
		menu[3].setPosition(sf::Vector2f(width / 2 - menu[3].getLocalBounds().width / 2, height / (ITEMS + 1) * 4));

		selectedIndex = 0;

		

		for (int i = 0; i < 10; i++) {
			player temp{ "-----------" , 0 };
			highscores += temp;
		}

		int licznik = 0;
		//inicjalizacja highscores
		std::ifstream plik("highscores.txt");
		if (plik) {
			player tmp;
			while ((plik >> tmp.name >> tmp.score) && licznik < 9) {
				highscores += tmp;
				tmp.name = "";
				tmp.score = 0;
				licznik++;
			}
			plik.close();
		}
		while (highscores > 10) {
			highscores.dropLast();
		}
}


WelcomeScreen::~WelcomeScreen()
{
	highscores.save("highscores.txt");
}

bool WelcomeScreen::compare(player p1, player p2) {
	return (p1.score > p2.score);
}


void WelcomeScreen::addHighscore(std::string nam, int scor) {

	std::string name = nam.substr(0, nam.size() - 1);
	player newPlayer{ name, scor };
	highscores += newPlayer;
	highscores.dropLast();

}



bool WelcomeScreen::checkIfGoodEnough(int scor) {
	return highscores.goodEnough(scor);
}


bool WelcomeScreen::endGame(sf::RenderWindow &window, int score) {
	sf::Text goodScore;
	sf::String name;
	sf::Text nameText;
	bool saveScore = checkIfGoodEnough(score);
	std::string scoreText;
	sf::Text end;
	end.setFont(font);
	end.setFillColor(sf::Color::Red);
	//obsluga endGame w zaleznosci czy score sie kwalifikuje do zapisania
	if (saveScore)
		scoreText = "End game! Score was: " + std::to_string(score);
	else
		scoreText = "End game! Score was: " + std::to_string(score) + ".\n Hit enter to play again";
	end.setString(scoreText);
	end.setPosition(sf::Vector2f(window.getSize().x / 2 - end.getLocalBounds().width / 2, window.getSize().y / (4) * 1));
	if (saveScore) {
		goodScore.setFont(font);
		goodScore.setFillColor(sf::Color::Cyan);
		goodScore.setString("Nice! Enter Your name: ");
		goodScore.setPosition(sf::Vector2f(window.getSize().x / 2 - goodScore.getLocalBounds().width / 2, window.getSize().y / (3) * 1));
		nameText.setFont(font);
		nameText.setFillColor(sf::Color::Cyan);
		nameText.setPosition(sf::Vector2f(window.getSize().x / 2 - goodScore.getLocalBounds().width / 2, window.getSize().y / 3 + 30));
	}


	while (window.isOpen()) {
		window.clear();
		window.draw(end);
		if (saveScore) {
			window.draw(goodScore);
			window.draw(nameText);
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (saveScore) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					return false;
				case sf::Event::TextEntered:
					if (event.text.unicode != 8) {
						name += event.text.unicode;
						nameText.setString(name);
					}
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code) {
					case sf::Keyboard::Enter:
						addHighscore(name, score);
						return true;
					case sf::Keyboard::BackSpace:
						if (name.getSize() > 0) {
							name.erase(name.getSize() - 1);
							nameText.setString(name);
						}
						break;
					}
				}
			}
			else {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					return false;
				case sf::Event::KeyReleased:
					switch (event.key.code) {
					case sf::Keyboard::Enter:
						return true;
					}
				}
			}
			window.display();
		}
	}

}

int WelcomeScreen::highscoresMenu(sf::RenderWindow &window) {
	/*
	window.clear();


	for (int i = 0; i < 10; i++) {
		score[i].setFont(font);
		score[i].setFillColor(sf::Color::Green);
		std::string temp = highscores[i].name + ": " + std::to_string(highscores[i].score);
		score[i].setString(temp);
		score[i].setPosition(sf::Vector2f(window.getSize().x / 2 - score[i].getLocalBounds().width / 2, window.getSize().y / (10 + 1) * (i + 1)));
		window.draw(score[i]);
	}

	window.display();
	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					return 1;
				}
			}
		}
	}
	*/
	return highscores.showHighscores(window, score, font);
}