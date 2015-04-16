#include "Common.hpp"
#include "Eases.hpp"
#include "Spinor.hpp"

#include <random>

float Math::midAng(float ang1, float ang2, float perc)
{
	return Spinor::slerp(Spinor(ang1), Spinor(ang2), perc).getAngle();
}

float Math::randomFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(std::random_device());
}
int Math::randomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(std::random_device());
}