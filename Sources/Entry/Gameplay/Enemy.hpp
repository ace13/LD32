#pragma once

#include <Kunlaboro/Component.hpp>

namespace Gameplay
{

	class Enemy : public Kunlaboro::Component
	{
	public:
		Enemy();
		~Enemy();

		void addedToEntity();

	private:

	};

}