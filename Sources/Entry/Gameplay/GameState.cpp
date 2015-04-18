#include "GameState.hpp"
#include "FallacyTime.hpp"
#include <Math/Vec2.hpp>

using namespace Gameplay;

GameState::GameState() : Kunlaboro::Component("Fallacy.GameState"),
	ENEMY_DELAY(std::chrono::seconds(1))
{

}

void GameState::addedToEntity()
{
	requestMessage("Game.Tick", &GameState::tick);
}

void GameState::tick(Util::Timespan& dt)
{
	mTimeLeft -= std::chrono::duration_cast<Util::Timespan>(dt * FallacyTimeController::FallacyTime);
	if (mTimeLeft.count() < 0)
	{
		mTimeLeft = ENEMY_DELAY;

		auto eid = getEntitySystem()->createEntity("Fallacy.Enemy");
		sendMessageToEntity<void, const Math::Vec2&>(eid, "SetPosition", Math::Vec2());
	}
}
