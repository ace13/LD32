class BouncyBall
{

	BouncyBall()
	{
		time = 0;
		shape = sf::Shapes::Circle(32);
		shape.Origin = Vec2(32, 32);

		shape.OutlineThickness = 4;
		shape.OutlineColor = sf::Colors::Black;
	}

	void Tick(float dt)
	{
		time += dt * 2 * FT;

		Vec2 oldPos = shape.Position;
		shape.Position = Vec2(shape.Position.X + (sf::Mouse::Position.X - shape.Position.X) * .1 * FT, view.Size.Y - 32 - abs(sin(time)) * 32 * 10);

		float delta = 1 + (shape.Position - oldPos).Length / 2 / 2 / 2 / 2 / 2 / 2;
		shape.Scale = Vec2(delta, 1 / delta);

		shape.Rotation = (shape.Position - oldPos).Angle * (180 / PI);

		ChangePriority(Priority::Draw, 1);
	}

	void Draw(sf::Renderer@ rt)
	{
		view = rt.View;
		rt.Draw(shape);
	}

	private float time;
	private sf::Shapes::Circle shape;
	private sf::View view;

}
