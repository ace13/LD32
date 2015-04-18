#include "Weapon.hpp"

using namespace Gameplay::Weapon;

Manager& Manager::Singleton()
{
	static Manager* man;
	if (!man)
		man = new Manager();
	return *man;
}

Game::ScriptObject* Manager::createProjectile(const std::string& name)
{
	return nullptr;
}
Game::ScriptObject* Manager::createWeapon(const std::string& name)
{
	return nullptr;
}

void Manager::addProjectile(const std::string& name, asIObjectType* obj)
{

}
void Manager::addWeapon(const std::string& name, asIObjectType* obj)
{

}
