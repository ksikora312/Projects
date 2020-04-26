#ifndef J_SHAPE_H
#define J_SHAPE_H
#include "Shape.h"
class J_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		"  * "
		"  * "
		" ** "
		"    ",
		"    "
		"*   "
		"*** "
		"    ",
		" ** "
		" *  "
		" *  "
		"    ",
		"    "
		"    "
		"*** "
		"  * "
	};
public:
	J_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	J_Shape();
	~J_Shape();
};

#endif