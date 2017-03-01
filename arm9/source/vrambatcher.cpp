#include <algorithm>
#include <cstring>
#include "vrambatcher.h"

VramBatcher::VramBatcher() {}
VramBatcher::~VramBatcher() {}

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
	AddPoke(line,Poke(std::move(data),dataSize,addr));
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