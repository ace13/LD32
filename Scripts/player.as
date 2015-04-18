class Player
{

	Player()
	{
		msg = "YOUR AND IDIOT KILL YOU'RE SELVE ";
	}


	void Tick(float dt)
	{
		if (joy.Connected)
		{
			Vec2 axisPos = Vec2(joy.AxisPosition(sf::Joystick::Axis::X), joy.AxisPosition(sf::Joystick::Axis::Y));

			if (axisPos.Length < 25)
				axisPos = Vec2();

			vel += (axisPos - vel) * .1;

			axisPos = Vec2(joy.AxisPosition(sf::Joystick::Axis::R), joy.AxisPosition(sf::Joystick::Axis::U));
			shouting = axisPos.Length > 25;
			if (shouting)
			{
				wepon.Color = sf::Colors::White;
				wepon.Rotation = axisPos.Angle * (180 / PI);

				float ang = axisPos.Angle;
				if (ang < -HALF_PI || ang > HALF_PI)
					wepon.Scale = Vec2(1, -1);
				else
					wepon.Scale = Vec2(1, 1);
			}
			else
				wepon.Color = sf::Colors::Transparent;
		}

		pos += vel * dt * FT;
		UpdateCharacter(pos, 16);

	}

	void Update(float dt)
	{
		int oldTime = int(time * 10);
		time += dt * FT;
		if (int(time * 10) != oldTime)
		{
			string c = msg.substr(msg.length - 1, 1);
			msg = c + msg.substr(0, msg.length - 1);
		}
	}

	void Draw(sf::Renderer@ rt)
	{
		sf::Shapes::Circle shape(16);
		shape.Origin = Vec2(16, 16);
		shape.Position = pos;

		rt.Draw(shape);

		if (shouting)
		{
			wepon.String = msg;
			Rect b = wepon.LocalBounds;
			wepon.Origin = Vec2(8, b.Size.Y / 2.f + 8);

			wepon.Position = pos;

			rt.Draw(wepon);
		}
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

	private float time;
	private string msg;
	private sf::Joystick joy;
	private Vec2 pos, vel;

	private sf::Text wepon;
	private bool shouting;

}