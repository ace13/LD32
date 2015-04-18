#include "Menu.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

std::string TDs[] = {
	"TD",
	"TD",
	"TD",
	"TD",
	"TD",

	"Though... Damn",

	"Totally Dastardly",
	"Totally Deranged",
	"Totally Disgusted",
	"Totally Disgusting",

	"Tumblr Debating",
	"Tumblr Deportees",

	"Typically Demented"
};

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
