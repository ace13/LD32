#include "Gameplay/Character.hpp"
#include "Gameplay/Enemy.hpp"
#include "Gameplay/FallacyTime.hpp"
#include "Gameplay/GameState.hpp"
#include "Gameplay/Weapon.hpp"
#include "Menu.hpp"
#include "Resources.hpp"
#include "ScriptWeapon.hpp"

#include <GameClass.hpp>
#include <Game/ScriptManager.hpp>
#include <Game/ScriptObject.hpp>
#include <Util/Path.hpp>

#include <ctime>

void addWeapon(asIObjectType* obj)
{
	Gameplay::Weapon::Manager::Singleton().addWeapon(obj->GetName(), obj);
}

void addProjectile(asIObjectType* obj)
{
	Gameplay::Weapon::Manager::Singleton().addProjectile(obj->GetName(), obj);
}

int main(int argc, char** argv)
{
	Util::setSaneCWD();

	Kunlaboro::EntitySystem es;
	es.registerComponent<Gameplay::Character>("Fallacy.Character");
	es.registerComponent<Gameplay::Enemy>("Fallacy.Enemy");
	es.registerComponent<Gameplay::GameState>("Fallacy.GameState");
	es.registerComponent<Menu>("Fallacy.Menu");
	es.registerComponent<FallacyTimeController>("Fallacy.Time");
	es.registerComponent<ScriptWeapon>("Fallacy.ScriptWeapon");

	es.registerTemplate("Fallacy.Enemy", std::vector<std::string> { "Fallacy.Character", "Fallacy.Enemy" });


	GameClass game(es);
	auto& sm = Game::ScriptManager::Singleton();
	sm.addMetaCallback("Weapon", addWeapon);
	sm.addMetaCallback("Projectile", addProjectile);

	float timeLeft;
	{
		std::chrono::system_clock::time_point targetTime;

		tm inp;
		inp.tm_sec = inp.tm_min = 0;
		inp.tm_hour = 3;
		inp.tm_mday = 18;
		inp.tm_mon = 3;
		inp.tm_year = 115;

		time_t time = mktime(&inp);
		targetTime = std::chrono::system_clock::from_time_t(time);

		timeLeft = std::chrono::duration_cast<std::chrono::duration<float>>(targetTime - std::chrono::system_clock::now()).count();
	}

	auto eng = sm.getEngine();
	Gameplay::Character::addScript(eng);
	eng->RegisterGlobalProperty("const float TIME_LEFT", &timeLeft);
	eng->RegisterGlobalProperty("const float FT", &FallacyTimeController::FallacyTime);

	eng->SetDefaultNamespace("Resources");
	eng->RegisterGlobalFunction("sf::SoundBuf@ GetSound(string&in)", asFUNCTION(Resources::getSound), asCALL_CDECL);
	eng->RegisterGlobalFunction("sf::Music@ GetMusic(string&in)", asFUNCTION(Resources::getMusic), asCALL_CDECL);
	eng->SetDefaultNamespace("");

	eng->RegisterEnum("WeaponType");
	eng->RegisterEnumValue("WeaponType", "Beam", Gameplay::Weapon::Type_Beam);
	eng->RegisterEnumValue("WeaponType", "Cone", Gameplay::Weapon::Type_Cone);
	eng->RegisterEnumValue("WeaponType", "Projectile", Gameplay::Weapon::Type_Projectile);

	eng->RegisterInterface("IWeapon");
	eng->RegisterInterfaceMethod("IWeapon", "string get_Name() const");
	eng->RegisterInterfaceMethod("IWeapon", "WeaponType get_Type() const");
	eng->RegisterInterfaceMethod("IWeapon", "bool get_CanFire() const");
	eng->RegisterInterfaceMethod("IWeapon", "bool get_Firing() const");
	eng->RegisterInterfaceMethod("IWeapon", "void set_Firing(bool)");

	for (auto& weapon : Util::getFilesInDir("Scripts/Weapons"))
		sm.loadScriptFromFile(weapon);

	GameClass::RegisterComponents(es);

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");
	es.addComponent(eid, "Game.AspectHolder");
	es.addComponent(eid, "Fallacy.Time");

	es.addComponent(eid, "Fallacy.GameState");

	eid = es.createEntity();
	es.addComponent(eid, sm.createObject("Scripts/player.as", "Player", es));
	es.addComponent(eid, "Fallacy.Character");
	es.addComponent(eid, Gameplay::Weapon::Manager::Singleton().createWeapon(es, "Strawman"));

	game.init();

	int ret = game.run();

	return ret;
}
