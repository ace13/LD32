#pragma once

namespace Math
{

	struct Spinor
	{
		static Spinor slerp(const Spinor& s1, const Spinor& s2, float t);

		Spinor();
		Spinor(float ang);

		bool operator==(const Spinor& rhs);

		Spinor& operator +=(const Spinor& rhs);
		Spinor& operator -=(const Spinor& rhs);
		Spinor& operator *=(const Spinor& rhs);
		Spinor& operator /=(const Spinor& rhs);
		Spinor& operator *=(float val);
		Spinor& operator /=(float val);

		Spinor operator +(const Spinor& rhs) const;
		Spinor operator -(const Spinor& rhs) const;
		Spinor operator *(const Spinor& rhs) const;
		Spinor operator /(const Spinor& rhs) const;
		Spinor operator *(float val) const;
		Spinor operator /(float val) const;

		float getAngle() const;
		float getLength() const;

		void setAngle(float ang);
		void setLength(float len);

		float Real, Complex;
	};

}
