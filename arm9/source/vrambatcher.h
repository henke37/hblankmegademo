#ifndef VRAMBATCHER_H
#define VRAMBATCHER_H

#include <memory>
#include <cstdint>
#include <nds/arm9/video.h>

#include "poke.h"

#define ARRAY_POKES_PER_LINE 4

class VramBatcher {
	public:
		VramBatcher();
		~VramBatcher();
		
		void AddPoke(int line, uint8_t val, volatile uint8_t *addr);
		void AddPoke(int line, uint16_t val, volatile uint16_t *addr);
		void AddPoke(int line, uint32_t val, volatile uint32_t *addr);

		void AddPoke(int line, uint8_t val, volatile uint8_t &ref);
		void AddPoke(int line, uint16_t val, volatile uint16_t &ref);
		void AddPoke(int line, uint32_t val, volatile uint32_t &ref);

		void AddPoke(int line, uint8_t val, uint8_t mask, volatile uint8_t *addr);
		void AddPoke(int line, uint16_t val, uint16_t mask, volatile uint16_t *addr);
		void AddPoke(int line, uint32_t val, uint32_t mask, volatile uint32_t *addr);
		
		void AddPoke(int line, std::unique_ptr<uint8_t[]> &&, size_t dataSize, hwPtr addr, PokeMode mode);
		
		void Clear();
		void ApplyPokesForLine(int line);
	private:

		Poke lineEntries[SCREEN_HEIGHT][ARRAY_POKES_PER_LINE];
		void AddPoke(int line, Poke&& p);
};

#endif