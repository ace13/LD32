#include "Statistics.hpp"
#include "../Util/DefaultFont.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cstdio>

using namespace Game;

Statistics::Statistics() :
	Kunlaboro::Component("Game.Statistics"),
	mCurFrames(0)
{

}

void Statistics::addedToEntity()
{
	requestMessage("Game.Update", &Statistics::newFrame);
	requestMessage("Game.DrawUI", &Statistics::drawUI);
}

void Statistics::newFrame(const Util::Timespan& dt)
{
	mCurTime += dt;
	if (mCurTime >= std::chrono::seconds(1))
	{
		mCurTime -= std::chrono::seconds(1);

		mFramerates.push_front(mCurFrames);
		if (mFramerates.size() > 10)
			mFramerates.pop_back();

		mCurFrames = 0;
	}
}

void Statistics::drawUI(sf::RenderTarget& target)
{
	static sf::Font font = Util::getDefaultFont();

	++mCurFrames;
	if (mFramerates.empty())
		return;

	float avg5FPS = 0, avg10FPS = 0;
	auto it = mFramerates.begin();
	for (int i = 0; it != mFramerates.end(); ++i, ++it)
	{
		if (i < 5)
			avg5FPS += *it;
		avg10FPS += *it;
	}

	avg5FPS /= 5;
	avg10FPS /= 10;

	char text[256];
	std::sprintf(text, "FPS: %5d %8.2f %8.2f", mFramerates.front(), avg5FPS, avg10FPS);

	sf::Text fpsText(text, font, 14u);
	fpsText.setPosition(target.getView().getSize().x - fpsText.getGlobalBounds().width - 5, 5);
	fpsText.setColor(sf::Color(179, 179, 0));

	target.draw(fpsText);
}
