#include "poke.h"
#include <nds/arm9/sassert.h>

Poke::Poke() : size(0), mode(PM_NOOP) {}
Poke::Poke(uint8_t val, volatile uint8_t *addr_) : size(sizeof(uint8_t)), mode(PM_INT), addr(addr_), value8(val) {
}
Poke::Poke(uint16_t val, volatile uint16_t *addr_) : size(sizeof(uint16_t)), mode(PM_INT), addr(addr_), value16(val) {
}
Poke::Poke(uint32_t val, volatile uint32_t *addr_) : size(sizeof(uint32_t)), mode(PM_INT), addr(addr_), value32(val) {
}
Poke::Poke(std::unique_ptr<uint8_t[]> &&dataPtr, size_t dataSize, hwPtr addr_, PokeMode mode_) : size(dataSize), mode(mode_), addr(addr_), valuePtr(std::move(dataPtr)) {
	switch(mode_) {
		case PM_DMA_16:
		case PM_DMA_32:
		case PM_MEMCPY_8:
		case PM_MEMCPY_16:
		case PM_MEMCPY_32:
		break;
		
		default:
			sassert(0,"Invalid pokemode selected for memory copy poke");
	}
}

Poke::Poke(uint8_t val, uint8_t mask, volatile uint8_t *addr_) : size(sizeof(uint8_t)), mode(PM_BITFIELD), addr(addr_), bitField8(val, mask) {
}
Poke::Poke(uint16_t val, uint16_t mask, volatile uint16_t *addr_) : size(sizeof(uint16_t)), mode(PM_BITFIELD), addr(addr_), bitField16(val, mask) {
}
Poke::Poke(uint32_t val, uint32_t mask, volatile uint32_t *addr_) : size(sizeof(uint32_t)), mode(PM_BITFIELD), addr(addr_), bitField32(val,mask) {
}

Poke::Poke(Poke &&p2) : size(p2.size), mode(p2.mode), addr(p2.addr) {
	
	switch(p2.mode) {
		case PM_NOOP:
		break;
		case PM_INT:
			switch(p2.size) {
				case sizeof(uint8_t):
					value8=p2.value8;
				break;
				case sizeof(uint16_t):
					value16=p2.value16;
				break;
				case sizeof(uint32_t):
					value32=p2.value32;
				break;
				default:
					sassert(0,"Invalid size for plain poke found");
			}
		break;
		
		case PM_BITFIELD:
			switch (p2.size) {
				case sizeof(uint8_t) :
					bitField8 = std::move(p2.bitField8);
					break;
				case sizeof(uint16_t) :
					bitField16 = std::move(p2.bitField16);
					break;
				case sizeof(uint32_t) :
					bitField32 = std::move(p2.bitField32);
					break;
				default:
					sassert(0,"Invalid size found for bitfield poke");
			}
		break;
		
		case PM_DMA_16:
		case PM_DMA_32:
		case PM_MEMCPY_8:
		case PM_MEMCPY_16:
		case PM_MEMCPY_32:
			valuePtr=std::move(p2.valuePtr);
		break;
	}
	p2.mode=PM_NOOP;
	p2.size=0;
}


Poke::~Poke() {
	switch(mode) {
		case PM_DMA_16:
		case PM_DMA_32:
		case PM_MEMCPY_8:
		case PM_MEMCPY_16:
		case PM_MEMCPY_32:
			valuePtr.~unique_ptr();
		break;
		case PM_BITFIELD://no destructor to call
		default:
		break;
	}
}

PokeChainLink::PokeChainLink() {}
PokeChainLink::PokeChainLink(PokeChainLink &&pch2) : next(std::move(pch2.next)), poke(std::move(pch2.poke)) {}
PokeChainLink::PokeChainLink(Poke &&p) : next(nullptr), poke(std::move(p)) {}
PokeChainLink::PokeChainLink(Poke &&p, std::unique_ptr<PokeChainLink> &&next_) : next(std::move(next_)), poke(std::move(p)) {}
PokeChainLink::~PokeChainLink() {}
