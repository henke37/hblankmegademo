
#include <cstring>
#include "vrambatcher.h"
Poke::Poke() : size(0), mode(PM_NOOP) {}
Poke::Poke(uint8_t val, volatile uint8_t *addr_) : size(sizeof(uint8_t)), mode(PM_INT), addr(addr_), value8(val) {
}
Poke::Poke(uint16_t val, volatile uint16_t *addr_) : size(sizeof(uint16_t)), mode(PM_INT), addr((hwPtr)addr_), value16(val) {
}
Poke::Poke(uint32_t val, volatile uint32_t *addr_) : size(sizeof(uint32_t)), mode(PM_INT), addr((hwPtr)addr_), value32(val) {
}
Poke::Poke(std::unique_ptr<uint8_t[]> &&dataPtr, size_t dataSize, hwPtr addr_) : size(dataSize), mode(PM_MEMCPY), addr(addr_), valuePtr(dataPtr) {
}

Poke::~Poke() {
	switch(mode) {
		case PM_MEMCPY:
		case PM_DMA:
			valuePtr.~unique_ptr<uint8_t[]>();
		break;
		case PM_BITFIELD:
		default:
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
		case PM_MEMCPY:
			doMemCopy();
		break;
		case PM_BITFIELD:
		break;
		case PM_DMA:
		break;
	}
}

void Poke::doMemCopy() {
	uint8_t *src=valuePtr.get();
	hwPtr dst=addr;
	for(size_t i=0;i<size;++i,++src,++dst) {
		*dst=*src;
	}
}

PokeChainLink::PokeChainLink() {}
PokeChainLink::PokeChainLink(Poke&& p, std::unique_ptr<PokeChainLink> next_) : next(next_), poke(p) {}
PokeChainLink::~PokeChainLink() {}

void VramBatcher::AddPoke(int line, uint8_t val, volatile uint8_t *addr) {
	AddPoke(line,Poke(val,addr));
}
void VramBatcher::AddPoke(int line, uint16_t val, volatile uint16_t *addr){
	AddPoke(line,Poke(val,addr));
}
void VramBatcher::AddPoke(int line, uint32_t val, volatile uint32_t *addr){
	AddPoke(line,Poke(val,addr));
}
void VramBatcher::AddPoke(int line, std::unique_ptr<uint8_t[]> &&data, size_t dataSize, hwPtr addr){
	AddPoke(line,Poke(data,dataSize,addr));
}
void VramBatcher::AddPoke(int line, Poke&& p) {
	lineEntries[line]=std::unique_ptr<PokeChainLink>(new PokeChainLink(p,lineEntries[line]));
}

void VramBatcher::Clear() {
	for(int line=0;line<SCREEN_HEIGHT;++line) {
		lineEntries[line].reset();
	}
}

void VramBatcher::ApplyPokesForLine(int line) {
	for(PokeChainLink *pPtr=lineEntries[line].get();pPtr!=nullptr;pPtr=pPtr->next.get()) {
		pPtr->poke.Perform();
	}
}