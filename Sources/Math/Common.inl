#pragma once

template<typename T>
inline T Math::mid(const T& start, const T& end, float perc)
{
	return start + (perc * (end - start));
}

template<typename T>
inline void Math::simpleEase(T& val, const T& target)
{
	val += (target - val) * .1f;
}