#pragma once

#include <Kunlaboro/Component.hpp>
#include <Util/Time.hpp>

namespace sf { class RenderTarget; }

class Menu : public Kunlaboro::Component
{
public:
	Menu();
	~Menu();

	void addedToEntity();

private:
	void update(const Util::Timespan& dt);
	void drawUI(sf::RenderTarget& rt);
};
