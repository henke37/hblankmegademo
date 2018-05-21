#include "vrambatcher.h"

#ifdef __INTELLISENSE__
#undef ITCM_CODE
#define ITCM_CODE
#endif

ITCM_CODE void VramBatcher::ApplyPokesForLine(int line) {
	auto &lineEntry = lineEntries[line];
	for (int pokeIndex = 0; pokeIndex<ARRAY_POKES_PER_LINE; ++pokeIndex) {
		auto &pokeEntry = lineEntry[pokeIndex];
		pokeEntry.Perform();
	}
}