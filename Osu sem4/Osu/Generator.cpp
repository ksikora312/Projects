#include "Generator.h"

#include <iostream>
Generator::Generator(int min, int max, int min_x, int max_x, int min_y, int max_y) :distribution(min, max), distribution_x(min_x, max_x),
	distribution_y(min_y, max_y), distribution_wsp(1.5, 2.0), generator(rd()), dist_x((max_x - min_x) / 2, (max_x - min_x - 120)/4), 
	dist_y((max_y - min_y) / 2, (max_y - min_y - 120)/4), target_type_dist(0, 1) {
	minimum_x = min_x;
	maximum_x = max_x;
	minimum_y = min_y;
	maximum_y = max_y;
}


int Generator::generate() {
	return distribution(generator);
}

int Generator::generate_x() {
	int temp = (int)dist_x(generator);
	if (temp > maximum_x)
		temp = maximum_x;
	else if (temp < minimum_x)
		temp = minimum_x;
	return temp;
	//return distribution_x(generator);
}

int Generator::generate_y() {
	int temp = (int)dist_y(generator);
	if (temp > maximum_y)
		temp = maximum_y;
	else if (temp < minimum_y)
		temp = minimum_y;
	return temp;
	//return distribution_y(generator);
}

float Generator::generate_wsp() {
	return distribution_wsp(generator);
}

double Generator::targetType() {
	return target_type_dist(generator);
}