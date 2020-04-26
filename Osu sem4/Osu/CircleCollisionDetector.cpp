#include "CircleCollisionDetector.h"


bool CircleCollisionDetector::check(int position1_x, int position1_y, int radius1, int position2_x, int position2_y, int radius2) {
	float distance_between_centres = sqrt(pow(position1_x - position2_x, 2) + pow(position1_y - position2_y, 2));
	if (distance_between_centres <= radius1 + radius2)
		return true;
	return false;
}