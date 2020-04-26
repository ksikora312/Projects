#include "List.h"



List::List()
{
	head = nullptr;
}


List::~List()
{
	Score *temp = head;
	while (temp) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

void List::add(std::string name_, int val) {
	if (head == nullptr) {
		Score *sc = new Score{ name_, val, nullptr };
		head = sc;
		return;
	}

	if (val > head->score) {
		Score *sc = new Score{ name_, val, head };
		head = sc;
		return;
	}

	Score *temp = head;

	while (temp->next) {
		if (temp->next->score >= val)
			temp = temp->next;
		else
			break;
	}
	if (temp->next) {
		Score *sc = new Score{ name_, val, temp->next };
		temp->next = sc;
		return;
	}
	//gdy na koncu do dodania
	else {
		Score *sc = new Score{ name_, val, nullptr };
		temp->next = sc;
		return;
	}
}

void List::show() {
	Score *temp = head;
	while (temp) {
		std::cout << temp->name << ": " << temp->score << std::endl;
		temp = temp->next;
	}
}

void List::dropLast() {
	Score *temp = head;
	while (temp->next->next) {
		temp = temp->next;
	}
	Score *temp2 = temp->next;
	temp->next = 0;
	delete temp2;
}

List &List::operator+=(player sc) {
	add(sc.name, sc.score);
	return *this;
}

bool List::operator>(int val) {
	int size = 0;
	Score *temp = head;
	while (temp) {
		size++;
		temp = temp->next;
	}
	if (size > val)
		return true;
	return false;
}

void List::save(std::string filename) {
	std::ofstream plik(filename);
	if (plik) {
		Score *temp = head;
		for (int i = 0; i < 10; i++) {
			plik << temp->name << " " << temp->score << std::endl;
			temp = temp->next;
		}
		plik.close();
	}
}

bool List::goodEnough(int scor) {
	Score *temp = head;
	for (int i = 0; i < 10; i++) {
		if (scor > temp->score)
			return true;
		temp = temp->next;
	}
	return false;
}

int List::showHighscores(sf::RenderWindow &window, sf::Text score[10], sf::Font &font) {

	window.clear();

	Score *tem = head;
	for (int i = 0; i < 10; i++) {
		score[i].setFont(font);
		score[i].setFillColor(sf::Color::Green);
		std::string temp = tem->name + ": " + std::to_string(tem->score);
		score[i].setString(temp);
		score[i].setPosition(sf::Vector2f(window.getSize().x / 2 - score[i].getLocalBounds().width / 2, window.getSize().y / (10 + 1) * (i + 1)));
		window.draw(score[i]);
		tem = tem->next;
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
}