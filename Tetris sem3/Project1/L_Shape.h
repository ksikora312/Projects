#ifndef L_SHAPE_H
#define L_SHAPE_H
#include "Shape.h"
class L_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		" *  "
		" *  "
		" ** "
		"    ",
		"    "
		"*** "
		"*   "
		"    ",
		" ** "
		"  * "
		"  * "
		"    ",
		"  * "
		"*** "
		"    "
		"    "
	};
public:
	L_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	L_Shape();
	~L_Shape();
};

#endif