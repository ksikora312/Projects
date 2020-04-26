#include "Scores.h"

#include <iostream>





bool Scores::comp(scor &s1, scor &s2) {
	if (s1.score > s2.score)
		return true;
	return false;
}


Scores::Scores(int scores, int hp) {
	score = scores;
	this->hp = hp;
	try {
		font.loadFromFile("font/font.ttf");
	}
	catch (const std::exception &ex) {
		exit(-1);
	}

	draw_bonus_time = false;

	text_score.setFont(font);
	text_score.setString("Score: " + std::to_string(score));
	text_score.setFillColor(sf::Color::Green);
	text_score.setPosition(1080 - healthBar.getSize().x - 400, 20);

	healthBar.setFillColor(sf::Color::Red);
	healthBar.setSize(sf::Vector2f(2 * hp, 40));
	healthBar.setPosition(1080 - healthBar.getSize().x, 20);

	healthBarOutline.setFillColor(sf::Color(0, 0, 0, 0));
	healthBarOutline.setOutlineColor(sf::Color::White);
	healthBarOutline.setOutlineThickness(1);
	healthBarOutline.setPosition(1080 - healthBar.getSize().x, 20);
	healthBarOutline.setSize(sf::Vector2f(2 * max_hp, 40));

	text_aim_bonus.setFont(font);
	text_aim_bonus.setFillColor(sf::Color::Green);
	text_aim_bonus.setPosition(0, 20);

	text_game_time_left.setFont(font);
	text_game_time_left.setFillColor(sf::Color::Green);
	text_game_time_left.setPosition(healthBarOutline.getPosition().x + healthBar.getSize().x + 20, 20);


}


void Scores::drawScores(sf::RenderWindow &window) {
	window.draw(text_score);
	window.draw(text_game_time_left);
	window.draw(healthBar);
	window.draw(healthBarOutline);
	if (draw_bonus_time)
		window.draw(text_aim_bonus);
}

void Scores::setScore(int s) {
	this->score = s;
	text_score.setString("Score: " + std::to_string(score));
}

void Scores::setHp(int hp_) {
	this->hp = hp;
	if (hp_ >= 0) {
		healthBar.setSize(sf::Vector2f(2 * hp_, healthBar.getSize().y));
	}
	else {
		healthBar.setSize(sf::Vector2f(0, healthBar.getSize().y));
	}
}

void Scores::setAimBonusTime(int32_t t) {
	if (t > 0) {
		draw_bonus_time = true;
		text_aim_bonus.setString("Aim bonus: " + std::to_string(t) + " ms");
	}
	else {
		draw_bonus_time = false;
	}

	if (t >= 2000 && t < 3000)
		text_aim_bonus.setFillColor(sf::Color(255, 140, 0, 255));
	else if (t < 2000 && t > 0)
		text_aim_bonus.setFillColor(sf::Color::Red);
	else
		text_aim_bonus.setFillColor(sf::Color::Green);

}

void Scores::setGameTimeLeft(sf::Time t) {
	if (t.asSeconds() < 50)
		text_game_time_left.setFillColor(sf::Color(255, 140, 0, 255)); //orange
	else if (t.asSeconds() < 20)
		text_game_time_left.setFillColor(sf::Color::Red);
	else
		text_game_time_left.setFillColor(sf::Color::Green);
	text_game_time_left.setString("Time left: " + std::to_string(t.asSeconds()));
}


void Scores::fetchHighscores(std::vector <scor> &tab) {
	bool success = true;
	try {
		std::ifstream plik;
		plik.open("highscores.txt");
		int licznik = 0;
		if (plik.is_open()) {
			scor temp;
			while (plik >> temp.name >> temp.score && licznik != 10) {
				tab.push_back(temp);
				licznik++;
			}
			while (licznik <= 9) {
				temp.name = "------------";
				temp.score = 0;
				tab.push_back(temp);
				licznik++;
			}
		}
		else {
			success = false;
		}
		plik.close();
	}
	catch (const std::exception &ex) {
		success = false;
	}
	if (!success) {
		std::ofstream plik("highscores.txt");
		if (plik) {
			for (int i = 0; i < 10; i++) {
				tab[i].name = "------------";
				tab[i].score = 0;
				plik << tab[i].name << " " << tab[i].score << std::endl;
			}
		}
		plik.close();
	}
	std::sort(tab.begin(), tab.end(), comp);
}

void Scores::saveHighscores(std::vector <scor> &tab) {
	std::ofstream plik("highscores.txt");
	if (plik) {
		for (int i = 0; i < 10; i++) {
			plik << tab[i].name << " " << tab[i].score << std::endl;
		}
	}
	plik.close();
}