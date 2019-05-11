#include "objectManager.h"
#include <cassert>
#include <nds/dma.h>
#include <nds/interrupts.h>
#include <nds/arm9/cache.h>
#include <stdio.h>

unsigned int objHeight(const SpriteEntry &obj);

uint32_t irqForDmaChannel[4] = {IRQ_DMA0, IRQ_DMA1, IRQ_DMA2, IRQ_DMA3};

ObjectManager mainObjManager(0, false);
ObjectManager subObjManager(1, true);

ObjectManager::ObjectManager(unsigned int dmaChannel_, bool isSub_) : 
	enabled(false), 
	isSub(isSub_), 
	dmaChannel(dmaChannel_)
{
	assert(dmaChannel_ <= 3);
}

ObjectManager::~ObjectManager() {
	deactivate();
}

void ObjectManager::activate() {
	if(enabled) return;
	enabled = true;

	lastUsedObjSlots = SPRITE_COUNT;

	while(dmaBusy(dmaChannel));

	if(isSub) {
		REG_DISPCNT_SUB |= DISPLAY_SPR_HBLANK;
	} else {
		REG_DISPCNT |= DISPLAY_SPR_HBLANK;
	}

	DMA_CR(dmaChannel) = DMA_START_HBL | DMA_SRC_FIX | DMA_DST_FIX;
}

void ObjectManager::deactivate() {
	if(!enabled) return;
	enabled = false;

	if(isSub) {
		REG_DISPCNT_SUB &= ~DISPLAY_SPR_HBLANK;
	} else {
		REG_DISPCNT &= ~DISPLAY_SPR_HBLANK;
	}

	DMA_CR(dmaChannel) &= ~DMA_ENABLE;

	while(dmaBusy(dmaChannel));
}

void ObjectManager::tick() {
	if(!enabled) return;

	shadowObjects.reserve(objects.capacity());
	for(unsigned int i = 0; i < objects.size(); ++i) {
		const SpriteEntry &obj = objects[i];
		shadowObjects[i] = obj;
		shadowObjects[i].attribute3=objHeight(obj)+obj.y;
	}
	shadowObjects.resize(objects.size());

	const unsigned int chunkSize = 4;

	for(unsigned int scanline = 0; scanline < SCREEN_HEIGHT; scanline+=chunkSize) {
		buildUpdateForScanlines(scanline,chunkSize);
	}

	updates[0].DMANow(dmaChannel, isSub);
}

void ObjectManager::buildUpdateForScanlines(unsigned int start, unsigned int chunkSize) {
	int slotIndex = 0;
	auto &update = updates[start];
	auto &objBuff = update.objBuffer;

	unsigned int regionEnd = start + chunkSize - 1;
	if(regionEnd > SCREEN_HEIGHT) regionEnd = SCREEN_HEIGHT;

	for(SpriteEntry &candidate : shadowObjects) {
		auto bottom = candidate.attribute3;
		//check if upper bound is before region start
		if(bottom < start) continue;

		//check if lower bound is before the region start
		if(candidate.y > regionEnd) continue;

		auto &oamSlot = objBuff[slotIndex++];
		
		oamSlot= candidate;
		oamSlot.attribute3 = 0;
		if(slotIndex >= SPRITE_COUNT) break;
	}

	int prevLastUsedObjSlots = lastUsedObjSlots;
	lastUsedObjSlots = slotIndex;
	
	for(; slotIndex < prevLastUsedObjSlots; ++slotIndex) {
		objBuff[slotIndex].isHidden = 1;
		objBuff[slotIndex].isRotateScale = 0;
	}

	update.updateSize = slotIndex;

}

ObjectManager::OAMUpdate::OAMUpdate() : updateSize(0) {}

void ObjectManager::OAMUpdate::DMANow(unsigned int dmaChannel, bool isSub) {
	if(updateSize == 0) return;
	size_t transferSize = sizeof(SpriteEntry) * updateSize;
	DC_FlushRange(objBuffer, transferSize);

	DMA_SRC(dmaChannel) = (uintptr_t) objBuffer;
	if(isSub) {
		DMA_DEST(dmaChannel) = 0x07000400;
	} else {
		DMA_DEST(dmaChannel) = 0x07000000;
	}

	DMA_CR(dmaChannel) = DMA_COPY_WORDS | (transferSize >> 2) | DMA_START_NOW |
		DMA_SRC_INC | DMA_DST_INC;
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


