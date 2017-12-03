#include "flutterDemo.h"

#include <nds/arm9/video.h>
#include <nds/dma.h>
#include <stdio.h>
#include <cstdlib>

using std::rand;

extern uint16_t objTileData[8 * 8 / 4];
extern _palette bgPalette;
extern _palette objPalette;

FlutterDemo::FlutterDemo() {}
FlutterDemo::~FlutterDemo() {}

void FlutterDemo::Load() {
	BaseParticleDemo::Load();

	setupParticles();
	loadGraphics();
}

void FlutterDemo::Unload() {
	BaseParticleDemo::Unload();
}

void FlutterDemo::updateParticles() {

	for(Particle &particle : particles) {
		if(rand() % 5 != 0) continue;

		switch(rand() % 4) {
		case 0:
			if(particle.x <= 0) continue;
			particle.x--;
			break;
		case 1:
			if(particle.x >= SCREEN_WIDTH) continue;
			particle.x++;
			break;
		case 2:
			if(particle.y <= 0) continue;
			particle.y--;
			break;
		case 3:
			if(particle.y >= SCREEN_HEIGHT) continue;
			particle.y++;
			break;
		}
	}
}

void FlutterDemo::AcceptInput() {}

void FlutterDemo::setupParticles() {
	for(int y = 0; y < SCREEN_HEIGHT; y += 10) {
		for(int x = 0; x < SCREEN_WIDTH; x += 10) {
			particles.push_back(std::move(
				Particle(x, y, 0, 0)
			));
		}
	}
	printf("Particle count: %i\n", particles.size());
}

void FlutterDemo::loadGraphics() {

	vramSetBankA(VRAM_A_MAIN_SPRITE);

	//load pixel data
	dmaCopyWords(3, objTileData, SPRITE_GFX,sizeof(objTileData));

	//setup palettes
	dmaCopyWords(3, bgPalette, BG_PALETTE, sizeof(bgPalette));
	dmaCopyWords(3, objPalette, SPRITE_PALETTE, sizeof(bgPalette));
}

uint16_t objTileData[8 * 8 / 4] = {
	1,1,2,2,0
};

_palette bgPalette = {RGB8(0x70,0x70,0x70)};
_palette objPalette = {
	RGB8(255,0,255),RGB8(255,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(0,255,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(0,0,255),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(255,255,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(255,0,255),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(0,255,255),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(255,0,255),RGB8(255,255,255),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
	RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),RGB8(0,0,0),
RGB8(0,0,0)};