#include "objectManager.h"

#include <nds/arm9/cache.h>
#include <nds/dma.h>
#include <cassert>
#include <cstdint>

unsigned int objHeight(const SpriteEntry &obj);

void ObjectManager::hdmaCompleteHandler() {
	if(REG_VCOUNT >= SCREEN_HEIGHT) return;
	updateObjsForScanline(REG_VCOUNT + 1);

	if(!(REG_DISPSTAT & (DISP_IN_VBLANK | DISP_IN_HBLANK))) {
		puts("ObjMan: update missed deadline. \n");
	}
}


void objHdmaMainHandler() { mainObjManager.hdmaCompleteHandler(); }
void objHdmaSubHandler() { subObjManager.hdmaCompleteHandler(); }


void ObjectManager::updateObjsForScanline(int scanline) {
	int slotIndex = 0;

	for(SpriteEntry candidateObj : shadowObjects) {
		int height = objHeight(candidateObj);
		if(candidateObj.y > scanline) continue;
		if(candidateObj.y + height < scanline) continue;

		objBuff[slotIndex++] = candidateObj;
	}

	for(; slotIndex < SPRITE_COUNT; ++slotIndex) {
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


unsigned int objHeight(const SpriteEntry &obj) {
	switch(obj.shape) {
	case 0:
		//square
		switch(obj.size) {
		case 0:
			return 8;
		case 1:
			return 16;
		case 2:
			return 32;
		case 3:
			return 64;
		}
		assert(0);
	case 1:
		//tall
		switch(obj.size) {
		case 0:
			return 16;
		case 1:
			return 16;
		case 2:
			return 32;
		case 3:
			return 64;
		}
		assert(0);
	case 2:
		//wide
		switch(obj.size) {
		case 0:
			return 8;
		case 1:
			return 8;
		case 2:
			return 16;
		case 3:
			return 32;
		}
		assert(0);
	default:
		assert(0);
	}
}
