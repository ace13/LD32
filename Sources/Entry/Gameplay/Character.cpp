#include "Character.hpp"
#include "FallacyTime.hpp"
#include <Game/ScriptObject.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <scriptarray/scriptarray.h>
#include <angelscript.h>

using namespace Gameplay;

namespace
{
	void* getCharacter()
	{
		asIScriptObject* obj = reinterpret_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
		Kunlaboro::Component* sobj = reinterpret_cast<Kunlaboro::Component*>(obj->GetObjectType()->GetUserData((uintptr_t)obj));

		return sobj->getEntitySystem()->getAllComponentsOnEntity(sobj->getOwnerId(), "Fallacy.Character")[0];
	}

	CScriptArray* findInRadius(const Math::Vec2& pos, float radius)
	{
		std::list<Character*> list;

		asIScriptObject* obj = reinterpret_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
		Kunlaboro::Component* sobj = reinterpret_cast<Kunlaboro::Component*>(obj->GetObjectType()->GetUserData((uintptr_t)obj));

		sobj->sendMessage<void, std::list<Character*>&>("Fallacy.GetEnemies", list);

		auto ret = CScriptArray::Create(obj->GetEngine()->GetObjectTypeByDecl("array<Character@>"));
		for (auto& val : list)
			if (val->getPosition().getDistance(pos) < radius)
			ret->InsertLast(val);

		return ret;
	}

	CScriptArray* findInLine(const Math::Vec2& pos, const Math::Vec2& dir, float radius, float lineThickness)
	{
		std::list<Character*> list;

		asIScriptObject* obj = reinterpret_cast<asIScriptObject*>(asGetActiveContext()->GetThisPointer());
		Kunlaboro::Component* sobj = reinterpret_cast<Kunlaboro::Component*>(obj->GetObjectType()->GetUserData((uintptr_t)obj));

		sobj->sendGlobalMessage<void, std::list<Character*>&>("Fallacy.GetEnemies", list);

		auto ret = CScriptArray::Create(obj->GetEngine()->GetObjectTypeByDecl("array<Character@>"));
		for (auto& val : list)
		{
			if (!val)
				continue;

			auto dirCopy = dir;
			auto diff = (val->getPosition() - pos);
			dirCopy.setLength(diff.getLength());
			if (diff.getDistance(dirCopy) < val->getRadius() + lineThickness && diff.getLength() < radius)
				ret->InsertLast(&val);
		}

		return ret;
}

#ifndef AS_SUPPORT_VALRET
	void findInRadius_generic(asIScriptGeneric* gen)
	{
		Math::Vec2* v = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		float rad = gen->GetArgFloat(1);

		gen->SetReturnObject(findInRadius(*v, rad));
	}

	void findInLine_generic(asIScriptGeneric* gen)
	{
		Math::Vec2* v = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(0));
		Math::Vec2* v2 = reinterpret_cast<Math::Vec2*>(gen->GetArgObject(1));
		float rad = gen->GetArgFloat(2);
		float lineThick = gen->GetArgFloat(3);

		gen->SetReturnObject(findInLine(*v, *v2, rad, lineThick));
	}
#endif

}

