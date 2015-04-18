#include "Character.hpp"
#include <Game/ScriptObject.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <angelscript.h>

using namespace Gameplay;

namespace
{
	void update(const Math::Vec2& pos, float rad)
	{
		asIScriptObject* obj = reinterpret_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
		Game::ScriptObject* sobj = reinterpret_cast<Game::ScriptObject*>(obj->GetObjectType()->GetUserData((uintptr_t)obj));

		sobj->sendMessage<void, const Math::Vec2&>("SetPosition", pos);
		sobj->sendMessage<void, float>("SetRadius", rad);
	}
}

void Character::addScript(asIScriptEngine* eng)
{
	eng->RegisterGlobalFunction("void UpdateCharacter(Vec2&in,float)", asFUNCTION(update), asCALL_CDECL);
}

Character::Character() : Kunlaboro::Component("Fallacy.Character"),
	mRadius(0), mHealth(1), mSanity(1), mMaxSanity(1)
{

}
Character::~Character()
{

}

void Character::addedToEntity()
{
	requestMessage("SetPosition", &Character::setPosition, true);
	requestMessage("GetPosition", &Character::getPositionMsg, true);
	requestMessage("SetRadius", &Character::setRadius, true);
	requestMessage("GetRadius", &Character::getRadiusMsg , true);

	requestMessage("Game.Draw", &Character::draw);
}

float Character::getRadius() const
{
	return mRadius;
}

void Character::setRadius(float r)
{
	mRadius = r;
}

const Math::Vec2& Character::getPosition() const
{
	return mPosition;
}

void Character::setPosition(const Math::Vec2& pos)
{
	mPosition = pos;
}

void Character::draw(sf::RenderTarget& target)
{
	sf::CircleShape shape(16);
	shape.setOrigin(16, 16);
	shape.setPosition(mPosition);

	target.draw(shape);
}

Kunlaboro::Optional<Math::Vec2> Character::getPositionMsg()
{
	return mPosition;
}

Kunlaboro::Optional<float> Character::getRadiusMsg()
{
	return mRadius;
}
