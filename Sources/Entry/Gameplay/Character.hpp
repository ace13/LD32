#pragma once

#include <Math/Vec2.hpp>
#include <Kunlaboro/Component.hpp>
#include <Util/Time.hpp>

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

		const Math::Vec2& getAimVec() const;
		const Math::Vec2& getPosition() const;
		const Math::Vec2& getVelocity() const;
		void setAimVec(const Math::Vec2& aim);
		void setPosition(const Math::Vec2& position);
		void setVelocity(const Math::Vec2& velocity);

		float getHealth() const;
		float getRadius() const;
		float getSanity() const;
		void setRadius(float rad);

		static void addScript(asIScriptEngine* eng);
		
	private:
		void tick(const Util::Timespan& dt);
		void draw(sf::RenderTarget& rt);

		Kunlaboro::Optional<Math::Vec2> getPositionMsg();
		Kunlaboro::Optional<float> getRadiusMsg();

		float mRadius, mHealth, mSanity, mMaxSanity;
		Math::Vec2 mAimVec, mPosition, mVelocity;
	};
}