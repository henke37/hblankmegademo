#include "poke.h"
Poke::Poke() : size(0), mode(PM_NOOP) {}
Poke::Poke(uint8_t val, volatile uint8_t *addr_) : size(sizeof(uint8_t)), mode(PM_INT), addr(addr_), value8(val) {
}
Poke::Poke(uint16_t val, volatile uint16_t *addr_) : size(sizeof(uint16_t)), mode(PM_INT), addr(addr_), value16(val) {
}
Poke::Poke(uint32_t val, volatile uint32_t *addr_) : size(sizeof(uint32_t)), mode(PM_INT), addr(addr_), value32(val) {
}
Poke::Poke(std::unique_ptr<uint8_t[]> &&dataPtr, size_t dataSize, hwPtr addr_) : size(dataSize), mode(PM_MEMCPY), addr(addr_), valuePtr(std::move(dataPtr)) {
}
Poke::~Poke() {
	switch(mode) {
		case PM_DMA:
		case PM_MEMCPY:
			valuePtr.~unique_ptr();
		break;
		default:
		break;
	}
}

void Poke::Perform() {
	switch(mode) {
		case PM_NOOP:
		break;
		case PM_INT:
			switch(size) {
				case sizeof(uint8_t):
					*((volatile uint8_t*)addr)=value8;
				break;
				case sizeof(uint16_t):
					*((volatile uint16_t*)addr)=value16;
				break;
				case sizeof(uint32_t):
					*((volatile uint32_t*)addr)=value32;
				break;
			}
		break;
		case PM_BITFIELD:
		break;
		case PM_DMA:
		break;
		case PM_MEMCPY: {
			volatile uint8_t *dst=valuePtr.get();
			std::copy(dst,dst+size,(uint8_t *)addr);
		} break;
		
	}
}

PokeChainLink::PokeChainLink() {}
PokeChainLink::PokeChainLink(Poke &&p, std::unique_ptr<PokeChainLink> &&next_) : next(std::move(next_)), poke(std::move(p)) {}
PokeChainLink::~PokeChainLink() {}