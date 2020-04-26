#ifndef BONUSAIMTARGET_H
#define BONUSAIMTARGET_H
#include "Target.h"

class BonusAimTarget :
	public Target
{

public:

	BonusAimTarget(int target_pos_x, int target_pos_y, float wsp);

	void hit(Player &player);
	bool isHit();
	bool timed();

};


#endif


