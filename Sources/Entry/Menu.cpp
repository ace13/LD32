#include "Menu.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Menu::Menu() : Kunlaboro::Component("Fallacy.Menu")
{

}
Menu::~Menu()
{

}

void Menu::addedToEntity()
{
	requestMessage("Game.Update", &Menu::update);
	requestMessage("Game.DrawUI", &Menu::drawUI);
}

void Menu::update(const Util::Timespan& dt)
{

}

void Menu::drawUI(sf::RenderTarget& target)
{

}
