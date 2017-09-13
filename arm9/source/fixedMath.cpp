#include "fixedMath.h"

fp8 operator "" _fp8(unsigned long long x) { return fp8(x); }
fp12 operator "" _fp12(unsigned long long x) { return fp12(x); }

FixedAngle operator "" _fixedAngle(unsigned long long x) {
	return FixedAngle(degreesToAngle(x));
}

FixedAngle::FixedAngle() {}
FixedAngle::FixedAngle(s16 rawAngle) : raw(rawAngle) {}

FixedAngle::operator bool() const { return (bool)raw; }
FixedAngle::operator float() const {
	return angleToDegrees((float)(raw));
};

FixedAngle &FixedAngle::operator =(const FixedAngle &f2) { raw = f2.raw; return *this; }
FixedAngle &FixedAngle::operator +=(const FixedAngle &f2) { raw += f2.raw; return *this; }
FixedAngle &FixedAngle::operator -=(const FixedAngle &f2) { raw -= f2.raw; return *this; }
FixedAngle &FixedAngle::operator *=(const FixedAngle &f2) { raw = raw * f2.raw; return *this; }
FixedAngle &FixedAngle::operator &=(const FixedAngle &f2) { raw &= f2.raw; return *this; }
FixedAngle &FixedAngle::operator |=(const FixedAngle &f2) { raw |= f2.raw; return *this; }

FixedAngle FixedAngle::operator +(const FixedAngle &f2) const { return FixedAngle(raw + f2.raw); }
FixedAngle FixedAngle::operator -(const FixedAngle &f2) const { return FixedAngle(raw - f2.raw); }
FixedAngle FixedAngle::operator *(const FixedAngle &f2) const { return FixedAngle(raw * f2.raw); }
FixedAngle FixedAngle::operator &(const FixedAngle &f2) const { return FixedAngle(raw & f2.raw); }
FixedAngle FixedAngle::operator |(const FixedAngle &f2) const { return FixedAngle(raw | f2.raw); }

FixedAngle &FixedAngle::operator <<=(const unsigned sh) { raw <<= sh; return *this; }
FixedAngle &FixedAngle::operator >>=(const unsigned sh) { raw >>= sh; return *this; }
FixedAngle FixedAngle::operator <<(const unsigned sh) const { return FixedAngle(raw << sh); }
FixedAngle FixedAngle::operator >>(const unsigned sh) const { return FixedAngle(raw >> sh); }

bool FixedAngle::operator <(const FixedAngle &f2) const { return raw < f2.raw; }
bool FixedAngle::operator <=(const FixedAngle &f2) const { return raw <= f2.raw; }
bool FixedAngle::operator >(const FixedAngle &f2) const { return raw > f2.raw; }
bool FixedAngle::operator >=(const FixedAngle &f2) const { return raw >= f2.raw; }
bool FixedAngle::operator !=(const FixedAngle &f2) const { return raw != f2.raw; }
bool FixedAngle::operator ==(const FixedAngle &f2) const { return raw == f2.raw; }


fp12 sin(const FixedAngle &x) {
	return fp12(
		sinLerp(x.raw), 12
	);
}

fp12 cos(const FixedAngle &x) {
	return fp12(
		cosLerp(x.raw), 12
	);
}

fp12 tan(const FixedAngle &x) {
	return fp12(
		tanLerp(x.raw), 12
	);
}

FixedAngle asin(const fp12 x) {
	return asinLerp(x.raw);
}

FixedAngle acos(const fp12 x) {
	return acosLerp(x.raw);
}