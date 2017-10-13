#include "objectManager.h"
#include <cassert>
#include <nds/dma.h>
#include <nds/interrupts.h>

uint32_t irqForDmaChannel[4] = {IRQ_DMA0, IRQ_DMA1, IRQ_DMA2, IRQ_DMA3};

ObjectManager mainObjManager(0, false);
ObjectManager subObjManager(1, true);

ObjectManager::ObjectManager(unsigned int dmaChannel_, bool isSub_) : enabled(false), isSub(isSub_), dmaChannel(dmaChannel_) {
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
	shadowObjects = objects;
	updateObjsForScanline(0);
}


