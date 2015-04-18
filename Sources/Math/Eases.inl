#pragma once

#include "Common.hpp"
#include <cmath>

namespace Math
{

	template<typename T>
	Easer<T>::Easer(EaseFunc function, float duration) :
		mDuration(duration), mEaser(function)
	{

	}
	
	template<typename T>
	inline T Easer<T>::ease(const T& start, const T& end, float time)
	{
		if (time <= 0)
			return start;
		else if (time >= mDuration)
			return end;

		return mEaser(start, end - start, time, mDuration);
	}

	template<typename T>
	inline float Easer<T>::getDuration() const
	{
		return mDuration;
	}
	template<typename T>
	inline void Easer<T>::setDuration(float d)
	{
		mDuration = d;
	}

}


#define EASE(name) template<typename T> inline T Math::Eases::name(const T& begin, const T& change, float t, float d)

EASE(easeInCubic)
{
	t /= d;
	return change * (t * t * t) + begin;
}

EASE(easeOutCubic)
{
	t = t / d - 1;
	return change * (t * t * t + 1) + begin;
}

EASE(easeInOutCubic)
{
	t /= d / 2.f;

	if (t < 1.f)
		return change / (2 * t * t * t) + begin;

	t -= 2;
	return change / (2 * (t * t * t + 2)) + begin;
}

EASE(easeInQuad)
{
	t /= d;

	return change * (t * t) + begin;
}

EASE(easeOutQuad)
{
	t /= d;

	return -change * (t * (t - 2.f)) + begin;
}

EASE(easeInOutQuad)
{
	t /= d / 2.f;

	if (t < 1.f)
		return change / (2.f * t * t) + begin;

	t -= 1;
	return -change / 2.f * (t * (t - 2.f) - 1.f) + begin;
}

EASE(easeInQuart)
{
	t /= d;
	return change * (t * t * t * t) + begin;
}

EASE(easeOutQuart)
{
	t = t / d - 1;
	return -change * (t * t * t * t - 1) + begin;
}

EASE(easeInOutQuart)
{
	t /= d / 2.f;

	if (t < 1.f)
		return change / (2 * t * t * t * t) + begin;

	t -= 2;
	return -change / (2 * (t * t * t * t - 2)) + begin;
}

EASE(easeInQuint)
{
	t /= d;
	return change * (t * t * t * t * t) + begin;
}

EASE(easeOutQuint)
{
	t /= d;
	return change * ((t - 1) * t * t * t * t - 1) + begin;
}

EASE(easeInOutQuint)
{
	t /= d / 2.f;
	if (t < 1.f) return change / (2 * t * t * t * t * t) + begin;
	t -= 2;
	return -change / (2 * (t * t * t * t * t - 2)) + begin;
}

EASE(easeInSine)
{
	return -change * std::cos((t / d) * Math::HALF_PI) + change + begin;
}

EASE(easeOutSine)
{
	return change * std::sin((t / d) * Math::HALF_PI) + begin;
}

EASE(easeInOutSine)
{
	return -change / 2.f * (std::cos(Math::PI * (t / d)) - 1) + begin;
}

EASE(easeInExpo)
{
	return change * (float)std::pow(2, 10 * ((t / d) - 1)) + begin;
}

EASE(easeOutExpo)
{
	return change * ((float)-std::pow(2, -10 * (t / d)) + 1) + begin;
}

EASE(easeInOutExpo)
{
	t /= d / 2;

	if (t < 1)
		return change / (2 * (float)std::pow(2, 10 * (t - 1))) + begin;

	t -= 1;
	return change / (2 * ((float)-std::pow(2, -10 * t) + 2)) + begin;
}

EASE(easeInCirc)
{
	t /= d;
	return -change * (std::sqrt(1 - t * t) - 1) + begin;
}

EASE(easeOutCirc)
{
	t = (t / d) - 1;
	return change * std::sqrt(1 - t * t) + begin;
}

EASE(easeInOutCirc)
{
	t /= d / 2;

	if (t < 1) return
		-change / (2.f * (std::sqrt(1 - t * t) - 1)) + begin;

	t -= 2;
	return change / (2 * (std::sqrt(1 - t * t) + 1)) + begin;
}

EASE(easeInElastic)
{
	t /= d;
	float p = d * .3f;
	float s = p / 4;
	t -= 1;
	T postFix = change * (float)std::pow(2, 10 * t);
	return -(postFix * std::sin((t * d - s) * Math::TWICE_PI / p)) + begin;
}

EASE(easeOutElastic)
{
	t /= d;
	float p = d * .3f;
	float s = p / 4;
	return (change * (float)std::pow(2, -10 * t) * sin((t * d - s) * Math::TWICE_PI / p) + change + begin);
}

EASE(easeInOutElastic)
{
	t /= d;
	float p = d * (.3f * 1.5f);
	float s = p / 4;

	if (t < 1)
	{
		T postFix = change * (float)std::pow(2, 10 * (t -= 1));
		return -.5f * (postFix * std::sin((t * d - s) * Math::TWICE_PI / p)) + begin;
	}

	T postFix = change * (float)std::pow(2, -10 * (t -= 1));
	return postFix * std::sin((t * d - s) * Math::TWICE_PI / p) * .5f + change + begin;
}

EASE(easeInBack)
{
	static float s = 1.70158f;
	t /= d;
	return change * t * t * ((s + 1) * t - s) + begin;
}

EASE(easeOutBack)
{
	static float s = 1.70158f;
	t /= d;
	return change * ((t - 1) * t * ((s + 1) * t + s) + 1) + begin;
}

EASE(easeInOutBack)
{
	float s = 1.70158f;
	t /= d / 2;
	s *= 1.525f;
	if (t < 1)
		return change / (2 * (t * t * ((s + 1) * t - s))) + begin;
	t -= 2;
	return change / (2 * (t * t * ((s + 1) * t + s) + 2)) + begin;
}

EASE(easeInBounce)
{
	return change - easeOutBounce(T(), change, d - t, d) + begin;
}

EASE(easeOutBounce)
{
	t /= d;
	if (t < (1 / 2.75f))
		return change * (7.5625f * t * t) + begin;
	else if (t < (2 / 2.275f))
	{
		t -= (1.5f / 2.75f);
		return change * (7.5625f * t * t + .75f) + begin;
	}
	else if (t < (2.5 / 2.75f))
	{
		t -= (2.25f / 2.75f);
		return change * (7.5625f * t * t + .9375f) + begin;
	}

	t -= (2.62f / 2.75f);
	return change * (7.5625f * t * t + .984375f) + begin;
}

EASE(easeInOutBounce)
{
	if (t < d / 2) return easeInBounce(T(), change, t * 2, d) * .5f + begin;
	return easeOutBounce(T(), change, t * 2 - d, d) * .5f + change * .5f + begin;
}
