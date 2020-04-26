#ifndef O_SHAPE_H
#define O_SHAPE_H
#include "Shape.h"
class O_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    "
	};
public:
	O_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	O_Shape();
	~O_Shape();
};

#endif