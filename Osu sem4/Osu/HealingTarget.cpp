#include "HealingTarget.h"



HealingTarget::HealingTarget(int target_pos_x, int target_pos_y, float wsp) :Target(100, target_pos_x, target_pos_y, wsp) {
}


void HealingTarget::hit(Player &player) {
	player.hit(100); //healing target restores 100 hp on hit (restores all hp)
	scored = true;
}

bool HealingTarget::isHit() {
	return scored;
}


bool HealingTarget::timed() {
	return timed_down;
}
