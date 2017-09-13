#include "fixedMath.h"

fp8 operator "" _fp8(unsigned long long x) { return fp8(x); }
fp12 operator "" _fp12(unsigned long long x) { return fp12(x); }

FixedAngle operator "" _fixedAngle(unsigned long long x) {
	return FixedAngle(degreesToAngle(x));
}