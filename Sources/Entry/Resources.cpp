#include "Resources.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

sf::SoundBuffer* Resources::getSound(const std::string& name)
{
	static std::unordered_map<std::string, sf::SoundBuffer*> bufs;
	if (bufs.count(name) == 0)
	{
		bufs[name] = new sf::SoundBuffer();
		bufs[name]->loadFromFile(name);
	}

	return bufs[name];
}

sf::Music* Resources::getMusic(const std::string& name)
{
	static std::unordered_map<std::string, sf::Music*> bufs;
	if (bufs.count(name) == 0)
	{
		bufs[name] = new sf::Music();
		bufs[name]->openFromFile(name);
	}

	return bufs[name];
}

sf::Texture* Resources::getTexture(const std::string& name)
{
	static std::unordered_map<std::string, sf::Texture*> bufs;
	if (bufs.count(name) == 0)
	{
		bufs[name] = new sf::Texture();
		bufs[name]->loadFromFile(name);
	}

	return bufs[name];
}