void Character::addScript(asIScriptEngine* eng)
{
	eng->RegisterObjectType("Character", 0, asOBJ_REF | asOBJ_NOCOUNT);
	eng->RegisterGlobalFunction("Character@ GetCharacter()", asFUNCTION(getCharacter), asCALL_CDECL);

	eng->RegisterObjectMethod("Character", "const Vec2& get_AimVec() const", asMETHOD(Character, getAimVec), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "const Vec2& get_Position() const", asMETHOD(Character, getPosition), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "const Vec2& get_Velocity() const", asMETHOD(Character, getVelocity), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "void set_AimVec(Vec2&in) const", asMETHOD(Character, setAimVec), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "void set_Position(Vec2&in) const", asMETHOD(Character, setPosition), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "void set_Velocity(Vec2&in) const", asMETHOD(Character, setVelocity), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "float get_Radius() const", asMETHOD(Character, getRadius), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "void set_Radius(float) const", asMETHOD(Character, setRadius), asCALL_THISCALL);

	eng->RegisterObjectMethod("Character", "void Damage(float, Vec2&in)", asMETHOD(Character, damage), asCALL_THISCALL);
	eng->RegisterObjectMethod("Character", "void Kill()", asMETHOD(Character, kill), asCALL_THISCALL);

#ifdef AS_SUPPORT_VALRET
	eng->RegisterGlobalFunction("array<Character@>@ FindInRadius(Vec2&in, float)", asFUNCTION(findInRadius), asCALL_CDECL);
	eng->RegisterGlobalFunction("array<Character@>@ FindInLine(Vec2&in, Vec2&in, float, float = 0)", asFUNCTION(findInLine), asCALL_CDECL);
#else
	eng->RegisterGlobalFunction("array<Character@>@ FindInRadius(Vec2&in, float)", asFUNCTION(findInRadius_generic), asCALL_GENERIC);
	eng->RegisterGlobalFunction("array<Character@>@ FindInLine(Vec2&in, Vec2&in, float, float = 0)", asFUNCTION(findInLine_generic), asCALL_GENERIC);
#endif
}

Character::Character() : Kunlaboro::Component("Fallacy.Character"),
	mRadius(0), mHealth(10), mSanity(10), mMaxSanity(10)
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
	requestMessage("Game.Tick", &Character::tick);
}

void Character::damage(float dmg, const Math::Vec2& dir)
{
	if (mSanity > 0)
	{
		float dmgC = dmg;
		dmg -= mSanity;
		mSanity -= dmgC;

		if (mSanity < 0)
			mSanity = 0;
	}

	if (dmg > 0)
		mHealth -= dmg;

	mPosition += dir.getRotated(Math::randomFloat(-Math::HALF_PI / 2, Math::HALF_PI / 2)) * mRadius;

	if (mHealth < 0)
		kill();
}

void Character::kill()
{
	getEntitySystem()->destroyEntity(getOwnerId());
}

float Character::getRadius() const
{
	return mRadius;
}

void Character::setRadius(float r)
{
	mRadius = r;
}

const Math::Vec2& Character::getAimVec() const
{
	return mAimVec;
}
const Math::Vec2& Character::getPosition() const
{
	return mPosition;
}
const Math::Vec2& Character::getVelocity() const
{
	return mVelocity;
}
void Character::setAimVec(const Math::Vec2& aim)
{
	if (aim != Math::Vec2() && mAimVec == Math::Vec2())
	{
		sendMessage<void>("StartFiring");
	}
	else if (aim == Math::Vec2() && mAimVec != Math::Vec2())
	{
		sendMessage<void>("StopFiring");
	}

	mAimVec = aim;
}
void Character::setPosition(const Math::Vec2& pos)
{
	mPosition = pos;
}
void Character::setVelocity(const Math::Vec2& v)
{
	mVelocity = v;
}

void Character::draw(sf::RenderTarget& target)
{
	sf::CircleShape shape(16);
	shape.setOrigin(16, 16);
	shape.setPosition(mPosition);

	uint8_t a = 255;
	uint8_t gb = 255;

	if (mSanity < mMaxSanity)
		gb *= (mSanity / mMaxSanity);
	if (mHealth < 10)
		a *= (mHealth / 10.0);

	shape.setFillColor(sf::Color(255, gb, gb, a));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1);

	target.draw(shape);
}

void Character::tick(const Util::Timespan& dt)
{
	if (mSanity < mMaxSanity)
	{
		mSanity += std::min(mMaxSanity, std::chrono::duration<float>(dt).count() * FallacyTimeController::FallacyTime);
	}
}

Kunlaboro::Optional<Math::Vec2> Character::getPositionMsg()
{
	return mPosition;
}

Kunlaboro::Optional<float> Character::getRadiusMsg()
{
	return mRadius;
}
