#include "GameClass.hpp"
#include "Game/AspectHolder.hpp"
#include "Game/ScriptManager.hpp"
#include "Game/ScriptObject.hpp"
#include "Game/Statistics.hpp"
#include "Util/Time.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>

namespace
{
	GameClass* sSingleton;
}

void GameClass::RegisterComponents(Kunlaboro::EntitySystem& es)
{
	es.registerComponent<Game::AspectHolder>("Game.AspectHolder");
	es.registerComponent<Game::Statistics>("Game.Statistics");
	es.registerComponent<Game::ScriptObject>("Game.ScriptObject");
}

GameClass& GameClass::Singleton()
{
	return *sSingleton;
}

GameClass::GameClass(Kunlaboro::EntitySystem& es) :
	mTickRate(66), mRunning(false), mES(es)
{
	sSingleton = this;
}

void GameClass::init()
{
	mRenderWindow.create(sf::VideoMode(1024, 768), "LD32 Game");
}

int GameClass::run()
{
	mRunning = true;

	Util::Timespan tickDuration = std::chrono::nanoseconds(1000000000 / mTickRate);

	sf::Event ev;
	Util::Timestamp lastFrame = Util::ClockImpl::now();
	Util::Timespan totalTime;
	Kunlaboro::RequestId eventID = Kunlaboro::hash::hashString("Game.Event"),
		drawID = Kunlaboro::hash::hashString("Game.Draw"),
		drawUIID = Kunlaboro::hash::hashString("Game.DrawUI"),
		tickID = Kunlaboro::hash::hashString("Game.Tick"),
		updateID = Kunlaboro::hash::hashString("Game.Update");
	sf::View gameView;

	while (mRenderWindow.isOpen() && mRunning)
	{
		Util::Timestamp now = Util::ClockImpl::now();
		Util::Timespan frameTime = now - lastFrame;

		auto count = frameTime.count();
		frameTime = Util::Timespan(std::max(0l, std::min((long)count, 50000000l)));

		totalTime += frameTime;

		while (mRenderWindow.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				mRenderWindow.close();

			mES.sendUnsafeGlobalMessage<void, const sf::Event&>(eventID, ev);
		}

		while (totalTime >= tickDuration)
		{
			totalTime -= tickDuration;
			mES.sendUnsafeGlobalMessage<void, const Util::Timespan&>(tickID, tickDuration);
		}

		mES.sendUnsafeGlobalMessage<void, const Util::Timespan&>(updateID, frameTime);

		mRenderWindow.clear();

		mES.sendSafeGlobalMessage<void, sf::RenderTarget&>(drawID, mRenderWindow);

		gameView = mRenderWindow.getView();
		mRenderWindow.setView(sf::View(sf::Vector2f(mRenderWindow.getSize() / 2u), (sf::Vector2f)mRenderWindow.getSize()));

		mES.sendSafeGlobalMessage<void, sf::RenderTarget&>(drawUIID, mRenderWindow);

		mRenderWindow.setView(gameView);

		mRenderWindow.display();

		Game::ScriptManager::Singleton().checkForUpdates();
		lastFrame = now;
	}

	return 0;
}

int GameClass::getTickRate() const
{
	return mTickRate;
}
void GameClass::setTickRate(int rate)
{
	mTickRate = rate;
}

sf::RenderTarget& GameClass::getTarget()
{
	return mRenderWindow;
}
sf::RenderWindow& GameClass::getWindow()
{
	return mRenderWindow;
}
