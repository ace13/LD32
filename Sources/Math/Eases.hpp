#pragma once

#include <functional>

namespace Math
{

	template<typename T>
	class Easer
	{
	public:
		typedef std::function<T(const T&, const T&, float, float)> EaseFunc;

		Easer(EaseFunc function, float duration);
		Easer(const Easer&) = default;
		~Easer() = default;

		Easer& operator=(const Easer&) = default;

		T ease(const T& start, const T& end, float time);

		float getDuration() const;
		void setDuration(float d);

	private:
		float mDuration;
		EaseFunc mEaser;
	};

	namespace Eases
	{

#define FUNC(name) template<typename T> T name(const T&,const T&,float,float)
#define METHOD(name) FUNC(easeIn ## name); FUNC(easeOut ## name); FUNC(easeInOut ## name)

		METHOD(Back);
		METHOD(Bounce);
		METHOD(Circ);
		METHOD(Cubic);
		METHOD(Elastic);
		METHOD(Expo);
		METHOD(Quad);
		METHOD(Quart);
		METHOD(Quint);
		METHOD(Sine);

#undef FUNC
#undef METHOD

	}

}

#include "Eases.inl"
