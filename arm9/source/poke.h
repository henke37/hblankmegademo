#ifndef POKE_H
#define POKE_H

#include <memory>

typedef volatile void *hwPtr;

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
	Poke(Poke &&);
	Poke(uint8_t val, volatile uint8_t *addr);
	Poke(uint16_t val, volatile uint16_t *addr);
	Poke(uint32_t val, volatile uint32_t *addr);
	Poke(std::unique_ptr<uint8_t[]> &&, size_t dataSize, hwPtr addr);
	
	~Poke();
	
	void Perform();
};

struct PokeChainLink;
struct PokeChainLink {
	std::unique_ptr<PokeChainLink> next;
	Poke poke;
	
	PokeChainLink();
	PokeChainLink(PokeChainLink &&);
	PokeChainLink(Poke&&, std::unique_ptr<PokeChainLink> &&next);
	PokeChainLink(Poke&&);
	~PokeChainLink();
};
#endif