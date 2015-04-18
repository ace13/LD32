#include "Character.hpp"
#include <Game/ScriptObject.hpp>
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

Character::Character() : Kunlaboro::Component("Fallacy.Character")
{

}
Character::~Character()
{

}

void Character::addedToEntity()
{
	requestMessage("SetPosition", &Character::setPosition, true);
	requestMessage("GetPosition", (Kunlaboro::Optional<Math::Vec2>(Character::*)())&Character::getPosition, true);
	requestMessage("SetRadius", &Character::setRadius, true);
	requestMessage("GetRadius", (Kunlaboro::Optional<float>(Character::*)())&Character::getRadius, true);
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

Kunlaboro::Optional<Math::Vec2> Character::getPosition()
{
	return mPosition;
}

Kunlaboro::Optional<float> Character::getRadius()
{
	return mRadius;
}
