#include "demo.h"
#include "demoRunner.h"

#include <nds/arm9/background.h>
#include <nds/arm9/decompress.h>

static size_t fileSize(FILE *fp);

Demo::Demo() {}
Demo::~Demo() {}

void Demo::tick(VramBatcher &batcher) {
	AcceptInput();
	PrepareFrame(batcher);
}

void Demo::setupDefaultBG() {
	setupTilemapBG("P.pal.bin", "P.img.bin", "P.map.bin");
}

void Demo::setupTilemapBG(const char *paletteFile, const char *tileSetFile, const char *tileMapFile) {
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	int bgid = bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 12, 0);

	loadBGPalette(paletteFile);
	compressedFile2Vram(tileSetFile, bgGetGfxPtr(bgid));
	compressedFile2Vram(tileMapFile, bgGetMapPtr(bgid));

	u32 vMode = MODE_0_2D;
	vMode |= DISPLAY_BG0_ACTIVE;
	REG_DISPCNT = vMode;
}

void Demo::compressedFile2Vram(const char *filename, void *dst) {
	FILE *fp = fopen(filename, "r");

	size_t fSize = fileSize(fp);
	void *compressedFile = malloc(fSize);

	fread(compressedFile, fSize, 1, fp);

	fclose(fp);

	decompress(compressedFile, dst, LZ77Vram);

	free(compressedFile);
}

void Demo::loadBGPalette(const char *paletteFile) {

	FILE *palFile = fopen(paletteFile, "r");

	fread(BG_PALETTE, sizeof(_palette), 1, palFile);

	fclose(palFile);
}

size_t fileSize(FILE *fp) {
	size_t size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	return size;
}