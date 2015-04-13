#pragma once

namespace Math
{

	static const float PI = 3.1415f;
	static const float HALF_PI = PI / 2.f;
	static const float TWICE_PI = PI * 2;

	template<typename T>
	extern T mid(const T& start, const T& end, float perc = 0.5);
	extern float midAng(float ang1, float ang2, float perc = 0.5f);
	template<typename T>
	extern void simpleEase(T& val, const T& target);

}

#include "Common.inl"
