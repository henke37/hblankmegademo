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
}

void TallTextDemo::Unload() {
	REG_BG0VOFS = 0;
}

void TallTextDemo::AcceptInput() {
}

void TallTextDemo::PrepareFrame(VramBatcher & batcher) {

	buildTileMap();

	//setup scroll advancements
	unsigned int totalAdvancement = 0;
	int line = 0;
	for(int row = 0; row < rowCount; row += 2) {
		line = row * rowHeight + rowHackPos;
		totalAdvancement += (rowHeight-rowHackPos);//skip ahead, past the empty lines in the lower tile
		batcher.AddPoke(line, totalAdvancement, &REG_BG0VOFS);
	}
}

void TallTextDemo::buildTileMap() {
	TileMapEntry16 *tilemap= (TileMapEntry16 *)bgGetMapPtr(0);

	for(int textRowIndex = 0; textRowIndex < textRowCount; ++textRowIndex) {
		char *textRowPtr = textRows + textRowIndex * textRowWidth;
		for(int col = 0; col < textRowWidth && *textRowPtr; ++col, ++textRowPtr) {
			int baseRow = textRowIndex * 2;
			char c = *textRowPtr;
			tilemap[(baseRow  )*textRowWidth +col].index = charToTile(c,false);
			tilemap[(baseRow+1)*textRowWidth +col].index = charToTile(c,true);
		}
	}
}

int TallTextDemo::charToTile(char, bool) {
	return 0;
}
