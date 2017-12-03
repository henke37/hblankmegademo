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
	REG_DISPCNT = DISPLAY_SPR_ACTIVE | DISPLAY_SPR_HBLANK | DISPLAY_SPR_1D | MODE_0_2D;
	mainObjManager.activate();
}

void BaseParticleDemo::Unload() {
	mainObjManager.deactivate();
}

void BaseParticleDemo::PrepareFrame(VramBatcher &) {
	updateParticles();
	buildObjectsFromParticles();
}

void BaseParticleDemo::buildObjectsFromParticles() {

	mainObjManager.objects.clear();
	for(const Particle &particle : particles) {
		SpriteEntry obj;

		auto size = spriteSizeToEnum(particle.width, particle.height);

		obj.isHidden = 0;
		obj.isMosaic = 0;
		obj.isRotateScale = 0;

		obj.hFlip = 0;
		obj.vFlip = 0;

		obj.gfxIndex = particle.baseTile;
		obj.palette = particle.palette;
		obj.colorMode = OBJCOLOR_16;
		obj.blendMode = OBJMODE_NORMAL;

		obj.priority = OBJPRIORITY_1;

		obj.x = particle.x;
		obj.y = particle.y;

		obj.size  = (ObjSize)  SPRITE_SIZE_SIZE(size);
		obj.shape = (ObjShape) SPRITE_SIZE_SHAPE(size);

		mainObjManager.objects.push_back(std::move(
			obj
		));
	}
}

BaseParticleDemo::Particle::Particle() {}
BaseParticleDemo::Particle::Particle(int x_, int y_, int baseTile_, int p_) : 
	x(x_), y(y_), width(1), height(1), baseTile(baseTile_), palette(p_) {}
BaseParticleDemo::Particle::Particle(int x_, int y_, int w, int h, int baseTile_, int p_) : 
	x(x_), y(y_), width(w), height(h), baseTile(baseTile_), palette(p_) {}

SpriteSize spriteSizeToEnum(int width, int height) {
	//round the width and height upwards to a multipiel of 8
	width +=7;//offset
	height +=7;
	width &= ~7;//and then round down
	width &= ~7;//which turns out to be rounding up thans to the offset

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
