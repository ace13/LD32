#include "FallacyTime.hpp"

#include <SFML/Window/Event.hpp>
#include <climits>

const float FallacyTimeController::FALLACY_TIME = 0.25;
float FallacyTimeController::FallacyTime = 1;

FallacyTimeController::FallacyTimeController() : Kunlaboro::Component("Fallacy.Time"),
	mEaser(&Math::Eases::easeInCubic<float>, 0.5), mCurState(State_FullSpeed)
{

}
FallacyTimeController::~FallacyTimeController()
{

}

void FallacyTimeController::addedToEntity()
{
	requestMessage("Game.Event", &FallacyTimeController::event);
	requestMessage("Game.Tick", &FallacyTimeController::tick);
	changeRequestPriority("Game.Tick", INT_MIN);
}

void FallacyTimeController::event(const sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::LControl)
		slowDown();
	else if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::LControl)
		speedUp();
}

void FallacyTimeController::tick(const Util::Timespan& dt)
{
	if (mCurState == State_SlowingDown || mCurState == State_SpeedingUp)
	{
		mTime += std::chrono::duration_cast<std::chrono::duration<float>>(dt).count();
		FallacyTime = mEaser.ease(mStart, mTarget, mTime);

		if (FallacyTime == mTarget)
			mCurState = (mCurState == State_SpeedingUp ? State_FullSpeed : State_SlowedDown);
	}
}

void FallacyTimeController::slowDown()
{
	if (mCurState == State_SlowedDown)
		return;
	if (mCurState == State_FullSpeed)
		mTime = 0;

	mCurState = State_SlowingDown;
	mTarget = FALLACY_TIME;
	mStart = 1;
}
void FallacyTimeController::speedUp()
{
	if (mCurState == State_FullSpeed)
		return;
	if (mCurState == State_SlowedDown)
		mTime = 0;

	mCurState = State_SpeedingUp;
	mTarget = 1;
	mStart = FALLACY_TIME;
}
