[Weapon]
class Strawman : IWeapon
{

	Strawman()
	{

	}

	string Name { get const { return "Strawman"; } }
	WeaponType Type { get const { return WeaponType::Beam; } }
	bool CanFire { get const { return true; } }
	bool Firing { get const { return isFiring; }
		set 
		{
			isFiring = value;

			if (isFiring)
			{
				@owner = GetCharacter();
				msg = "YOUR AND IDIOT KILL YOU'RE SELVE ";
			}
		}
	}

	private float time;
	private bool isFiring;
	private sf::Text wepon;
	private Character@ owner;
	private string msg;

	void Tick(float dt)
	{
		if (!isFiring)
			return;

		float ang = owner.AimVec.Angle;
		if (ang < -HALF_PI || ang > HALF_PI)
			wepon.Scale = Vec2(1, -1);
		else
			wepon.Scale = Vec2(1, 1);

		wepon.Rotation = ang * (180 / PI);

		int oldTime = int(time * 40);
		time += dt * FT;
		if (int(time * 40) != oldTime)
		{
			string c = msg.substr(msg.length - 1, 1);
			msg = c + msg.substr(0, msg.length - 1);
		}

		if (int(time * 40) % 40 == 0 && oldTime % 40 != 0)
		{
			// array<Character@>@ targets = FindInLine();
		}
	}

	void Update(float dt)
	{
		if (!isFiring)
			return;

		wepon.Position = owner.Position;
	}

	void Draw(sf::Renderer@ rt)
	{
		if (!isFiring)
			return;

		wepon.String = msg;
		Rect b = wepon.LocalBounds;
		wepon.Origin = Vec2(8, b.Size.Y / 2.f + 8);

		rt.Draw(wepon);
	}
}
