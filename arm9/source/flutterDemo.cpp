#include "flutterDemo.h"

#include <nds/arm9/video.h>
#include <nds/dma.h>

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

void FlutterDemo::PrepareFrame(VramBatcher &) {
	buildObjectsFromParticles();
}

void FlutterDemo::AcceptInput() {}

void FlutterDemo::setupParticles() {
	for(int y = 0; y < SCREEN_HEIGHT; y += 10) {
		for(int x = 0; x < SCREEN_WIDTH; x += 10) {
			particles.push_back(std::move(
				Particle(x, y, 0)
			));
		}
	}
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
	1,0
};

_palette bgPalette = {RGB8(0,0,0)};
_palette objPalette = {RGB8(255,0,255),RGB8(255,255,255),
RGB8(255,0,0),RGB8(0,255,0),RGB8(0,0,255),
RGB8(255,255,0),RGB8(255,0,255),RGB8(0,255,255),
RGB8(0,0,0)};