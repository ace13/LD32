#include <GameClass.hpp>
#include <Game/ScriptManager.hpp>
#include <Game/ScriptObject.hpp>
#include <Util/Path.hpp>

int main(int argc, char** argv)
{
	Util::setSaneCWD();

	Kunlaboro::EntitySystem es;
	GameClass game(es);
	auto& sm = Game::ScriptManager::Singleton();

	GameClass::RegisterComponents(es);

	sm.loadScriptFromFile("Scripts/main.as");

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");

	eid = es.createEntity();
	auto obj = sm.createObject("Scripts/main.as", "BouncyBall", es);
	es.addComponent(eid, obj);

	game.init();

	int ret = game.run();

	delete &Game::ScriptManager::Singleton();

	return ret;
}
