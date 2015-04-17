#include "AspectHolder.hpp"
#include "../Math/Vec2.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

using namespace Game;
AspectHolder::AspectHolder() : Kunlaboro::Component("Game.AspectHolder"),
	mDirtied(false)
{

}
AspectHolder::~AspectHolder()
{

}


void AspectHolder::addedToEntity()
{
	requestMessage("Game.Event", &AspectHolder::onEvent);
	requestMessage("Game.Draw", &AspectHolder::draw);
	changeRequestPriority("Game.Draw", INT_MIN);
}

void AspectHolder::onEvent(const sf::Event& ev)
{
	if (ev.type == sf::Event::Resized)
		mDirtied = true;
}
void AspectHolder::draw(sf::RenderTarget& rt)
{
	if (!mDirtied)
		return;

	static float size = 0;
	if (size == 0)
	{
		Math::Vec2 start = rt.getDefaultView().getSize();
		size = start.getLength();
	}

	Math::Vec2 newSize = rt.getSize();
	newSize.setLength(size);

	auto view = rt.getView();

	view.setSize(newSize);
	view.setCenter(newSize / 2.f);

	rt.setView(view);

	mDirtied = false;
}