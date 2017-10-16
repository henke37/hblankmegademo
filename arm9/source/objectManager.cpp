#include "objectManager.h"
#include <cassert>
#include <nds/dma.h>
#include <nds/interrupts.h>


unsigned int objHeight(const SpriteEntry &obj);

uint32_t irqForDmaChannel[4] = {IRQ_DMA0, IRQ_DMA1, IRQ_DMA2, IRQ_DMA3};

ObjectManager mainObjManager(0, false);
ObjectManager subObjManager(1, true);

ObjectManager::ObjectManager(unsigned int dmaChannel_, bool isSub_) : 
	enabled(false), 
	isSub(isSub_), 
	dmaChannel(dmaChannel_),
	lastUsedObjSlots(SPRITE_COUNT)
{
	assert(dmaChannel_ <= 3);
}

ObjectManager::~ObjectManager() {
	deactivate();
}

void ObjectManager::activate() {
	if(enabled) return;

	while(dmaBusy(dmaChannel));

	if(isSub) {
		REG_DISPCNT_SUB |= DISPLAY_SPR_HBLANK;
	} else {
		REG_DISPCNT |= DISPLAY_SPR_HBLANK;
	}

	irqSet(irqForDmaChannel[dmaChannel], isSub ? objHdmaSubHandler : objHdmaMainHandler);
	irqEnable(irqForDmaChannel[dmaChannel]);

	DMA_CR(dmaChannel) = DMA_START_HBL | DMA_SRC_FIX | DMA_DST_FIX | DMA_IRQ_REQ;
}

void ObjectManager::deactivate() {
	if(!enabled) return;

	if(isSub) {
		REG_DISPCNT_SUB &= ~DISPLAY_SPR_HBLANK;
	} else {
		REG_DISPCNT &= ~DISPLAY_SPR_HBLANK;
	}

	irqDisable(irqForDmaChannel[dmaChannel]);

	DMA_CR(dmaChannel) &= ~DMA_ENABLE;

	while(dmaBusy(dmaChannel));
}

void ObjectManager::tick() {
	if(!enabled) return;

	shadowObjects.reserve(objects.capacity());
	for(unsigned int i = 0; i < objects.size(); ++i) {
		const SpriteEntry &obj = objects[i];
		shadowObjects[i] = {obj, objHeight(obj)+obj.y};
	}
	shadowObjects.resize(objects.size());

	updateObjsForScanline(0);
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


