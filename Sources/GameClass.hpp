#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <Kunlaboro/EntitySystem.hpp>

class GameClass
{
public:
	static void RegisterComponents(Kunlaboro::EntitySystem&);
	static GameClass& Singleton();

	GameClass(Kunlaboro::EntitySystem& es);

	void init();

	int run();

	int getTickRate() const;
	void setTickRate(int rate);

	sf::RenderTarget& getTarget();
	sf::RenderWindow& getWindow();

private:
	int mTickRate;
	bool mRunning;

	Kunlaboro::EntitySystem mES;
	sf::RenderWindow mRenderWindow;
};
