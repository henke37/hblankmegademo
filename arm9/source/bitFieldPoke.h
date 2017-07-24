#ifndef BITFIELDPOKE_H
#define BITFIELDPOKE_H
template <class T> struct BitFieldPoke {
	T value;
	T mask;
	
	BitFieldPoke(T v, T m) : value(v), mask(m) {}
	
	void Poke(volatile T *ptr) {
		T t=*ptr;
		t &= ~mask;
		t |= value & mask;
		*ptr=t;
	}
	
	BitFieldPoke<T> operator |(const BitFieldPoke &p2) const {
		assert(isCompatible(p2));
		return BitFieldPoke<T>(value | p2.value, mask | p2.mask);
	}
	
	BitFieldPoke<T> &operator |=(const BitFieldPoke &p2) {
		assert(isCompatible(p2));
		value|=p2.value;
		mask|=p2.mask;
		return *this;
	}
	
	bool operator ==(const BitFieldPoke &p2) const {
		return value==p2.value && mask==p2.value;
	}
	
	bool operator !=(const BitFieldPoke &p2) const {
		return value!=p2.value || mask!=p2.value;
	}
	
	bool isCompatible(const BitFieldPoke &p2) const {
		return (mask & p2.mask)==0;
	}
};
#endif