#ifndef S_SHAPE_H
#define S_SHAPE_H
#include "Shape.h"
class S_Shape : public virtual Shape
{
protected:
	const char *shape[4] = {
		" *  "
		" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    ",
		" *  "
		" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    "
	};
public:
	S_Shape *clone();
	void draw(sf::RenderWindow &window);
	bool isShape(int x, int y);
	S_Shape();
	~S_Shape();
};

#endif