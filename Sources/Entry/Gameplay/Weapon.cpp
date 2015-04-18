#include "Weapon.hpp"
#include "Game/ScriptManager.hpp"

using namespace Gameplay::Weapon;

Manager& Manager::Singleton()
{
	static Manager* man;
	if (!man)
		man = new Manager();
	return *man;
}

Game::ScriptObject* Manager::createProjectile(Kunlaboro::EntitySystem& es, const std::string& name)
{
	return nullptr;
}
Game::ScriptObject* Manager::createWeapon(Kunlaboro::EntitySystem& es, const std::string& name)
{
	auto obj = static_cast<Game::ScriptObject*>(es.createComponent("Game.ScriptObject"));
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
