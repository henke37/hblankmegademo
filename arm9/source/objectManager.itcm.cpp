#include "objectManager.h"

#include <nds/arm9/cache.h>
#include <nds/dma.h>
#include <cassert>
#include <cstdint>
#include <stdio.h>

template class std::vector<SpriteEntry>;

void ObjectManager::setupNextHDMA() {
	if(!enabled) return;
	int targetLine = REG_VCOUNT + 1;
	if(targetLine > SCREEN_HEIGHT) return;

	auto &update = updates[targetLine];
	update.registerForHDMA(dmaChannel, isSub);

	if(REG_VCOUNT > targetLine || (REG_VCOUNT== targetLine && (REG_DISPSTAT & DISP_IN_HBLANK))) {
		printf("ObjMan: update missed deadline. %i\n",targetLine);
	}
}

void ObjectManager::OAMUpdate::registerForHDMA(unsigned int dmaChannel,bool isSub) {
	if(updateSize == 0) return;
	size_t transferSize = sizeof(SpriteEntry) * updateSize;
	DC_FlushRange(objBuffer, transferSize);

	DMA_SRC(dmaChannel) = (uintptr_t) objBuffer;
	if(isSub) {
		DMA_DEST(dmaChannel) = 0x07000400;
	} else {
		DMA_DEST(dmaChannel) = 0x07000000;
	}

	DMA_CR(dmaChannel) = DMA_COPY_WORDS | (transferSize >> 2) | DMA_START_HBL | 
		DMA_SRC_INC | DMA_DST_INC;
}