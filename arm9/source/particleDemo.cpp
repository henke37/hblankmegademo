#include "particleDemo.h"
#include "vrambatcher.h"
#include "objectManager.h"

#include <nds/arm9/video.h>
#include <nds/arm9/sprite.h>
#include <cassert>

static SpriteSize spriteSizeToEnum(int width, int height);

BaseParticleDemo::BaseParticleDemo() {}
BaseParticleDemo::~BaseParticleDemo() {}
void BaseParticleDemo::Load() {
	REG_DISPCNT = DISPLAY_SPR_ACTIVE;
	mainObjManager.activate();
}

void BaseParticleDemo::Unload() {
	mainObjManager.deactivate();
}

BaseParticleDemo::Particle::Particle() {}
BaseParticleDemo::Particle::Particle(int x_, int y_) : x(x_), y(y_), width(1), height(1) {}
BaseParticleDemo::Particle::Particle(int x_, int y_, int w, int h) : x(x_), y(y_), width(w), height(h) {}

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
	sassert(0,"Bad object size found");
}
