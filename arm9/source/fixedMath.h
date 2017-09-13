#ifndef FIXEDMATH_H
#define FIXEDMATH_H

#include <cstdint>
#include <nds/arm9/math.h>
#include <nds/arm9/trig_lut.h>

template <int Base> class FixedPoint;

#define intFromBaseToBase(raw, Base, oldBase) Base>oldBase ? (raw >> (Base - oldBase)) : (raw << (oldBase - Base))

template <int Base> class FixedPoint {
public:
	FixedPoint(const int32_t _raw, const int oldBase) : raw(intFromBaseToBase(_raw, Base, oldBase)) {}
	template <int Base2> FixedPoint(const FixedPoint<Base2> &f2) : raw(intFromBaseToBase(f2.raw, Base, Base2)) {}
	FixedPoint(const int in) : raw(in<<Base) {}
	FixedPoint() {}

	operator int() const { return raw >> Base; }
	operator uint8_t() const { return raw >> Base; }
	operator bool() const { return (bool)raw; }
	operator float() const { return ((float)raw) / ((float)(1 << Base)); }
	
	FixedPoint<Base> &operator -() { raw = -raw; return *this; }
	
	FixedPoint<Base> &operator --() { raw -= Base; return *this; }
	FixedPoint<Base> &operator ++() { raw += Base; return *this; }

	FixedPoint<Base> &operator =(const FixedPoint<Base> &f2) { raw = f2.raw; return *this; }
	FixedPoint<Base> &operator +=(const FixedPoint<Base> &f2) { raw += f2.raw; return *this; }
	FixedPoint<Base> &operator -=(const FixedPoint<Base> &f2) { raw -= f2.raw; return *this; }
	FixedPoint<Base> &operator *=(const FixedPoint<Base> &f2) { raw = (raw * f2.raw) >> Base; return *this; }
	FixedPoint<Base> &operator &=(const FixedPoint<Base> &f2) { raw &= f2.raw; return *this; }
	FixedPoint<Base> &operator |=(const FixedPoint<Base> &f2) { raw |= f2.raw; return *this; }

	FixedPoint<Base> operator +(const FixedPoint<Base> &f2) const { return FixedPoint(raw + f2.raw, Base); }
	FixedPoint<Base> operator -(const FixedPoint<Base> &f2) const { return FixedPoint(raw - f2.raw, Base); }
	FixedPoint<Base> operator *(const FixedPoint<Base> &f2) const { return FixedPoint((raw * f2.raw)>>Base, Base); }
	FixedPoint<Base> operator &(const FixedPoint<Base> &f2) const { return FixedPoint(raw & f2.raw, Base); }
	FixedPoint<Base> operator |(const FixedPoint<Base> &f2) const { return FixedPoint(raw | f2.raw, Base); }
	
	FixedPoint<Base> operator +(const int x) const { return FixedPoint(raw + (x<<Base), Base); }
	FixedPoint<Base> operator -(const int x) const { return FixedPoint(raw - (x<<Base), Base); }
	FixedPoint<Base> operator *(const int x) const { return FixedPoint((raw * (x<<Base))>>Base, Base); }
	FixedPoint<Base> operator &(const int x) const { return FixedPoint(raw & (x<<Base), Base); }
	FixedPoint<Base> operator |(const int x) const { return FixedPoint(raw | (x<<Base), Base); }

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

template<int Base> bool operator < (const int x, const FixedPoint<Base> &f) { return (x<<Base) < f.raw; }
template<int Base> bool operator <=(const int x, const FixedPoint<Base> &f) { return (x<<Base) <= f.raw; }
template<int Base> bool operator > (const int x, const FixedPoint<Base> &f) { return (x<<Base) > f.raw; }
template<int Base> bool operator >=(const int x, const FixedPoint<Base> &f) { return (x<<Base) >= f.raw; }
template<int Base> bool operator ==(const int x, const FixedPoint<Base> &f) { return (x<<Base) == f.raw; }
template<int Base> bool operator !=(const int x, const FixedPoint<Base> &f) { return (x<<Base) != f.raw; }

template<int Base> FixedPoint<Base> operator +(const int x, const FixedPoint<Base> &f) { return FixedPoint<Base>((x<<Base) + f.raw, Base); }
template<int Base> FixedPoint<Base> operator -(const int x, const FixedPoint<Base> &f) { return FixedPoint<Base>((x<<Base) - f.raw, Base); }
template<int Base> FixedPoint<Base> operator *(const int x, const FixedPoint<Base> &f) { return FixedPoint<Base>(((x<<Base) * f.raw)>>Base, Base); }
template<int Base> FixedPoint<Base> operator &(const int x, const FixedPoint<Base> &f) { return FixedPoint<Base>((x<<Base) & f.raw, Base); }
template<int Base> FixedPoint<Base> operator |(const int x, const FixedPoint<Base> &f) { return FixedPoint<Base>((x<<Base) | f.raw, Base); }

typedef FixedPoint<8> fp8;
typedef FixedPoint<12> fp12;


fp8 operator "" _fp8(unsigned long long x);
fp12 operator "" _fp12(unsigned long long x);

inline fp12 sqrt(const fp12 &x) { return fp12(sqrtf32(x.raw), 12); }
inline fp12 operator / (const fp12 &x, const fp12 &y) { 
	if (y.raw == 0) return 0;
	return fp12(divf32(x.raw, y.raw), 12);
}

inline fp12 operator % (const fp12 x, const fp12 y) {
	if (y.raw == 0) return 0;
	return fp12(mod64(((int64)x.raw) << 12, y.raw), 12);
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
		x.raw = mod64(((int64)x.raw) << 12, y.raw);
	}
	return x;
}



class FixedAngle {
	public:
	FixedAngle();
	FixedAngle(s16 rawAngle);
	
	operator bool() const;
	operator float() const;
	
	FixedAngle &operator =(const FixedAngle &f2);
	FixedAngle &operator +=(const FixedAngle &f2);
	FixedAngle &operator -=(const FixedAngle &f2);
	FixedAngle &operator *=(const FixedAngle &f2);
	FixedAngle &operator &=(const FixedAngle &f2);
	FixedAngle &operator |=(const FixedAngle &f2);

	FixedAngle operator +(const FixedAngle &f2) const;
	FixedAngle operator -(const FixedAngle &f2) const;
	FixedAngle operator *(const FixedAngle &f2) const;
	FixedAngle operator &(const FixedAngle &f2) const;
	FixedAngle operator |(const FixedAngle &f2) const;

	FixedAngle &operator <<=(const unsigned sh);
	FixedAngle &operator >>=(const unsigned sh);
	FixedAngle operator <<(const unsigned sh) const;
	FixedAngle operator >>(const unsigned sh) const;

	bool operator <(const FixedAngle &f2) const;
	bool operator <=(const FixedAngle &f2) const;
	bool operator >(const FixedAngle &f2) const;
	bool operator >=(const FixedAngle &f2) const;
	bool operator !=(const FixedAngle &f2) const;
	bool operator ==(const FixedAngle &f2) const;
	
	s16 raw;
};

FixedAngle operator "" _fixedAngle(unsigned long long x);

inline fp12 sin(const FixedAngle &x);
inline fp12 cos(const FixedAngle &x);
inline fp12 tan(const FixedAngle &x);
inline FixedAngle asin(const fp12 x);
inline FixedAngle acos(const fp12 x);


#endif