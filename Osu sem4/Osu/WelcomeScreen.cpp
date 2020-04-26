#include "WelcomeScreen.h"

#include <iostream>

WelcomeScreen::WelcomeScreen(int items_, std::string texts[], bool selectable_) {
	font.loadFromFile("font/font.ttf");
	background_tex.loadFromFile("sprites/background.jpg");
	background.setTexture(background_tex);
	background.setPosition(0, 0);

	selectable = selectable_;
	std::cout << selectable << std::endl;


	items = items_;

	text = new sf::Text[items];

	selected_index = 0;

	for (int i = 0; i < items; i++) {
		text[i].setString(texts[i]);
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::Cyan);
		text[i].setPosition(sf::Vector2f(background_tex.getSize().x / 2 - text[i].getGlobalBounds().width / 2, background_tex.getSize().y / (items + 1) * (i + 1)));
		if (selected_index == i && selectable) {
			text[i].setFillColor(sf::Color::Green);
			text[i].setStyle(sf::Text::Bold);
		}
	}
}

void WelcomeScreen::moveUp() {
	if (selected_index > 0) {
		text[selected_index].setFillColor(sf::Color::Cyan);
		text[selected_index].setStyle(sf::Text::Regular);
		selected_index--;
		text[selected_index].setFillColor(sf::Color::Green);
		text[selected_index].setStyle(sf::Text::Bold);
	}
}

void WelcomeScreen::moveDown() {
	if (selected_index < items - 1) {
		text[selected_index].setFillColor(sf::Color::Cyan);
		text[selected_index].setStyle(sf::Text::Regular);
		selected_index++;
		text[selected_index].setFillColor(sf::Color::Green);
		text[selected_index].setStyle(sf::Text::Bold);
	}
}

int WelcomeScreen::drawMenuStartGame(sf::RenderWindow &window) {
	while (window.isOpen()) {
		window.clear();
		window.draw(background);
		for (int i = 0; i < items; i++) {
			window.draw(text[i]);
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					return items - 1;
					break;
				case sf::Keyboard::Up:
					if (selectable)
						moveUp();
					break;
				case sf::Keyboard::Down:
					if (selectable)
						moveDown();
					break;
				case sf::Keyboard::Enter:
					window.clear();
					return selected_index;
					break;
				}
			}
		}
		window.display();
	}
	return selected_index;
}

void WelcomeScreen::setSettings(std::vector <std::string> texts, bool selectable_) {
	font.loadFromFile("font/font.ttf");
	background_tex.loadFromFile("sprites/background.jpg");
	background.setTexture(background_tex);
	background.setPosition(0, 0);

	selectable = selectable_;

	items = texts.size();

	text = new sf::Text[items];

	selected_index = 0;

	for (int i = 0; i < items; i++) {
		text[i].setString(texts[i]);
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::Cyan);
		text[i].setPosition(sf::Vector2f(background_tex.getSize().x / 2 - text[i].getGlobalBounds().width / 2, background_tex.getSize().y / (items + 1) * (i + 1)));
		if (selected_index == i && selectable) {
			text[i].setFillColor(sf::Color::Green);
			text[i].setStyle(sf::Text::Bold);
		}
	}
}

void WelcomeScreen::setSettings(std::vector <scor> texts, bool selectable_) {
	font.loadFromFile("font/font.ttf");
	background_tex.loadFromFile("sprites/background.jpg");
	background.setTexture(background_tex);
	background.setPosition(0, 0);

	selectable = selectable_;

	items = texts.size();

	text = new sf::Text[items];

	selected_index = 0;

	for (int i = 0; i < items; i++) {
		text[i].setString(texts[i].name + " " + std::to_string(texts[i].score));
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::Cyan);
		text[i].setPosition(sf::Vector2f(background_tex.getSize().x / 2 - text[i].getGlobalBounds().width / 2, background_tex.getSize().y / (items + 1) * (i + 1)));
		if (selected_index == i && selectable) {
			text[i].setFillColor(sf::Color::Green);
			text[i].setStyle(sf::Text::Bold);
		}
	}
}


