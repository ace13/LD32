#include "Common.hpp"
#include "Eases.hpp"
#include "Spinor.hpp"

using namespace Math;

float midAng(float ang1, float ang2, float perc)
{
	return Spinor::slerp(Spinor(ang1), Spinor(ang2), perc).getAngle();
}
