#pragma once

#include <Kunlaboro/Component.hpp>
#include <Util/Time.hpp>
#include <list>

namespace Gameplay
{

	class Character;

	class Enemy : public Kunlaboro::Component
	{
	public:
		Enemy();
		~Enemy();

		void addedToEntity();

	private:
		void tick(const Util::Timespan& dt);
		void getEnemies(std::list<Enemy*>& enemies);

		Character* mChar;
	};

}