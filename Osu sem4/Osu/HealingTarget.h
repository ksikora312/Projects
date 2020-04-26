#ifndef HEALINGTARGET_H
#define HEALINGTARGET_H
#include "Target.h"
#include "SFML/Graphics.hpp"
class HealingTarget :
	public Target
{
public:

	HealingTarget(int target_pos_x, int target_pos_y, float wsp);

	void hit(Player &player);
	bool isHit();
	bool timed();
};


#endif


