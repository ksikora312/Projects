#include "Matrixx.h"


Matrixx::Matrixx()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			matrix[i][j].isFull = false;
			matrix[i][j].r = 0;
			matrix[i][j].g = 0;
			matrix[i][j].b = 0;
		}
	}
}

Matrixx::~Matrixx()
{
}

bool Matrixx::loadFromFile(std::string name, int &sc) {
	int temp = 0;
	std::string filename = name.substr(0, name.size() - 1);
	std::ifstream plik(filename);
	if (plik) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				plik >> matrix[i][j].isFull >> matrix[i][j].r >> matrix[i][j].g >> matrix[i][j].b;
			}
		}
		plik >> temp;
		sc = temp;
		plik.close();
		return true;
	}
	return false;
}
bool Matrixx::saveToFile(std::string name, int sc) {
	std::string filename = name.substr(0, name.size() - 1);
	std::ofstream plik(filename);
	if (plik) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				plik << matrix[i][j].isFull << " " << matrix[i][j].r << " " << matrix[i][j].g << " " << matrix[i][j].b << std::endl;
			}
		}
		plik << sc;
		plik.close();
		return true;
	}
	return false;
}

void Matrixx::drawMatrix(sf::RenderWindow &win) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (matrix[i][j].isFull == false) {
				sf::RectangleShape pt(sf::Vector2f(1, 1));
				pt.setFillColor(sf::Color(255, 255, 255));
				pt.setPosition(sf::Vector2f(720 / 20 * i + 720/20/2, 720 / 20 * j + 720/20/2));
				win.draw(pt);
			}
			else {
				sf::RectangleShape pt(sf::Vector2f(720 / 20 - 1, 720 / 20 - 1));
				pt.setFillColor(sf::Color(matrix[i][j].r, matrix[i][j].g, matrix[i][j].b));
				pt.setPosition(sf::Vector2f(720 / 20 * i + 1, 720 / 20 * j + 1));
				win.draw(pt);
			}
		}
	}
}

bool Matrixx::collision(Shape *shape) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape->isShape(i, j)) {
				int sx = shape->getX() + i;
				int sy = shape->getY() + j;
				if (sx < 0 || sx > 9 || sy > 19 || sy < 0)
					return true;
				if (matrix[sx][sy].isFull)
					return true;
			}
		}
	}
	return false;
}


void Matrixx::joinAndScore(Shape *shap, int &score) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shap->isShape(i, j)) {
				matrix[shap->getX() + i][shap->getY() + j].isFull = true;
				matrix[shap->getX() + i][shap->getY() + j].r = shap->getR();
				matrix[shap->getX() + i][shap->getY() + j].g = shap->getG();
				matrix[shap->getX() + i][shap->getY() + j].b = shap->getB();
			}
		}
	}
	for (int z = 0; z < 19; z++) {
		for (int y = 20 - 1; y >= 0; --y)
		{
			bool solid = true;
			for (int x = 0; x < 10; ++x)
				if (!matrix[x][y].isFull)
				{
					solid = false;
					break;
				}
			if (solid)
			{
				score += 10;
				for (int yy = y - 1; yy >= 0; --yy)
					for (int x = 0; x < 10; ++x)
						matrix[x][yy + 1] = matrix[x][yy];
				for (int x = 0; x < 10; ++x)
					matrix[x][0].isFull = false;
			}
		}
	}
}