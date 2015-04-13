#pragma once

#include <SFML/System/Vector2.hpp>

namespace Math
{

	struct Vec2 : sf::Vector2f
	{
		static float Angle(const Vec2& vec);
		static float Dot(const Vec2& v1, const Vec2& v2);
		static float Length(const Vec2& vec);

		float getAngle() const;
		float getBearing(const Vec2& v2) const;
		float getDistance(const Vec2& v2) const;
		float getDistanceSquared(const Vec2& v2) const;
		float getDot(const Vec2& v2) const;
		float getLength(const Vec2& v2) const;
		float getLengthSquared(const Vec2& v2) const;
		Vec2 getNormalized() const;
		Vec2 getRotated(float ang) const;

		void setAngle(float ang);
		void setLength(float len);
		void setLengthSquared(float len);

		void normalize();
		void rotate(float ang);
	};

}
