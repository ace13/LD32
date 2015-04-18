class Countdown
{

	Countdown()
	{
		time = TIME_LEFT;
	}

	void Tick(float dt)
	{
		int oldTime = int(time);
		time -= dt * FT;

		if (int(time) != oldTime)
		{
			//tick.Play();
		}
	}

	void Draw(sf::Renderer@ rt)
	{
		{
			int h = -int(ceil(time / 60 / 60));
			int m = -int(ceil((time % 3600) / 60));
			int s = -int(ceil(time % 60));

			sf::Text countdown((h < 10 ? "0" : "") + h + ":" + (m < 10 ? "0" : "") + m + ":" + (s < 10 ? "0" : "") + s + " into LD32 \"An Unconventional Weapon\"");

			rt.Draw(countdown);
		}

		sf::Shapes::Circle backface(128, 60);
		backface.Position = rt.View.Center;
		backface.Origin = Vec2(128, 128);
		backface.Scale = Vec2(1.6, 1.6);
		backface.OutlineColor = sf::Colors::White;
		backface.OutlineThickness = 1.2;
		backface.FillColor = sf::Color(48, 48, 48, 255);

		rt.Draw(backface);

		backface.Scale = Vec2(1, 1);
		backface.FillColor = sf::Color(64, 64, 64, 255);
		backface.OutlineThickness = 4.f;

		rt.Draw(backface);

		sf::Shapes::Rectangle line(Vec2(128, 1));
		line.FillColor = sf::Colors::Transparent;
		line.OutlineThickness = 2;
		line.OutlineColor = sf::Colors::Red;
		line.Origin = Vec2(32, 0.5);
		line.Position = rt.View.Center;

		line.Rotation = 270 - (time) * (360 / 60);

		rt.Draw(line);

		line.Size = Vec2(128, 4);
		line.Origin = Vec2(32, 2);
		line.FillColor = sf::Colors::White;
		line.OutlineColor = sf::Colors::Transparent;
		line.OutlineThickness = 0;

		line.Rotation = 270 - ceil((time % 3600) / 60) * (360 / 60);

		rt.Draw(line);

		line.Size = Vec2(100, 4);
		line.Origin = Vec2(32, 2);

		line.Rotation = 270 - ceil(time / 60 / 60) * (360 / 24);

		rt.Draw(line);

		for (int i = 60; i > 0; i -= 5)
		{
			sf::Text digit("" + i);
			Rect b = digit.LocalBounds;
			digit.Origin = Vec2(b.Width / 2, b.Height / 2) + Vec2(0, 6);

			digit.Position = rt.View.Center + Vec2(cos(i * (TWICE_PI / 60.0) - HALF_PI) * 175, sin(i * (TWICE_PI / 60.0) - HALF_PI) * 175);

			rt.Draw(digit);
		}
	}

	private float time;

}
