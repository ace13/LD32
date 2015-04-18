#include "Gameplay/Character.hpp"
#include "Gameplay/FallacyTime.hpp"
#include "Gameplay/GameState.hpp"
#include "Menu.hpp"
#include "Resources.hpp"

#include <GameClass.hpp>
#include <Game/ScriptManager.hpp>
#include <Game/ScriptObject.hpp>
#include <Util/Path.hpp>

#include <ctime>

int main(int argc, char** argv)
{
	Util::setSaneCWD();

	Kunlaboro::EntitySystem es;
	es.registerComponent<Gameplay::Character>("Fallacy.Character");
	es.registerComponent<Gameplay::GameState>("Fallacy.GameState");
	es.registerComponent<Menu>("Fallacy.Menu");
	es.registerComponent<FallacyTimeController>("Fallacy.Time");
	GameClass game(es);
	auto& sm = Game::ScriptManager::Singleton();

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



	GameClass::RegisterComponents(es);

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");
	es.addComponent(eid, "Game.AspectHolder");
	es.addComponent(eid, "Fallacy.Time");

	es.addComponent(eid, "Fallacy.GameState");

	eid = es.createEntity();
	es.addComponent(eid, sm.createObject("Scripts/player.as", "Player", es));
	es.addComponent(eid, "Fallacy.Character");

	game.init();

	int ret = game.run();

	return ret;
}
