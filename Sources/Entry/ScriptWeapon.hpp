#pragma once

#include "Gameplay/Weapon.hpp"
#include <AS_SFML/Common.hpp>
#include <Util/Time.hpp>
#include <Kunlaboro/Component.hpp>

class asIObjectType;
class asIScriptFunction;
class asIScriptObject;
class asIScriptModule;

namespace sf { class RenderTarget; }

class ScriptWeapon : public Kunlaboro::Component
{
public:
	ScriptWeapon();
	ScriptWeapon(const ScriptWeapon&) = delete;
	~ScriptWeapon();

	void addedToEntity();

	void setObject(asIScriptObject*);
	asIScriptObject* getObject();

	const std::string& getName() const;
	Gameplay::Weapon::Type getType() const;

	bool canFire() const;
	bool isFiring() const;

	void startFire();
	void stopFire();

private:
	enum FuncType
	{
		Func_Update,
		Func_Tick,
		Func_Draw,
		Func_DrawUI,

		Func_CanFire,
		Func_GetFire,
		Func_SetFire,

		Func_COUNT
	};

	Kunlaboro::Optional<asIScriptObject*> getObjectMsg(asIScriptModule* mod);
	void setObjectMsg(asIScriptObject* obj, asIScriptModule* mod);
	Kunlaboro::Optional<bool> canFireMsg();
	Kunlaboro::Optional<bool> isFiringMsg();
	void updateFunc(const Util::Timespan& dt);
	void tickFunc(const Util::Timespan& dt);
	void drawFunc(sf::RenderTarget&);
	void drawUIFunc(sf::RenderTarget&);

	asIScriptObject* mObj;

	asIScriptFunction* mFuncs[Func_COUNT];
	std::string mName;
	Gameplay::Weapon::Type mType;
};

