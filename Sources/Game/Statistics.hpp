#pragma once

#include "../Util/Time.hpp"

#include <Kunlaboro/Component.hpp>

#include <list>

namespace sf { class RenderTarget; }

namespace Game
{

	class Statistics : public Kunlaboro::Component
	{
	public:
		Statistics();

		void addedToEntity();

		void newFrame(const Util::Timespan& dt);
		void drawUI(sf::RenderTarget& target);
		
	private:
		std::list<int> mFramerates;

		Util::Timespan mCurTime;
		int mCurFrames;
	};

}
