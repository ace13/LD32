#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "Vec2.hpp"

namespace Math
{

	struct Rect : sf::FloatRect
	{
		static Rect FromPoints(const Vec2& p1, const Vec2& p2);

		Vec2 getCenter() const;
		Vec2 getSize() const;
		void setCenter(const Vec2& point);
		void setSize(const Vec2& size);

		Vec2 capture(const Vec2& point);
		void move(const Vec2& distance);
	};

}
