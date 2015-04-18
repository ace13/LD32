#include "Enemy.hpp"
#include "Character.hpp"

using namespace Gameplay;

Enemy::Enemy() : Kunlaboro::Component("Fallacy.Enemy")
{

}
Enemy::~Enemy()
{

}

void Enemy::addedToEntity()
{
	requestComponent("Fallacies.Character", [&](Kunlaboro::Component* comp, Kunlaboro::MessageType msg) {
		if (msg == Kunlaboro::Type_Create)
			mChar = static_cast<Character*>(comp);
		else if (msg == Kunlaboro::Type_Destroy)
			mChar = nullptr;
	});
	requestMessage("Fallacies.GetEnemies", &Enemy::getEnemies);
}

void Enemy::tick(const Util::Timespan& dt)
{
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
