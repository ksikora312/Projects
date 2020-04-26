#ifndef NORMALTARGET_H
#define NORMALTARGET_H
#include "Target.h"
#include "SFML/Graphics.hpp"
class NormalTarget :
	public Target
{
public:

	NormalTarget(int color_number, int target_pos_x, int target_pos_y, float wsp);

	void hit(Player &player);
	bool isHit();
	bool timed();
};

#endif

