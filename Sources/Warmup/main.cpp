#include <GameClass.hpp>
#include <Game/ScriptManager.hpp>

int main(int argc, char** argv)
{
	Kunlaboro::EntitySystem es;
	GameClass game(es);
	Game::ScriptManager::Singleton();

	GameClass::RegisterComponents(es);

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");

	game.init();

	int ret = game.run();

	delete &Game::ScriptManager::Singleton();

	return ret;
}
