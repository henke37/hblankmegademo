#include <cstring>
#include "vrambatcher.h"
Poke::Poke() : size(0), mode(PM_NOOP) {}
Poke::Poke(uint8_t val, volatile uint8_t *addr_) : size(sizeof(uint8_t)), mode(PM_INT), addr(addr_), value8(val) {
}
Poke::Poke(uint16_t val, volatile uint16_t *addr_) : size(sizeof(uint16_t)), mode(PM_INT), addr(addr_), value16(val) {
}
Poke::Poke(uint32_t val, volatile uint32_t *addr_) : size(sizeof(uint32_t)), mode(PM_INT), addr(addr_), value32(val) {
}
Poke::~Poke() {
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
	}
}

PokeChainLink::PokeChainLink() {}
PokeChainLink::PokeChainLink(Poke &&p, std::unique_ptr<PokeChainLink> &&next_) : next(std::move(next_)), poke(std::move(p)) {}
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
void VramBatcher::AddPoke(int line, Poke&& p) {
	PokeChainLink *l=new PokeChainLink(std::move(p),std::move(lineEntries[line]));
	lineEntries[line]=std::unique_ptr<PokeChainLink>(l);
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