#include "NormalTarget.h"


NormalTarget::NormalTarget(int color_number, int target_pos_x, int target_pos_y, float wsp) :Target(color_number, target_pos_x, target_pos_y, wsp) {
}


void NormalTarget::hit(Player &player) {
	player.hit(2); //normal target restores 2 hp on hit
	scored = true;
}

bool NormalTarget::isHit() {
	return scored;
}


bool NormalTarget::timed() {
	return timed_down;
}