#ifndef T_SHAPE_H
#define T_SHAPE_H
#include "Shape.h"
class T_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		" *  "
		" ** "
		" *  "
		"    ",
		"    "
		"*** "
		" *  "
		"    ",
		" *  "
		"**  "
		" *  "
		"    ",
		" *  "
		"*** "
		"    "
		"    "
	};
public:
	T_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	T_Shape();
	~T_Shape();
};

#endif