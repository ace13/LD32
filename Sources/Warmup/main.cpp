#include <GameClass.hpp>

int main(int argc, char** argv)
{
	Kunlaboro::EntitySystem es;
	GameClass::RegisterComponents(es);

	auto eid = es.createEntity();
	es.addComponent(eid, "Game.Statistics");

	GameClass game(es);

	game.init();

	return game.run();
}
