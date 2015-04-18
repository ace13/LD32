#include "Enemy.hpp"

using namespace Gameplay;

Enemy::Enemy() : Kunlaboro::Component("Fallacy.Enemy")
{

}
Enemy::~Enemy()
{

}

void Enemy::addedToEntity()
{

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
