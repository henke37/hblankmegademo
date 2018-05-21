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
void VramBatcher::AddPoke(int line, std::unique_ptr<uint8_t[]> &&data, size_t dataSize, hwPtr addr, PokeMode mode){
	AddPoke(line,Poke(std::move(data),dataSize,addr,mode));
}
void VramBatcher::AddPoke(int line, Poke&& p) {
	auto &lineEntry = lineEntries[line];
	for (int pokeIndex = 0; pokeIndex<ARRAY_POKES_PER_LINE; ++pokeIndex) {
		auto &&pokeEntry = lineEntry[pokeIndex];
		if (pokeEntry) continue;
		pokeEntry = std::move(p);
		return;
	}

	fprintf(stderr, "Poke buffer for line %d!", line);
}
void VramBatcher::AddPoke(int line, uint8_t val, uint8_t mask, volatile uint8_t *addr) {
	AddPoke(line, Poke(val, mask, addr));
}
void VramBatcher::AddPoke(int line, uint16_t val, uint16_t mask, volatile uint16_t *addr) {
	AddPoke(line, Poke(val, mask, addr));
}
void VramBatcher::AddPoke(int line, uint32_t val, uint32_t mask, volatile uint32_t *addr) {
	AddPoke(line, Poke(val, mask, addr));
}

void VramBatcher::Clear() {
	for(int line=0;line<SCREEN_HEIGHT;++line) {
		auto &lineEntry = lineEntries[line];
		for (int pokeIndex = 0; pokeIndex<ARRAY_POKES_PER_LINE; ++pokeIndex) {
			auto &pokeEntry = lineEntry[pokeIndex];
			pokeEntry.Clear();
		}
	}
}
