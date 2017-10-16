#include "objectManager.h"

#include <nds/arm9/cache.h>
#include <nds/dma.h>
#include <cassert>
#include <cstdint>

template class std::vector<ObjectManager::ShadowEntry>;

void ObjectManager::hdmaCompleteHandler() {
	if(REG_VCOUNT >= SCREEN_HEIGHT) return;
	updateObjsForScanline(REG_VCOUNT + 1);

	if(!(REG_DISPSTAT & (DISP_IN_VBLANK | DISP_IN_HBLANK))) {
		//puts("ObjMan: update missed deadline. \n");
	}
}


void objHdmaMainHandler() { mainObjManager.hdmaCompleteHandler(); }
void objHdmaSubHandler() { subObjManager.hdmaCompleteHandler(); }


void ObjectManager::updateObjsForScanline(unsigned int scanline) {
	int slotIndex = 0;

	for(ShadowEntry candidate : shadowObjects) {
		if(candidate.obj.y > scanline) continue;
		if(candidate.endY < scanline) continue;

		objBuff[slotIndex++] = candidate.obj;
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

	DMA_CR(dmaChannel) |= DMA_COPY_WORDS | (transferSize >> 2);
}