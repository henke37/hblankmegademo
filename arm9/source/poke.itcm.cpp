#include "poke.h"
#include "registerOverride.h"
#include <nds/dma.h>
#include <nds/arm9/video.h>
#include <cassert>

#define VRAM_F_SIZE (16*1024)
#define VRAM_G_SIZE (16*1024)
#define VRAM_H_SIZE (32*1024)
#define VRAM_I_SIZE (16*1024)

ITCM_CODE static bool pointerInRange(volatile void *needle, volatile void *base, size_t size);

ITCM_CODE void Poke::Perform() {
	registerOverride<uint8_t> oldVRamMode;

	if(pointerInRange(addr, VRAM_F, VRAM_F_SIZE)) {
		oldVRamMode.set(&VRAM_F_CR, VRAM_F_LCD);
	} else if(pointerInRange(addr, VRAM_G, VRAM_G_SIZE)) {
		oldVRamMode.set(&VRAM_G_CR, VRAM_G_LCD);
	} else if(pointerInRange(addr, VRAM_H, VRAM_H_SIZE)) {
		oldVRamMode.set(&VRAM_H_CR, VRAM_H_LCD);
	} else if(pointerInRange(addr, VRAM_I, VRAM_I_SIZE)) {
		oldVRamMode.set(&VRAM_I_CR, VRAM_I_LCD);
	}

	switch(mode) {
	case PM_NOOP:
		break;
	case PM_INT:
		switch(size) {
		case sizeof(uint8_t) :
			*((volatile uint8_t*)addr) = value8;
			break;
		case sizeof(uint16_t) :
			*((volatile uint16_t*)addr) = value16;
			break;
		case sizeof(uint32_t) :
			*((volatile uint32_t*)addr) = value32;
			break;
		default:
			assert(0);
		}
		break;
	case PM_BITFIELD:
		switch(size) {
		case sizeof(uint8_t) :
			bitField8.Poke((volatile uint8_t*)addr);
			break;
		case sizeof(uint16_t) :
			bitField16.Poke((volatile uint16_t*)addr);
			break;
		case sizeof(uint32_t) :
			bitField32.Poke((volatile uint32_t*)addr);
			break;
		default:
			assert(0);
		}
		break;
	case PM_DMA_16:
		dmaCopyHalfWords(3, valuePtr.get(), (void*)addr, size);
		break;
	case PM_DMA_32:
		dmaCopyWords(3, valuePtr.get(), (void*)addr, size);
		break;
	case PM_MEMCPY_8: {
		volatile uint8_t *src = valuePtr.get();
		std::copy(src, src + size, (uint8_t *)addr);
	} break;
	case PM_MEMCPY_16: {
		volatile uint16_t *src = (volatile uint16_t *)valuePtr.get();
		std::copy(src, src + size/2, (uint16_t *)addr);
	} break;
	case PM_MEMCPY_32: {
		volatile uint32_t *src = (volatile uint32_t *)valuePtr.get();
		std::copy(src, src + size/4, (uint32_t *)addr);
	} break;
	}
}


static bool pointerInRange(uintptr_t needle, uintptr_t base, size_t size) {
	return needle >= base && needle < (base + size);
}
static bool pointerInRange(volatile void *needle, volatile void *base, size_t size) {
	return pointerInRange((uintptr_t)needle, (uintptr_t)base, size);
}