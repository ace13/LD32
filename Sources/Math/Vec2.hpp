#pragma once

#include <SFML/System/Vector2.hpp>

namespace Math
{

	struct Vec2 : sf::Vector2f
	{
		Vec2();
		Vec2(float x, float y);
		template<typename T>
		Vec2(const sf::Vector2<T>&);
		Vec2(const Vec2&) = default;
		~Vec2() = default;

		float getAngle() const;
		float getBearing(const Vec2& v2) const;
		float getDistance(const Vec2& v2) const;
		float getDistanceSquared(const Vec2& v2) const;
		float getDot(const Vec2& v2) const;
		float getLength() const;
		float getLengthSquared() const;
		Vec2 getNormalized() const;
		Vec2 getRotated(float ang) const;

		void setAngle(float ang);
		void setLength(float len);

		void normalize();
		void rotate(float ang);
	};

}

template<typename T>
inline Math::Vec2::Vec2(const sf::Vector2<T>& v) : sf::Vector2f((float)v.x, (float)v.y) { }
