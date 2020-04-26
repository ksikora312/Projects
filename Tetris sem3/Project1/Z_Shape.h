#ifndef Z_SHAPE_H
#define Z_SHAPE_H
#include "Shape.h"
class Z_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		"  * "
		" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    ",
		"  * "
		" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    "
	};
public:
	Z_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	Z_Shape();
	~Z_Shape();
};

#endif