#pragma once

#include <Kunlaboro/Component.hpp>

namespace Gameplay
{

	class GameState : public Kunlaboro::Component
	{
	public:
		GameState();
		~GameState() = default;

		void addedToEntity();

	private:

	};

}