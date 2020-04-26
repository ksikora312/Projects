#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include <chrono>

class Generator
{
	int minimum_x, maximum_x, minimum_y, maximum_y;
	std::default_random_engine generator;
	std::uniform_int_distribution <int> distribution;
	std::uniform_int_distribution <int> distribution_x;
	std::uniform_int_distribution <int> distribution_y;
	std::uniform_real_distribution <float> distribution_wsp;
	std::normal_distribution <double> dist_x;
	std::normal_distribution <double> dist_y;
	std::uniform_real_distribution <double> target_type_dist;

	std::random_device rd;

public:
	Generator(int min, int max, int min_x, int max_x, int min_y, int max_y);
	int generate();
	int generate_x();
	int generate_y();
	float generate_wsp();
	double targetType();
};


#endif

