#ifndef FIXEDMATH_H
#define FIXEDMATH_H

#include <cstdint>
#include <nds/arm9/math.h>

template <int Base> class FixedPoint;

template <int Base> class FixedPoint {
public:
	FixedPoint(const int32_t raw, const int oldBase) : raw(Base>oldBase ? (raw >> (Base - oldBase)) : (raw << (oldBase - Base))) {}
	template <int Base2> FixedPoint(const FixedPoint<Base2> &f2) : raw(Base>Base2?(f2.raw>>(Base-Base2)):(f2.raw<<(Base2-Base))) {}
	FixedPoint(const int in) : raw(in<<Base) {}
	FixedPoint() : raw(0) {}

	operator int() const { return raw >> Base; }
	operator bool() const { return (bool)raw; }
	operator float() const { return ((float)raw) / (1 >> Base); }

	FixedPoint<Base> &operator =(const FixedPoint<Base> &f2) { raw = f2; return *this; }
	FixedPoint<Base> &operator +=(const FixedPoint<Base> &f2) { raw += f2.raw; return *this; }
	FixedPoint<Base> &operator -=(const FixedPoint<Base> &f2) { raw -= f2.raw; return *this; }
	FixedPoint<Base> &operator *=(const FixedPoint<Base> &f2) { raw *= f2.raw; return *this; }

	FixedPoint<Base> operator +(const FixedPoint<Base> &f2) const { return FixedPoint(raw + f2.raw, Base); }
	FixedPoint<Base> operator -(const FixedPoint<Base> &f2) const { return FixedPoint(raw - f2.raw, Base); }
	FixedPoint<Base> operator *(const FixedPoint<Base> &f2) const { return FixedPoint(raw * f2.raw, Base); }

	FixedPoint<Base> &operator <<=(const unsigned sh) { raw <<= sh; return *this; }
	FixedPoint<Base> &operator >>=(const unsigned sh) { raw >>= sh; return *this; }
	FixedPoint<Base> operator <<(const unsigned sh) const { return FixedPoint(raw << sh, Base); }
	FixedPoint<Base> operator >>(const unsigned sh) const { return FixedPoint(raw >> sh, Base); }

	bool operator <(const FixedPoint<Base> &f2) const { return raw < f2.raw; }
	bool operator <=(const FixedPoint<Base> &f2) const { return raw <= f2.raw; }
	bool operator >(const FixedPoint<Base> &f2) const { return raw > f2.raw; }
	bool operator >=(const FixedPoint<Base> &f2) const { return raw >= f2.raw; }
	bool operator !=(const FixedPoint<Base> &f2) const { return raw != f2.raw; }
	bool operator ==(const FixedPoint<Base> &f2) const { return raw == f2.raw; }


	bool operator <(const int x) const { return raw < x << Base; }
	bool operator <=(const int x) const { return raw <= x << Base; }
	bool operator >(const int x) const { return raw > x << Base; }
	bool operator >=(const int x) const { return raw >= x << Base; }
	bool operator !=(const int x) const { return raw != x << Base; }
	bool operator ==(const int x) const { return raw == x << Base; }

	FixedPoint<Base> &operator +=(const int x) { raw += x << Base; return *this; }
	FixedPoint<Base> &operator -=(const int x) { raw -= x << Base; return *this; }
	FixedPoint<Base> &operator *=(const int x) { raw *= x << Base; return *this; }

	int32_t raw;

};

typedef FixedPoint<8> fp8;
typedef FixedPoint<12> fp12;

inline fp12 sqrt(const fp12 &x) { return fp12(sqrtf32(x.raw), 12); }
inline fp12 operator / (const fp12 &x, const fp12 &y) { 
	if (y.raw == 0) return 0;
	return fp12(divf32(x.raw, y.raw), 12);
}

inline fp12 operator % (const fp12 x, const fp12 y) {
	if (y.raw == 0) return 0;
	return fp12(mod32(x.raw, y.raw), 12);
}

inline fp12 &operator /=(fp12 &x, const fp12 &y) {
	if (y.raw == 0) {
		x.raw = 0;
	} else {
		x.raw = divf32(x.raw, y.raw);
	}
	return x;
}

inline fp12 &operator %=(fp12 &x, const fp12 &y) {
	if (y.raw == 0) {
		x.raw = 0;
	} else {
		x.raw = mod32(x.raw, y.raw);
	}
	return x;
}

#endif