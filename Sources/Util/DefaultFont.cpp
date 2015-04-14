#include "DefaultFont.hpp"

using namespace Util;

namespace
{
	static const std::array<std::string,
#ifdef WIN32
		3
#else
		6
#endif
	> DefaultFonts =
#ifdef WIN32
	{
		"C:\\Windows\\Fonts\\Arial.ttf",
		"Fallback.ttf",
		"Fallback.otf"
	};
#else
	{
		"/usr/share/fonts/corefonts/arial.ttf",
		"/usr/share/fonts/dejavu/DejaVuSans.ttf",
		"/usr/share/fonts/droid/DroidSans.ttf",
		"/usr/share/fonts/ttf-bitstream-vera/Vera.ttf",
		"fallback.ttf",
		"fallback.otf"
	};
#endif
}

sf::Font& Util::getDefaultFont()
{
	static sf::Font* sFont = nullptr;

	if (!sFont)
	{
		sFont = new sf::Font();

		bool loaded = false;
		for (auto& file : DefaultFonts)
			if (sFont->loadFromFile(file))
			{
				loaded = true;
				break;
			}

		if (!loaded)
			throw new std::runtime_error("Failed to find a suitable font, copy or symlink a font into a 'fallback.ttf' or 'fallback.otf' file next to this executable.");
	}

	return *sFont;
}
