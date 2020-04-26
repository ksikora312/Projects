#ifndef MATRIX_H
#define MATRIX_H
#include <SFML\Graphics.hpp>
#include "Shape.h"
#include <fstream>
struct values {
	bool isFull;
	int r, g, b;
};
class Matrixx
{
public:
	values matrix[10][20];
	bool loadFromFile(std::string name, int &sc);
	bool saveToFile(std::string name, int sc);
	void drawMatrix(sf::RenderWindow &win);
	bool collision(Shape *shape);
	void joinAndScore(Shape *shap, int &score);
	Matrixx();
	~Matrixx();
};

#endif
