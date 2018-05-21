#ifndef POKE_H
#define POKE_H

#include <memory>
#include <cstdint>
#include "bitFieldPoke.h"

typedef volatile void *hwPtr;

enum PokeMode {
	PM_NOOP    = 0,
	PM_INT     = 1,
	PM_BITFIELD= 2,
	PM_MEMCPY_8  = 3,
	PM_MEMCPY_16  = 4,
	PM_MEMCPY_32  = 5,
	PM_DMA_16  = 6,
	PM_DMA_32  = 7
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
		BitFieldPoke<uint8_t> bitField8;
		BitFieldPoke<uint16_t> bitField16;
		BitFieldPoke<uint32_t> bitField32;
	};
	
	public:
	Poke();
	Poke(Poke &&);
	Poke(uint8_t val, volatile uint8_t *addr);
	Poke(uint16_t val, volatile uint16_t *addr);
	Poke(uint32_t val, volatile uint32_t *addr);
	Poke(std::unique_ptr<uint8_t[]> &&, size_t dataSize, hwPtr addr, PokeMode mode);
	Poke(uint8_t val, uint8_t mask, volatile uint8_t *addr);
	Poke(uint16_t val, uint16_t mask, volatile uint16_t *addr);
	Poke(uint32_t val, uint32_t mask, volatile uint32_t *addr);

	void operator =(std::nullptr_t);
	void operator =(Poke &&);
	operator bool() const;

	void Clear();
	
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