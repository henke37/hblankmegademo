#include "objectManager.h"

#include <nds/arm9/cache.h>
#include <nds/dma.h>
#include <cassert>
#include <cstdint>
#include <stdio.h>

template class std::vector<SpriteEntry>;

void ObjectManager::hdmaCompleteHandler() {
	int targetLine = REG_VCOUNT + 1;
	if(targetLine > SCREEN_HEIGHT) return;

	updateObjsForScanline(targetLine);


	if(REG_VCOUNT > targetLine || (REG_VCOUNT== targetLine && (REG_DISPSTAT & DISP_IN_HBLANK))) {
		printf("ObjMan: update missed deadline. %i\n",targetLine);
	}
}


void objHdmaMainHandler() { mainObjManager.hdmaCompleteHandler(); }
void objHdmaSubHandler() { subObjManager.hdmaCompleteHandler(); }


void ObjectManager::updateObjsForScanline(unsigned int scanline) {
	int slotIndex = 0;

	for(SpriteEntry &candidate : shadowObjects) {
		if(candidate.y > scanline) continue;
		if(candidate.attribute3 < scanline) continue;

		objBuff[slotIndex++] = candidate;
		if(slotIndex>=SPRITE_COUNT) break;
	}

	int prevLastUsedObjSlots = lastUsedObjSlots;
	lastUsedObjSlots = slotIndex;

	for(; slotIndex < prevLastUsedObjSlots; ++slotIndex) {
		objBuff[slotIndex].isHidden = 1;
		objBuff[slotIndex].isRotateScale = 0;
	}

	setHDMA(slotIndex - 1 * sizeof(SpriteEntry));

}

void ObjectManager::setHDMA(std::size_t transferSize) {
	DC_FlushRange(objBuff, transferSize);

	DMA_SRC(dmaChannel) = (uintptr_t) objBuff;
	if(isSub) {
		DMA_DEST(dmaChannel) = 0x07000400;
	} else {
		DMA_DEST(dmaChannel) = 0x07000000;
	}

	DMA_CR(dmaChannel) = DMA_COPY_WORDS | (transferSize >> 2) | DMA_START_HBL | 
		DMA_SRC_INC | DMA_DST_INC | DMA_IRQ_REQ;
}