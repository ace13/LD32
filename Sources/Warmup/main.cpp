#include <GameClass.hpp>
#include <Game/ScriptManager.hpp>
#include <Game/ScriptObject.hpp>
#include <Util/Path.hpp>

#include <ctime>

int main(int argc, char** argv)
{
	Util::setSaneCWD();

	Kunlaboro::EntitySystem es;
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

	sm.getEngine()->RegisterGlobalProperty("const float TIME_LEFT", &timeLeft);

	GameClass::RegisterComponents(es);

	sm.loadScriptFromFile("Scripts/main.as");
	sm.loadScriptFromFile("Scripts/clock.as");

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");
	es.addComponent(eid, "Game.AspectHolder");

	eid = es.createEntity();
	auto obj = sm.createObject("Scripts/main.as", "BouncyBall", es);
	es.addComponent(eid, obj);
	obj = sm.createObject("Scripts/clock.as", "Countdown", es);
	es.addComponent(eid, obj);

	game.init();

	int ret = game.run();

	return ret;
}
