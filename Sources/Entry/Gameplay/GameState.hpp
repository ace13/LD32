#pragma once

#include <Kunlaboro/Component.hpp>
#include <Util/Time.hpp>

namespace Gameplay
{

	class GameState : public Kunlaboro::Component
	{
	public:
		GameState();
		~GameState() = default;

		void addedToEntity();

	private:
		void tick(Util::Timespan& dt);

		Util::Timespan ENEMY_DELAY, mTimeLeft;
	};

}