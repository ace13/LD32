[Weapon]
class Strawman : IWeapon
{

	Strawman()
	{
		shout.SetBuf(Resources::GetSound("shouting.ogg"));
		shout.Looping = true;
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
				msg = "YOUR AND IDIOT KILL YOU'RE SELVES ";

				shout.Play();
			}
			else
				shout.Pause();
		}
	}

	private sf::Sound shout;

	private float time;
	private bool isFiring;
	private sf::Text wepon;
	private Character@ owner;
	private string msg;

	void Tick(float dt)
	{
		if (!isFiring)
			return;

		shout.Pitch = FT;

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

		if (int(time * 40) % 20 == 0 && oldTime % 20 != 0)
		{
			array<Character@>@ targets = FindInLine(owner.Position, owner.AimVec, 1024);

			for (uint i = 0; i < targets.length; ++i)
			{
				Character@ target = @targets[i];

				target.Damage(0.25, owner.AimVec);
			}
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
