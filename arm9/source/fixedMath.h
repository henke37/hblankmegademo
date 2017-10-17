#ifndef FIXEDMATH_H
#define FIXEDMATH_H

#include <cstdint>

template <int Base> class FixedPoint;

#define intFromBaseToBase(raw, Base, oldBase) (Base>oldBase) ? (raw >> (Base - oldBase)) : (raw << (oldBase - Base))

template <int Base> class FixedPoint {
public:
	FixedPoint(const int32_t _raw, const int oldBase) : raw(intFromBaseToBase(_raw, Base, oldBase)) {}
	template <int Base2> FixedPoint(const FixedPoint<Base2> &f2) : raw(intFromBaseToBase(f2.raw, Base, Base2)) {}
	FixedPoint(const int in) : raw(in<<Base) {}
	FixedPoint(const double in) : raw(in * (1<< Base)) {}
	FixedPoint() {}

	operator int() const { return raw >> Base; }
	operator uint8_t() const { return raw >> Base; }
	operator bool() const { return (bool)raw; }
	operator float() const { return ((float)raw) / ((float)(1 << Base)); }
	
	FixedPoint<Base> operator -() const { return FixedPoint(-raw, Base); }
	FixedPoint<Base> &operator !() const { return !raw; }
	
	FixedPoint<Base> &operator --() { raw -= (1 << Base); return *this; }
	FixedPoint<Base> &operator ++() { raw += (1 << Base); return *this; }

	FixedPoint<Base> &operator =(const FixedPoint<Base> &f2) { raw = f2.raw; return *this; }
	FixedPoint<Base> &operator +=(const FixedPoint<Base> &f2) { raw += f2.raw; return *this; }
	FixedPoint<Base> &operator -=(const FixedPoint<Base> &f2) { raw -= f2.raw; return *this; }
	FixedPoint<Base> &operator *=(const FixedPoint<Base> &f2) { raw = fixedMul(raw,f2.raw); return *this; }
	FixedPoint<Base> &operator &=(const FixedPoint<Base> &f2) { raw &= f2.raw; return *this; }
	FixedPoint<Base> &operator |=(const FixedPoint<Base> &f2) { raw |= f2.raw; return *this; }

	FixedPoint<Base> operator +(const FixedPoint<Base> &f2) const { return FixedPoint(raw + f2.raw, Base); }
	FixedPoint<Base> operator -(const FixedPoint<Base> &f2) const { return FixedPoint(raw - f2.raw, Base); }
	FixedPoint<Base> operator *(const FixedPoint<Base> &f2) const { return FixedPoint(fixedMul(raw,f2.raw), Base); }
	FixedPoint<Base> operator &(const FixedPoint<Base> &f2) const { return FixedPoint(raw & f2.raw, Base); }
	FixedPoint<Base> operator |(const FixedPoint<Base> &f2) const { return FixedPoint(raw | f2.raw, Base); }
	
	FixedPoint<Base> operator +(const int x) const { return FixedPoint(raw + (x<<Base), Base); }
	FixedPoint<Base> operator -(const int x) const { return FixedPoint(raw - (x<<Base), Base); }
	FixedPoint<Base> operator *(const int x) const { return FixedPoint(fixedMul(raw,x<<Base), Base); }
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


	bool operator <(const int x) const { return raw < (x << Base); }
	bool operator <=(const int x) const { return raw <= (x << Base); }
	bool operator >(const int x) const { return raw > (x << Base); }
	bool operator >=(const int x) const { return raw >= (x << Base); }
	bool operator !=(const int x) const { return raw != (x << Base); }
	bool operator ==(const int x) const { return raw == (x << Base); }


	FixedPoint<Base> &operator =(const int x) { raw = (x << Base); return *this; }
	FixedPoint<Base> &operator +=(const int x) { raw += (x << Base); return *this; }
	FixedPoint<Base> &operator -=(const int x) { raw -= (x << Base); return *this; }
	FixedPoint<Base> &operator *=(const int x) { raw *= (x << Base); return *this; }

	int32_t raw;

private:
	int32_t static fixedMul(int32_t a, int32_t b) {
		return int32_t((int64_t(a) * int64_t(b)) >> Base);
	}

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
fp12 operator "" _fp12(long double x);

fp12 sqrt(const fp12 &x);
fp12 operator / (const fp12 &x, const fp12 &y);
fp12 operator % (const fp12 x, const fp12 y);
fp12 &operator /=(fp12 &x, const fp12 &y);
fp12 &operator %=(fp12 &x, const fp12 &y);


class FixedAngle {
	public:
	FixedAngle();
	FixedAngle(int16_t rawAngle);
	
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
	
	int16_t raw;
};

FixedAngle operator "" _fixedAngle(unsigned long long x);

fp12 sin(const FixedAngle &x);
fp12 cos(const FixedAngle &x);
fp12 tan(const FixedAngle &x);
FixedAngle asin(const fp12 x);
FixedAngle acos(const fp12 x);


#endif