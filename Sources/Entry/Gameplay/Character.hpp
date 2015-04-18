#pragma once

#include <Math/Vec2.hpp>
#include <Kunlaboro/Component.hpp>

class asIScriptEngine;

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
		Kunlaboro::Optional<Math::Vec2> getPosition();
		Kunlaboro::Optional<float> getRadius();

		float mRadius;
		Math::Vec2 mPosition;
	};
}