bool WelcomeScreen::endGameWithoutSave(sf::RenderWindow &window, int score, bool timed) {
	int texts = 3;
	sf::Text txt[3];
	if (timed) {
		txt[0].setString("Time has run out!");

	}
	else {
		txt[0].setString("You have lost!");
	}
		

		txt[1].setString("Your score was : " + std::to_string(score));
		txt[2].setString("Space/enter to play again. Escape to close the game.");

		txt[0].setFillColor(sf::Color::Red);
		txt[1].setFillColor(sf::Color::Green);
		txt[2].setFillColor(sf::Color::Green);

		for (int i = 0; i < texts; i++) {
			txt[i].setFont(font);
			txt[i].setPosition(sf::Vector2f(background_tex.getSize().x / 2 - txt[i].getGlobalBounds().width / 2, background_tex.getSize().y / (texts + 1) * (i + 1)));
		}


		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::KeyReleased:
					switch (event.key.code) {
					case sf::Keyboard::Space:
					case sf::Keyboard::Enter:
						return true;
					case sf::Keyboard::Escape:
						return false;
					}
				}
			}
			window.clear();
			window.draw(background);
			for (int i = 0; i < texts; i++) {
				window.draw(txt[i]);
			}
			window.display();
		}

}

bool WelcomeScreen::endGameWithSave(sf::RenderWindow &window, std::vector <scor> &highscores, int score, bool timed) {
	bool correct_name = true;
	sf::Text incorrect;
	incorrect.setFont(font);
	incorrect.setCharacterSize(20);
	incorrect.setFillColor(sf::Color::Red);
	incorrect.setString("no special characters!");
	std::regex check("[a-zA-Z0-9]+");
	int texts = 5;
	sf::Text txt[5];
	sf::String input = "";
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);

	if (timed) {
		txt[0].setString("Time has run out!");

	}
	else {
		txt[0].setString("You have lost!");
	}


	txt[1].setString("Nice! Your score was : " + std::to_string(score));
	txt[2].setString("Enter you name to save highscore. Do not use special characters:");
	txt[3].setString(input);
	txt[4].setString("Hit enter when you're done typing. Escape to close the game.");

	txt[0].setFillColor(sf::Color::Red);
	txt[1].setFillColor(sf::Color::Green);
	txt[2].setFillColor(sf::Color::Green);
	txt[3].setFillColor(sf::Color::Blue);
	txt[4].setFillColor(sf::Color::Green);

	for (int i = 0; i < texts; i++) {
		txt[i].setFont(font);
		txt[i].setPosition(sf::Vector2f(background_tex.getSize().x / 2 - txt[i].getGlobalBounds().width / 2, background_tex.getSize().y / (texts + 1) * (i + 1)));
	}

	rect.setSize(sf::Vector2f(200, txt[texts - 2].getCharacterSize() + 2));
	rect.setPosition(txt[texts - 2].getPosition().x - rect.getSize().x/2, txt[texts - 2].getPosition().y);
	incorrect.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y + rect.getSize().y + 5));
	txt[texts - 2].setPosition(txt[texts - 2].getPosition().x - rect.getSize().x / 2, txt[texts - 2].getPosition().y);
	


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::TextEntered:
				if (event.text.unicode != 8) {
					input += event.text.unicode;
					txt[texts - 2].setString(input);
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Enter:
				{
					scor temp;
					sf::String temp_string = input;
					temp_string.erase(temp_string.getSize() - 1);
					std::string tmp_s = temp_string;
					//to get rid of the new line character at the end of the string
					if (!std::regex_match(tmp_s, check)) {
						correct_name = false;
						break;
					}
					temp.name = temp_string;
					temp.score = score;
					highscores.push_back(temp);
					std::sort(highscores.begin(), highscores.end(), Scores::comp);
					highscores.pop_back();
					Scores::saveHighscores(highscores);
					return true;
					break;
				}
				case sf::Keyboard::Escape:
					return false;
					break;
				case sf::Keyboard::Backspace:
					if (input.getSize() > 0) {
						input.erase(input.getSize() - 1);
						txt[texts - 2].setString(input);
					}
					break;
				}
			}
		}
		window.clear();
		window.draw(background);
		window.draw(rect);
		for (int i = 0; i < texts; i++) {
			window.draw(txt[i]);
		}
		if (!correct_name) {
			window.draw(incorrect);
		}
		window.display();
	}

}