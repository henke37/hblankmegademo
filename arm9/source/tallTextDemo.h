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

	const int rowCount = 24;
	const int rowHeight = 12;

	int textRowCount;
	const int textRowWidth = 24;
	char *textRows;
};


#endif // !TALL_TEXT_DEMO_H
