class BouncyBall
{

	BouncyBall()
	{
		time = 0;
		shape = sf::Shapes::Circle(32);
		shape.Origin = Vec2(32, 64);
	}

	void Tick(float dt)
	{
		time += dt;

		Vec2 oldPos = shape.Position;
		shape.Position = Vec2(sf::Mouse::Position.X, view.Size.Y - abs(sin(time)) * 32 * 10);

		float dy = shape.Position.Y - oldPos.Y;

		Vec2 oldScale = shape.Scale;
		if (dy < 0)
		{
			oldScale.X = 1 + dy / -20;
			oldScale.Y = 1;
		}
		else
		{
			oldScale.X = 1;
			oldScale.Y = 1 + dy / 20;
		}
		shape.Scale = oldScale;
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
