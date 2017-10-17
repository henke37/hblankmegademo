#include "fixedMath.h"
#include <nds/arm9/math.h>
#include <nds/arm9/trig_lut.h>
#include <stdio.h>

fp8 operator "" _fp8(unsigned long long x) { return fp8((int)x); }
fp12 operator "" _fp12(unsigned long long x) { return fp12((int)x); }

fp12 operator""_fp12(long double x) {
	return fp12((double)x);
}


fp12 sqrt(const fp12 &x) { 
	if (x < 0) {
		fprintf(stderr, "Trying to sqrt a negative value!\n%li %f\n",x.raw,(float)x);
	}
	return fp12(sqrtf32(x.raw), 12);
}
fp12 operator / (const fp12 &x, const fp12 &y) { 
	if (y.raw == 0) return 0;
	return fp12(divf32(x.raw, y.raw), 12);
}

fp12 operator % (const fp12 x, const fp12 y) {
	if (y.raw == 0) return 0;
	return fp12(mod64(((int64)x.raw) << 12, y.raw), 12);
}

fp12 &operator /=(fp12 &x, const fp12 &y) {
	if (y.raw == 0) {
		x.raw = 0;
	} else {
		x.raw = divf32(x.raw, y.raw);
	}
	return x;
}

fp12 &operator %=(fp12 &x, const fp12 &y) {
	if (y.raw == 0) {
		x.raw = 0;
	} else {
		x.raw = mod64(((int64)x.raw) << 12, y.raw);
	}
	return x;
}


FixedAngle operator "" _fixedAngle(unsigned long long x) {
	return FixedAngle(degreesToAngle(x));
}

FixedAngle::FixedAngle() {}
FixedAngle::FixedAngle(int16_t rawAngle) : raw(rawAngle) {}

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