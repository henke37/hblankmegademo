#include "particleDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/video.h>
#include <nds/arm9/sprite.h>
#include <cassert>

static SpriteSize spriteSizeToEnum(int width, int height);

BaseParticleDemo::BaseParticleDemo() {}
BaseParticleDemo::~BaseParticleDemo() {}
void BaseParticleDemo::Load() {
	REG_DISPCNT = DISPLAY_SPR_ACTIVE | DISPLAY_SPR_HBLANK;
}

void BaseParticleDemo::Unload() {}

void BaseParticleDemo::PrepareFrame(VramBatcher &batcher) {
	for(int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		
	}
}

void BaseParticleDemo::PrepareLine(int scanline) {
	int oamSlot = 0;
	for(auto &particle : particles) {
		if(particle.y > scanline) continue;
		if(particle.y + particle.height < scanline) continue;

		//TODO: move the updates to hblank
		auto &slot = oamMain.oamMemory[oamSlot];

		slot.x = particle.x;
		slot.y = particle.y;
		slot.isHidden = 0;
		slot.isRotateScale = 0;
	}

	for(; oamSlot < SPRITE_COUNT; ++oamSlot) {
		//TODO: move to hblank
		auto &slot = oamMain.oamMemory[oamSlot];
		slot.isHidden = 0;
		slot.isRotateScale = 0;
	}
}

BaseParticleDemo::Particle::Particle() {}
BaseParticleDemo::Particle::Particle(int _x, int _y) : x(_x), y(_y), width(1), height(1) {}

SpriteSize spriteSizeToEnum(int width, int height) {
	//round the width and height upwards to a multipiel of 8
	width +=7;//offset
	height +=7;
	width &= ~7;//and then round down
	width &= ~7;

	if(width == 8) {
		if(height == 8) return SpriteSize_8x8;
		if(height == 16) return SpriteSize_8x16;
		if(height == 32) return SpriteSize_8x32;
	}
	if(width == 16) {
		if(height == 8) return SpriteSize_16x8;
		if(height == 16) return SpriteSize_16x16;
		if(height == 32) return SpriteSize_16x32;
	}
	if(width == 32) {
		if(height == 8) return SpriteSize_32x8;
		if(height == 16) return SpriteSize_32x16;
		if(height == 32) return SpriteSize_32x32;
		if(height == 64) return SpriteSize_32x64;
	}
	if(width == 64) {
		if(height == 32) return SpriteSize_64x32;
		if(height == 64) return SpriteSize_64x64;
	}
	assert(0);
}
