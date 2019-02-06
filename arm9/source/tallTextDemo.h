#ifndef TALL_TEXT_DEMO_H
#define TALL_TEXT_DEMO_H

#include "demo.h"

class TallTextDemo : public HBlankDemo {
public:
	TallTextDemo();
	~TallTextDemo();

	void Load();
	void Unload();

protected:
	void AcceptInput();
	void PrepareFrame(VramBatcher &batcher);
private:
	int charToTile(char,bool);
	void LoadFont();
	void LoadText();

	const int rowCount = 24;
	const int rowHeight = 12;

	int textRowCount;
	const int textRowWidth = 256/8;
	char *textRows;

	unsigned int baseScroll = 0;
	const int scrollMax = 42;
};


#endif // !TALL_TEXT_DEMO_H
