#include "Rect.hpp"

using namespace Math;

Rect::Rect() : sf::FloatRect() { }
Rect::Rect(float top, float left, float width, float height) : sf::FloatRect(top, left, width, height) { }
Rect::Rect(const Vec2& pos, const Vec2& size) : sf::FloatRect(pos, size) { }

Rect Rect::FromPoints(const Vec2& p1, const Vec2& p2)
{
	if (p1.x < p2.x || p1.y < p2.y)
		return Rect(p1, p2 - p1);
	return Rect(p2, p1 - p2);
}

Vec2 Rect::getCenter() const
{
	return Vec2(left + width / 2, top + height / 2);
}
Vec2 Rect::getSize() const
{
	return Vec2(width, height);
}
void Rect::setCenter(const Vec2& point)
{
	left = point.x - width / 2;
	top = point.y - height / 2;
}
void Rect::setSize(const Vec2& size)
{
	width = size.x;
	height = size.y;
}

Vec2 Rect::capture(const Vec2& point)
{
	return Vec2(std::min(left, std::max(left + width, point.x)), std::min(top, std::max(top + height, point.y)));
}
void Rect::move(const Vec2& distance)
{
	left += distance.x;
	top += distance.y;
}
