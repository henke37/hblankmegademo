#include "vrambatcher.h"

ITCM_CODE void VramBatcher::ApplyPokesForLine(int line) {
	for(PokeChainLink *pPtr = lineEntries[line].get(); pPtr != nullptr; pPtr = pPtr->next.get()) {
		pPtr->poke.Perform();
	}
}