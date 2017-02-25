#include <memory>

typedef volatile void *hwPtr;

template <class T> struct BitFieldPoke {
	T value;
	T mask;
	
	BitFieldPoke(T v, T m) : value(v), mask(m) {}
	
	Poke(volatile T *ptr) {
		T t=*ptr;
		t &= ~mask;
		t |= v & mask;
		*ptr=t;
	}
	
	BitFieldPoke<T> operator |(const BitFieldPoke p2&) const {
		assert(isCompatible(p2));
		return BitFieldPoke<T>(value | p2.value, mask | p2.mask);
	}
	
	BitFieldPoke<T> &operator |=(const BitFieldPoke p2&) {
		assert(isCompatible(p2));
		value|=p2.value;
		mask|=p2.mask;
		return *this;
	}
	
	bool operator ==(const BitFieldPoke p2&) const {
		return value==p2.value && mask==p2.value;
	}
	
	bool operator !=(const BitFieldPoke p2&) const {
		return value!=p2.value || mask!=p2.value;
	}
	
	bool isCompatible(const BitFieldPoke p2&) const {
		return (mask & p2.mask)==0;
	}
}

class Poke {
	size_t size;
	hwPtr addr;
	union {
		uint8_t value8;
		uint16_t value16;
		uint32_t value32;
		std::unique_ptr<void> valuePtr;
	};
	
	public:
	Poke();
	Poke(uint8_t val, volatile uint8_t *addr);
	Poke(uint16_t val, volatile uint16_t *addr);
	Poke(uint32_t val, volatile uint32_t *addr);
	Poke(std::unique_ptr<data>, size_t dataSize, hwPtr addr);
	
	Poke~();
	
	void Perform();
};

struct PokeChainLink;
struct PokeChainLink {
	std::unique_ptr<PokeChainLink> next;
	Poke poke;
	
	PokeChainLink();
	PokeChainLink(Poke&&, std::unique_ptr<PokeChainLink> next);
	PokeChainLink~();
}

class VramBatcher {
	public:
		VramBatcher();
		
		void AddPoke(int line, uint8_t val, volatile uint8_t *addr);
		void AddPoke(int line, uint16_t val, volatile uint16_t *addr);
		void AddPoke(int line, uint32_t val, volatile uint32_t *addr);
		void AddPoke(int line, std::unique_ptr<data>, size_t dataSize, hwPre addr);
		
		void Clear();
	private:
		std::unique_ptr<PokeChainLink> lineEntries[SCREEN_HEIGHT];
		void ApplyPokesForLine(int line);
		void AddPoke(int line, Poke&& p);
};