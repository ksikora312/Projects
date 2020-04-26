#include "BonusAimTarget.h"



BonusAimTarget::BonusAimTarget(int target_pos_x, int target_pos_y, float wsp) :Target(-1, target_pos_x, target_pos_y, wsp) {
}


void BonusAimTarget::hit(Player &player) {
	player.setAimBonus();  //healing target restores 100 hp on hit (restores all hp)
	scored = true;
}

bool BonusAimTarget::isHit() {
	return scored;
}


bool BonusAimTarget::timed() {
	return timed_down;
}
