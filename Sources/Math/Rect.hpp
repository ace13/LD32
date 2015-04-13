#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "Vec2.hpp"

namespace Math
{

	struct Rect : sf::FloatRect
	{
		Rect();
		Rect(float top, float left, float width, float height);
		Rect(const Vec2& pos, const Vec2& size);
		template<typename T>
		Rect(const sf::Rect<T>&);
		Rect(const Rect&) = default;
		~Rect() = default;

		static Rect FromPoints(const Vec2& p1, const Vec2& p2);

		Vec2 getCenter() const;
		Vec2 getSize() const;
		void setCenter(const Vec2& point);
		void setSize(const Vec2& size);

		Vec2 capture(const Vec2& point);
		void move(const Vec2& distance);
	};

}

template<typename T>
Math::Rect::Rect(const sf::Rect<T>& rect) : sf::FloatRect(rect) { }
