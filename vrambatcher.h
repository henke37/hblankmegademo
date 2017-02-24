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
	Poke(std::unique_ptr<data>, size_t dataSize, hwPre addr);
	
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
		
		void Poke(int line, uint8_t val, hwPtr addr);
		void Poke(int line, uint16_t val, hwPtr addr);
		void Poke(int line, uint32_t val, hwPtr addr);
		void Poke(int line, std::unique_ptr<data>, size_t dataSize, hwPre addr);
		
		void Clear();
	private:
		std::unique_ptr<PokeChainLink> lineEntries[LINE_COUNT];
		void ApplyPokesForLine(int line);
		void VramBatcher::Poke(int line, Poke&& p);
		void Poke(int line, Poke *);
};