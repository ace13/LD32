#include "Vec2.hpp"

#include <cmath>

using namespace Math;

namespace
{
	inline float Angle(const Vec2& vec)
	{
		return std::atan2(vec.y, vec.x);
	}
	inline float Dot(const Vec2& v1, const Vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
}

Vec2::Vec2() : sf::Vector2f() { }
Vec2::Vec2(float x, float y) : sf::Vector2f(x, y) { }

float Vec2::getAngle() const
{
	return Angle(*this);
}
float Vec2::getBearing(const Vec2& v2) const
{
	return Angle(v2 - *this);
}
float Vec2::getDistance(const Vec2& v2) const
{
	Vec2 dist = v2 - *this;
	return std::sqrt(Dot(dist, dist));
}
float Vec2::getDistanceSquared(const Vec2& v2) const
{
	Vec2 dist = v2 - *this;
	return Dot(dist, dist);
}
float Vec2::getDot(const Vec2& v2) const
{
	return Dot(*this, v2);
}
float Vec2::getLength() const
{
	return std::sqrt(Dot(*this, *this));
}
float Vec2::getLengthSquared() const
{
	return Dot(*this, *this);
}
Vec2 Vec2::getNormalized() const
{
	float len = std::sqrt(Dot(*this, *this));
	return *this / len;
}
Vec2 Vec2::getRotated(float ang) const
{
	float c = std::cos(ang),
		s = std::sin(ang);
	return Vec2(c * x - s * y, s * x + c * y);
}

void Vec2::setAngle(float ang)
{
	float len = std::sqrt(Dot(*this, *this));
	x = len * std::cos(ang);
	y = len * std::sin(ang);
}
void Vec2::setLength(float len)
{
	float oldLen = std::sqrt(Dot(*this, *this));
	if (oldLen == 0)
		x = oldLen;
	else
	{
		float newLen = len / oldLen;
		*this *= newLen;
	}
}

void Vec2::normalize()
{
	float len = std::sqrt(Dot(*this, *this));
	*this /= len;
}

void Vec2::rotate(float ang)
{
	float c = std::cos(ang),
		s = std::sin(ang),
		nx = c * x - s * y;

	y = s * x + c * y;
	x = nx;
}
