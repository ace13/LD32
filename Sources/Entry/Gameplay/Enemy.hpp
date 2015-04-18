#pragma once

#include <Kunlaboro/Component.hpp>
#include <Util/Time.hpp>

namespace Gameplay
{

	class Enemy : public Kunlaboro::Component
	{
	public:
		Enemy();
		~Enemy();

		void addedToEntity();

	private:
		void tick(const Util::Timespan& dt);
	};

}