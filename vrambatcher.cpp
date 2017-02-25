#include <vrambatcher.h>
#include <cstring>
Poke::Poke() : size(0) {}
Poke::Poke(uint8_t val, volatile uint8_t *addr_) : size(sizeof(uint8_t)), addr(addr_), value8(val) {
}
Poke::Poke(uint16_t val, volatile uint16_t *addr) : size(sizeof(uint16_t)), addr(addr_), value16(val) {
}
Poke::Poke(uint32_t val, volatile uint32_t *addr) : size(sizeof(uint32_t)), addr(addr_), value32(val) {
}
Poke::Poke(std::unique_ptr<data> dataPtr, size_t dataSize, hwPre addr_) : size(dataSize), addr(addr_), valuePtr(dataPtr) {
}

Poke::Poke~() {}

Pole::Perform() {
	switch(size) {
		case 0:
		break;
		case sizeof(uint8_t):
			*((volatile uint8_t*)addr)=value8;
			break;
		case sizeof(uint16_t):
			*((volatile uint16_t*)addr)=value16;
			break;
		case sizeof(uint32_t):
			*((volatile uint32_t*)addr)=value32;
			break;
		default:
			memcpy(addr,valuePtr.get(),size);
	}
}

PokeChainLink::PokeChainLink() {}
PokeChainLink::PokeChainLink(Poke&& p, std::unique_ptr<PokeChainLink> next_) : poke(p), next(next_) {}
PokeChainLink::PokeChainLink~() {}

void VramBatcher::Poke(int line, uint8_t val, volatile uint8_t *addr) {
	Poke(Poke(val,addr));
}
void VramBatcher::Poke(int line, uint16_t val, volatile uint16_t *addr){
	Poke(Poke(val,addr));
}
void VramBatcher::Poke(int line, uint32_t val, volatile uint32_t *addr){
	Poke(Poke(val,addr));
}
void VramBatcher::Poke(int line, std::unique_ptr<data> data, size_t dataSize, hwPtr addr){
	Poke(Poke(data,dataSize,addr));
}
void VramBatcher::Poke(int line, Poke&& p) {
	lineEntries[line]=std::unique_ptr<PokeChainLink>(new PokeChainLink(p,lineEntries[line]));
}

void VramBatcher::Clear() {
	for(int line=0;line<lineEntries;++line) {
		lineEntries[line].reset();
	}
}

void VramBatcher::ApplyPokesForLine(int line) {
	for(PokeChainLink *pPtr=lineEntries[line].get();pPtr!=null_ptr;pPtr=pPtr->next.get()) {
		pPtr->poke.Perform();
	}
}