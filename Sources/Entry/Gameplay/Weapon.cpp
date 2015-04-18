#include "Weapon.hpp"
#include "../ScriptWeapon.hpp"
#include "Game/ScriptManager.hpp"

using namespace Gameplay::Weapon;

Manager& Manager::Singleton()
{
	static Manager* man;
	if (!man)
		man = new Manager();
	return *man;
}
/*
Game::ScriptObject* Manager::createProjectile(Kunlaboro::EntitySystem& es, const std::string& name)
{
	return nullptr;
}
*/
ScriptWeapon* Manager::createWeapon(Kunlaboro::EntitySystem& es, const std::string& name)
{
	auto obj = static_cast<ScriptWeapon*>(es.createComponent("Fallacy.ScriptWeapon"));
	auto eng = Game::ScriptManager::Singleton().getEngine();
	auto type = mWeapons[name];
	obj->setObject(static_cast<asIScriptObject*>(eng->CreateScriptObject(type)));



	return obj;
}

void Manager::addProjectile(const std::string& name, asIObjectType* obj)
{
	mProjectiles[name] = obj;
}
void Manager::addWeapon(const std::string& name, asIObjectType* obj)
{
	mWeapons[name] = obj;
}
