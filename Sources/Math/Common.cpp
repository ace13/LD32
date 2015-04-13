#include "Common.hpp"
#include "Eases.hpp"
#include "Spinor.hpp"

using namespace Math;

float midAng(float ang1, float ang2, float perc)
{
	return Spinor::slerp(Spinor(ang1), Spinor(ang2), perc).getAngle();
}

template<typename T>
Easer<T>::Easer(easeFunc function, float duration) :
	mDuration(duration), mEaser(function)
{
	assert(function != null);
}

template<typename T>
T Easer<T>::ease(const T& start, const T& end, float time)
{
	return mEaser(start, end - start, time, mDuration);
}
