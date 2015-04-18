#include "Menu.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

std::string TDs[] = {
	"TD", "TD",
	"TD", "TD",
	"TD", "TD",
	"TD", "TD",
	"TD", "TD",

	"Tasty Doughnuts",
	"They're Delicious",
	"They're Depressing",
	"Though... Damn",
	"Trolling Defender",
	"Twitchy Doctors",

	"Totally Dastardly",
	"Totally Deadened",
	"Totally Defected",
	"Totally Dehumanised",
	"Totally Deranged",
	"Totally Disgusted",
	"Totally Disgusting",

	"Tumblr Debating",
	"Tumblr Deportees",
	"Tumblr Dragons",

	"Typically Demented",
	"Typically Depressing",
	"Typically Deep",
	"Typically Disgraceful"
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
