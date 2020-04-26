#ifndef LIST_H
#define LIST_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

struct player {
	std::string name;
	int score;
};

struct Score {
	std::string name;
	int score;
	Score *next;
};

class List
{
public:
	Score *head;
	List();
	~List();
	void add(std::string name_, int val);
	void show();
	void dropLast();
	bool operator>(int val);
	void save(std::string filename);
	bool goodEnough(int scor);
	List &operator+=(player sc);
	int showHighscores(sf::RenderWindow &window, sf::Text score[10], sf::Font &f);

};

#endif