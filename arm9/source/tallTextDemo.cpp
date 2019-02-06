#include "tallTextDemo.h"

#include "vrambatcher.h"

#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/arm9/background.h>

TallTextDemo::TallTextDemo() {
}

TallTextDemo::~TallTextDemo() {
}

void TallTextDemo::Load() {
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 8, 0);

	LoadFont();
	LoadText();
}

void TallTextDemo::Unload() {
	REG_BG0VOFS = 0;
}

void TallTextDemo::AcceptInput() {
	auto keys = keysCurrent();

	if(keys & KEY_UP) {
		if(baseScroll > 0) baseScroll--;
	} else if(keys & KEY_DOWN) {
		if(baseScroll < scrollMax) baseScroll++;
	}
}

void TallTextDemo::PrepareFrame(VramBatcher & batcher) {
	//setup scroll advancements
	unsigned int totalAdvancement = baseScroll;
	int line = 0;
	TileMapEntry16 *tilemap= (TileMapEntry16 *)bgGetMapPtr(0);

	for(int textRowIndex = 0; textRowIndex < textRowCount; ++textRowIndex) {
		std::string &textRow = textRows[textRowIndex];
		for(int col = 0; col < textRowWidth && textRow[col]; ++col) {
			int baseRow = textRowIndex * 2;
			char c = textRow[col];
			tilemap[(baseRow  )*textRowWidth +col].index = charToTile(c,false);
			tilemap[(baseRow+1)*textRowWidth +col].index = charToTile(c,true);

			line = baseRow * rowHeight;
			totalAdvancement += (rowHeight - rowHeight);//skip ahead, past the empty lines in the upper tile
			batcher.AddPoke(line, totalAdvancement, &REG_BG0VOFS);
		}
	}
}

int TallTextDemo::charToTile(char, bool) {
	return 0;
}

void TallTextDemo::LoadFont() {}

void TallTextDemo::LoadText() {

}
