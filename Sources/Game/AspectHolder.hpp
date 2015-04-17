#pragma once

#include <Kunlaboro/Component.hpp>

namespace sf { class Event; class RenderTarget; }

namespace Game
{

	class AspectHolder : public Kunlaboro::Component
	{
	public:
		AspectHolder();
		~AspectHolder();

		void addedToEntity();

	private:
		void onEvent(const sf::Event&);
		void draw(sf::RenderTarget&);

		bool mDirtied;
	};

}
