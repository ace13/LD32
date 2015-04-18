#include "GameState.hpp"
#include "FallacyTime.hpp"
#include <Math/Vec2.hpp>

using namespace Gameplay;

GameState::GameState() : Kunlaboro::Component("Fallacy.GameState"),
	ENEMY_DELAY(std::chrono::seconds(5))
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

		float ang = Math::randomFloat(0, Math::TWICE_PI);
		Math::Vec2 playerPos;
		Math::Vec2 pos = playerPos + Math::Vec2(cos(ang), sin(ang)) * 1000.f;

		sendMessageToEntity<void, const Math::Vec2&>(eid, "SetPosition", pos);
	}
}
