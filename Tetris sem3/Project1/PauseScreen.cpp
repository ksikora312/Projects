#include "PauseScreen.h"

int PauseScreen::drawMenu(sf::RenderWindow &window) {

	selectedIndex = 0;

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
					return selectedIndex;
					break;
				}
			}
		}
		window.display();
	}
}

void PauseScreen::moveUp() {
	if (selectedIndex > 0) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}

void PauseScreen::moveDown() {
	if (selectedIndex < ITEMS - 1) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}


sf::String PauseScreen::saveScreen(sf::RenderWindow &win) {
	win.clear();
	filenameText.setFont(font);
	filenameText.setFillColor(sf::Color::Cyan);
	prompt.setFont(font);
	prompt.setFillColor(sf::Color::White);
	prompt.setString("Enter name of the file");
	prompt.setPosition(sf::Vector2f(win.getSize().x / 2 - prompt.getLocalBounds().width / 2, win.getSize().y / (3) * 1));
	filenameText.setPosition(sf::Vector2f(win.getSize().x / 2 - prompt.getLocalBounds().width / 2, win.getSize().y / (3) + 30));

	while (win.isOpen()) {
		win.clear();
		win.draw(prompt);
		win.draw(filenameText);
		sf::Event event;
		while (win.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode != 8) {
					filename += event.text.unicode;
					filenameText.setString(filename);
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Enter:
					return filename;
				case sf::Keyboard::BackSpace:
					if (filename.getSize() > 0) {
						filename.erase(filename.getSize() - 1);
						filenameText.setString(filename);
					}
					break;
				}
			}
			win.display();
	}

	return filename;
}

PauseScreen::PauseScreen(float width, float height)
{

	if (!font.loadFromFile("orange.ttf")) {
		//error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Continue");
	menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, height / (ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Save game & exit");
	menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, height / (ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("exit");
	menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getLocalBounds().width / 2, height / (ITEMS + 1) * 3));


	selectedIndex = 0;
}


PauseScreen::~PauseScreen()
{
}

void PauseScreen::showScore(sf::RenderWindow &win, int sc) {

	score.setFont(font);
	score.setFillColor(sf::Color::Cyan);
	std::string scoreText = "Score: " + std::to_string(sc);
	score.setString(scoreText);
	score.setPosition(sf::Vector2f(win.getSize().x / 2 - score.getLocalBounds().width / 2, 720));

	win.draw(score);
}