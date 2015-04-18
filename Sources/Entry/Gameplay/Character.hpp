#pragma once

#include <Math/Vec2.hpp>
#include <Kunlaboro/Component.hpp>

class asIScriptEngine;

namespace sf { class RenderTarget; }

namespace Gameplay
{
	class Character : public Kunlaboro::Component
	{
	public:
		Character();
		~Character();

		void addedToEntity();

		const Math::Vec2& getPosition() const;
		void setPosition(const Math::Vec2& position);
		float getRadius() const;
		void setRadius(float rad);

		static void addScript(asIScriptEngine* eng);
		
	private:
		void draw(sf::RenderTarget& rt);
		Kunlaboro::Optional<Math::Vec2> getPositionMsg();
		Kunlaboro::Optional<float> getRadiusMsg();

		float mRadius, mHealth, mSanity, mMaxSanity;
		Math::Vec2 mPosition;
	};
}