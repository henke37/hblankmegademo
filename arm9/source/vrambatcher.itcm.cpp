#include "vrambatcher.h"

#ifdef __INTELLISENSE__
#undef ITCM_CODE
#define ITCM_CODE
#endif

ITCM_CODE void VramBatcher::ApplyPokesForLine(int line) {
	for(PokeChainLink *pPtr = lineEntries[line].get(); pPtr != nullptr; pPtr = pPtr->next.get()) {
		pPtr->poke.Perform();
	}
}