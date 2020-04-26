#ifndef I_SHAPE_H
#define I_SHAPE_H
#include "Shape.h"
class I_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		" *  "
		" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    ",
		" *  "
		" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    "
	};
public:
	I_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	I_Shape();
	~I_Shape();
};

#endif