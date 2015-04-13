#include "Spinor.hpp"

#include <cmath>

using namespace Math;

Spinor Spinor::slerp(const Spinor& s1, const Spinor& s2, float t)
{
	float tr, tc, cosom, scale0, scale1;
	cosom = s1.real * s2.real + s1.complex * s2.complex;

	if (cosom < 0)
	{
		cosom = -cosom;
		tc = -s2.complex;
		tr = -s2.real;
	}
	else
	{
		tc = s2.complex;
		tr = s2.real;
	}

	if (1 - cosom > 0.001f)
	{
		float omega = std::acos(cosom);
		float sinom = std::sin(omega);
		scale0 = sin((1 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		scale0 = 1 - t;
		scale1 = t;
	}

	return Spinor(scale0 * s1.real + scale1 * tr, scale0 * s1.complex + scale1 * tc);
}

Spinor::Spinor() : real(0), complex(0) { }
Spinor::Spinor(float ang) : real(std::cos(ang)), complex(std::sin(ang)) { }
Spinor::Spinor(float r, float c) : real(r), complex(c) { }

Spinor& Spinor::operator +=(const Spinor& rhs)
{
	real += rhs.real; complex += rhs.complex;
	return *this;
}
Spinor& Spinor::operator -=(const Spinor& rhs)
{
	real -= rhs.real; complex -= rhs.complex;
	return *this;
}
Spinor& Spinor::operator *=(const Spinor& rhs)
{
	float newReal = real * rhs.real - complex * rhs.complex;
	complex = real * rhs.complex + complex * rhs.real;
	real = newReal;

	return *this;
}
Spinor& Spinor::operator /=(const Spinor& rhs)
{
	float len = rhs.real * rhs.real + rhs.complex * rhs.complex;
	if (len == 0)
		return *this;

	float newReal = (real * rhs.real - complex * rhs.complex) / len;
	complex = (real * rhs.complex + complex * rhs.real) / len;
	real = newReal;

	return *this;
}
Spinor& Spinor::operator *=(float val)
{
	real *= val; complex *= val;
	return *this;
}
Spinor& Spinor::operator /=(float val)
{
	real /= val; complex /= val;
	return *this;
}

Spinor Spinor::operator +(const Spinor& rhs) const
{
	return Spinor(real + rhs.real, complex + rhs.complex);
}
Spinor Spinor::operator -(const Spinor& rhs) const
{
	return Spinor(real - rhs.real, complex - rhs.complex);
}
Spinor Spinor::operator *(const Spinor& rhs) const
{
	return Spinor(real * rhs.real - complex * rhs.complex, real * rhs.complex + complex * rhs.real);
}
Spinor Spinor::operator /(const Spinor& rhs) const
{
	float len = rhs.real * rhs.real + rhs.complex * rhs.complex;
	if (len == 0)
		return *this;

	return Spinor((real * rhs.real - complex * rhs.complex) / len, (real * rhs.complex + complex * rhs.real) / len);
}
Spinor Spinor::operator *(float val) const
{
	return Spinor(real * val, complex * val);
}
Spinor Spinor::operator /(float val) const
{
	return Spinor(real / val, complex / val);
}

float Spinor::getAngle() const
{
	return std::atan2(complex, real) * 2;
}
float Spinor::getLength() const
{
	return std::sqrt(real * real + complex * complex);
}

void Spinor::setAngle(float ang)
{
	float len = std::sqrt(real * real + complex * complex);
	real = cos(ang) * len;
	complex = sin(ang) * len;
}
void Spinor::setLength(float len)
{
	float oldLen = std::sqrt(real * real + complex * complex);
	if (oldLen == 0)
		return;

	float newLen = len / oldLen;
	real *= newLen;
	complex *= newLen;
}
