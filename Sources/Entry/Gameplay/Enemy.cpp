#include "Enemy.hpp"
#include "Character.hpp"
#include "FallacyTime.hpp"

using namespace Gameplay;

Enemy::Enemy() : Kunlaboro::Component("Fallacy.Enemy")
{

}
Enemy::~Enemy()
{

}

void Enemy::addedToEntity()
{
	requestComponent("Fallacy.Character", [&](Kunlaboro::Component* comp, Kunlaboro::MessageType msg) {
		if (msg == Kunlaboro::Type_Create)
		{
			mChar = static_cast<Character*>(comp);
			requestMessage("Game.Tick", &Enemy::tick);
		}
		else if (msg == Kunlaboro::Type_Destroy)
		{
			mChar = nullptr;
			unrequestMessage("Game.Tick");
		}
	});
	requestMessage("Fallacies.GetEnemies", &Enemy::getEnemies);
}

void Enemy::tick(const Util::Timespan& dt)
{
	mChar->setPosition(mChar->getPosition() + (Math::Vec2(0, 0) - mChar->getPosition()) * std::chrono::duration<float>(dt).count()/2 * FallacyTimeController::FallacyTime);

	// TODO: Weaponry:
	// Vec2 deltaVec = (enemyPos - playerPos).Normalized();
	// if (deltaVec.dot(weaponVec.Normalized()) < enemyRadius)
	// 
	// ...Or something

	// Move towards player

	// Throw abuse at player when close enough
}

void Enemy::getEnemies(std::list<Enemy*>& enemies)
{
	enemies.push_back(this);
}
