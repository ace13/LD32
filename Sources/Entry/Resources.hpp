#pragma once

#include <string>

namespace sf { class Music; class SoundBuffer; class Texture; }

namespace Resources
{
	sf::SoundBuffer* getSound(const std::string& file);
	sf::Music* getMusic(const std::string& file);
	sf::Texture* getTexture(const std::string& file);
}
