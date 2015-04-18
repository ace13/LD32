#pragma once

#include <Math/Eases.hpp>
#include <Util/Time.hpp>
#include <Kunlaboro/Component.hpp>

namespace sf { class Event; }

class FallacyTimeController : public Kunlaboro::Component
{
public:
	static float FallacyTime;

	FallacyTimeController();
	~FallacyTimeController();

	void addedToEntity();

private:
	static const float FALLACY_TIME;

	void event(const sf::Event& ev);
	void tick(const Util::Timespan& dt);

	void slowDown();
	void speedUp();

	enum State
	{
		State_FullSpeed,
		State_SlowingDown,
		State_SlowedDown,
		State_SpeedingUp
	};

	State mCurState;
	Math::Easer<float> mEaser;
	float mStart, mTarget, mTime;
};
