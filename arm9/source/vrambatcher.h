#include <memory>
#include <nds/arm9/video.h>

typedef volatile uint8_t *hwPtr;

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

enum PokeMode {
	PM_NOOP=0,
	PM_INT=1,
	PM_BITFIELD=2,
	PM_DMA=3,
	PM_MEMCPY=4
};

class Poke {
	struct {
		size_t size:24;
		PokeMode mode:8;
	};
	hwPtr addr;
	union {
		uint8_t value8;
		uint16_t value16;
		uint32_t value32;
		std::unique_ptr<uint8_t[]> valuePtr;
	};
	
	public:
	Poke();
	Poke(uint8_t val, volatile uint8_t *addr);
	Poke(uint16_t val, volatile uint16_t *addr);
	Poke(uint32_t val, volatile uint32_t *addr);
	Poke(std::unique_ptr<uint8_t[]> &&, size_t dataSize, hwPtr addr);
	
	~Poke();
	
	void Perform();
	private:
		void doMemCopy();
};

struct PokeChainLink;
struct PokeChainLink {
	std::unique_ptr<PokeChainLink> next;
	Poke poke;
	
	PokeChainLink();
	PokeChainLink(Poke&&, std::unique_ptr<PokeChainLink> next);
	~PokeChainLink();
};

class VramBatcher {
	public:
		VramBatcher();
		~VramBatcher();
		
		void AddPoke(int line, uint8_t val, volatile uint8_t *addr);
		void AddPoke(int line, uint16_t val, volatile uint16_t *addr);
		void AddPoke(int line, uint32_t val, volatile uint32_t *addr);
		void AddPoke(int line, std::unique_ptr<uint8_t[]> &&, size_t dataSize, hwPtr addr);
		
		void Clear();
	private:
		std::unique_ptr<PokeChainLink> lineEntries[SCREEN_HEIGHT];
		void ApplyPokesForLine(int line);
		void AddPoke(int line, Poke&& p);
};