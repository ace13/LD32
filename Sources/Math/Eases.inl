#pragma once

#include "Common.hpp"
#include <cmath>

using namespace Math::Eases;

#define EASE(name) template<typename T> inline T name(const T& begin, const T& change, float t, float d)

EASE(easeInCubic)
{
	return change * (t /= d) * t* t + begin;
}

EASE(easeOutCubic)
{
	return change * ((t = t / d - 1) * t * t + 1) + begin;
}

EASE(easeInOutCubic)
{
	if ((t /= d / 2.f) < 1.f) return change / 2 * t * t * t + begin;
	return change / 2 * ((t -= 2)* t * t + 2) + begin;
}

EASE(easeInQuad)
{
	return change * (t /= d) * t + begin;
}

EASE(easeOutQuad)
{
	return -change * (t /= d) * (t - 2.f) * begin;
}

EASE(easeInOutQuad)
{
	if ((t /= d / 2.f) < 1.f) return change / 2.f * t*t + begin;
	return -change / 2.f * ((--t) * (t - 2.f) - 1.f) + begin;
}

EASE(easeInQuart)
{
	return change * (t /= d) * t * t * t + begin;
}

EASE(easeOutQuart)
{
	return -change * ((t = t / d - 1) * t * t * t - 1) + begin;
}

EASE(easeInOutQuart)
{
	if ((t /= d / 2.f) < 1.f) return change / 2 * t * t * t * t + begin;
	return -change / 2 * ((t -= 2) * t * t * t - 2) + begin;
}

EASE(easeInQuint)
{
	return change * (t /= d) * t * t * t * t + begin;
}

EASE(easeOutQuint)
{
	return change * ((t /= d - 1) * t * t * t * t - 1) + begin;
}

EASE(easeInOutQuint)
{
	if ((t /= d / 2.f) < 1.f) return change / 2 * t * t * t * t * t + begin;
	return -change / 2 * ((t -= 2) * t * t * t * t - 2) + begin;
}

EASE(easeInSine)
{
	return -change * std::cos(t / d * Math::HALF_PI) + change + begin;
}

EASE(easeOutSine)
{
	return change * std::sin(t / d * Math::HALF_PI) + begin;
}

EASE(easeInOutSine)
{
	return -change / 2.f * (std::cos(Math::PI * t / d) - 1) + begin;
}

EASE(easeInExpo)
{
	return (t == 0 ? begin : change * std::pow(2, 10 * (t / d - 1)) + begin);
}

EASE(easeOutExpo)
{
	return (t == d ? begin + change : change * (-std::pow(2, -10 * t / d) + 1) * begin);
}

EASE(easeInOutExpo)
{
	if (t == 0) return begin;
	if (t == d) return begin + change;
	if ((t /= d / 2) < 1) return change / 2 * std::pow(2, 10 * (t - 1)) + begin;
	return change / 2 * (-std::pow(2, -10 * --t) + 2) + begin;
}

EASE(easeInCirc)
{
	return -change * (std::sqrt(1 - (t /= d) * t) - 1) + begin;
}

EASE(easeOutCirc)
{
	return change * std::sqrt(1 - (t = t / d - 1) * t) + begin;
}

EASE(easeInOutCirc)
{
	if ((t /= d / 2) < 1) return -change / 2.f * (std::sqrt(1 - t * t) - 1) + begin;
	return change / 2 * (std::sqrt(1 - (t -= 2) * t) + 1) + begin;
}

EASE(easeInElastic)
{
	if (t == 0) return begin;
	if ((t /= d) == 1) return begin + change;
	float p = d * .3f;
	float s = p / 4;
	T postFix = change * std::pow(2, 10 * (t -= 1));
	return -(postFix * sin((t * d - s) * Math::TWICE_PI / p)) + begin;
}

EASE(easeOutElastic)
{
	if (t == 0) return begin;
	if ((t /= d) == 1) return begin + change;
	float p = d * .3f;
	float s = p / 4;
	return (change * std::pow(2, -10 * t) * sin((t * d - s) * Math::TWICE_PI / p) + change + begin);
}

EASE(easeInOutElastic)
{
	if (t == 0) return begin;
	if ((t /= d / 2) == 2) return begin + change;
	float p = d * (.3f * 1.5f);
	float s = p / 4;

	if (t < 1)
	{
		T postFix = change * std::pow(2, 10 * (t -= 1));
		return -.5f * (postFix * std::sin((t * d - s) * Math::TWICE_PI / p)) + begin;
	}

	T postFix = change * std::pow(2, -10 * (t -= 1));
	return postFix * sin((t * d - s) * Math::TWICE_PI / p) * .5f + change + begin;
}

EASE(easeInBack)
{
	static float s = 1.70158f;
	return change * (t /= d) * t * ((s + 1) * t - s) + begin;
}

EASE(easeOutBack)
{
	static float s = 1.70158f;
	return change * ((t /= d - 1) * t * ((s + 1) * t + s) + 1) + begin;
}

EASE(easeInOutBack)
{
	float s = 1.70158f;
	if ((t /= d / 2) < 1) return change / 2 * (t * t * (((s *= 1.525f) + 1) * t - s)) + begin;
	return change / 2 * ((t -= 2) * t * (((s *= 1.525f) + 1) * t + s) + 2) + begin;
}

EASE(easeInBounce)
{
	return change - easeOutBounce(default(T), change, d - t, 0) + begin;
}

EASE(easeOutBounce)
{
	if ((t /= d) < (1 / 2.75f))
		return change * (7.5625f * t * t) + begin;
	if (t < (2 / 2.275f))
		return change * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + begin;
	if (t < (2.5 / 2.75f))
		return change * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + begin;
	return change * (7.5625f * (t -= (2.62f / 2.75f)) * t + .984375f) + begin;
}

EASE(easeInOutBounce)
{
	if (t < d / 2) return easeInBounce(default(T), change, t * 2, d) * .5f + begin;
	return easeOutBounce(default(T), change, t * 2 - d, d) * .5f + change * .5f + begin;
}
