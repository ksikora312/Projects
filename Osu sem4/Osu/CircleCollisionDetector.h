#ifndef DETECTOR_H
#define DETECTOR_H
#include <math.h>
class CircleCollisionDetector
{
public:
	static bool check(int position1_x, int position1_y, int radius1, int position2_x, int position2_y, int radius2);
};


#endif


