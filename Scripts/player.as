class Player
{

	Player()
	{
		msg = "YOUR AND IDIOT KILL YOU'RE SELVE ";
	}


	void Tick(float dt)
	{
		if (char is null)
		{
			@char = GetCharacter();
			char.Radius = 16;
		}

		Vec2 walkDir, aimDir;

		if (joy.Connected)
		{
			walkDir = Vec2(joy.AxisPosition(sf::Joystick::Axis::X), joy.AxisPosition(sf::Joystick::Axis::Y));
			aimDir = Vec2(joy.AxisPosition(sf::Joystick::Axis::U), joy.AxisPosition(sf::Joystick::Axis::R));
		}
		else
		{
			bool w = sf::Keyboard::IsPressed(sf::Keyboard::Key::W),
				a = sf::Keyboard::IsPressed(sf::Keyboard::Key::A),
				s = sf::Keyboard::IsPressed(sf::Keyboard::Key::S),
				d = sf::Keyboard::IsPressed(sf::Keyboard::Key::D);

			walkDir.X = ((a ? -1 : 0) + (d ? 1 : 0)) * 100;
			walkDir.Y = ((w ? -1 : 0) + (s ? 1 : 0)) * 100;

			if (sf::Mouse::IsPressed(sf::Mouse::Button::Left))
			{
				aimDir = (sf::Mouse::Position - pos);
			}
		}

		if (walkDir.Length < 25)
			walkDir = Vec2();

		vel += (walkDir - vel) * .1 * FT;

		bool shouting = aimDir.Length > 25;
		if (shouting)
			char.AimVec = aimDir.Normalized;
		else
			char.AimVec = Vec2();

		pos += vel * dt * FT;

		char.Position = pos;
	}

	void Update(float dt)
	{
		int oldTime = int(time * 40);
		time += dt * FT;
		if (int(time * 40) != oldTime)
		{
			string c = msg.substr(msg.length - 1, 1);
			msg = c + msg.substr(0, msg.length - 1);
		}
	}

	void Draw(sf::Renderer@ rt)
	{
		sf::View gameView = rt.View;
		gameView.Center = gameView.Center + (pos - gameView.Center) * .001 * FT;
		rt.View = gameView;
	}

	void DrawUI(sf::Renderer@ rt)
	{
		sf::View view = rt.View;

		sf::Shapes::Rectangle rect;

		rect.Size = Vec2(view.Size.X, 105);
		rect.Origin = Vec2(0, 105);
		rect.Position = Vec2(0, view.Size.Y);

		rect.FillColor = sf::Color(12, 12, 179);
		rect.OutlineColor = sf::Colors::Black;
		rect.OutlineThickness = 2;

		rt.Draw(rect);

		rect.Origin = Vec2(0, 128);
		rect.Size = Vec2(196, 124);
		rect.Position = view.Size - Vec2(200, 1);

		rect.Move(2, 2);
		rt.Draw(rect);
		rect.OutlineColor = sf::Color(100, 100, 255);
		rect.Move(-2, -2);

		rt.Draw(rect);

		sf::Text argument;

		argument.CharacterSize = 24;
		argument.Style = sf::Text::Bold | sf::Text::Underlined;
		argument.Color = sf::Colors::Black;
		argument.String = "Strawman";
		Rect b = argument.LocalBounds;
		argument.Origin = b.Size / 2.f;

		argument.Position = view.Size - Vec2(100, 74);
		argument.Rotation = 18 + sin(time) * 3;
		argument.Scale = Vec2(1.2, 1.2) * (1 + abs(sin(time * 2)) / 5);

		rt.Draw(argument);

		rect.Size = Vec2(128, 124);
		rect.Position = view.Size - Vec2(350, 1);
		rect.OutlineColor = sf::Colors::Black;
		rect.Move(2, 2);
		rt.Draw(rect);
		rect.OutlineColor = sf::Color(100, 100, 255);
		rect.Move(-2, -2);
		rt.Draw(rect);

		rt.Draw(rect);
		sf::Text label("AMMO");
		label.Style = sf::Text::Bold;
		b = label.LocalBounds;
		label.Origin = b.Size / 2.f;
		label.Color = sf::Color(179, 179, 255);

		label.Position = view.Size - Vec2(285, 115);

		rt.Draw(label);

		rect.Size = Vec2(128, 124);
		rect.Position = view.Size - Vec2(view.Size.X / 2, 1);
		rect.OutlineColor = sf::Colors::Black;
		rect.Move(2, 2);
		rt.Draw(rect);
		rect.OutlineColor = sf::Color(100, 100, 255);
		rect.Move(-2, -2);
		rt.Draw(rect);
	}

	private Character@ char;

	private float time;
	private string msg;
	private sf::Joystick joy;
	private Vec2 pos, vel;

}