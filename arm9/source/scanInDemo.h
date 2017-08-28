#ifndef SCANINDEMO_H
#define SCANINDEMO_H

#include "demo.h"

class ScanInDemo : public Demo {
public:
	ScanInDemo();
	~ScanInDemo();

	void Load();
	void Unload();

protected:
	void AcceptInput();
	void PrepareFrame(VramBatcher &batcher);

private:
	int startLine;
};

#endif