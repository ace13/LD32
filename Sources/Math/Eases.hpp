#pragma once

#include <functional>

namespace Math
{

	template<typename T>
	class Easer
	{
	public:
		typedef std::function<T(const T&, const T&, float, float)> easeFunc;

		Easer(easeFunc function, float duration);

		T ease(const T& start, const T& end, float time);

	private:
		float mDuration;
		easeFunc mEaser;
	};

	namespace Eases
	{

#define FUNC(name) template<typename T> void name(T&,const T&,float,float)
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
