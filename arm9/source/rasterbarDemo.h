#ifndef RASTERBARDEMO_H
#define RASTERBARDEMO_H

#include "demo.h"

class RasterBarDemo : public Demo {
public:
	RasterBarDemo();
	~RasterBarDemo();

	void Load();
	void Unload();

protected:
	void AcceptInput();
	void PrepareFrame(VramBatcher &batcher);
};

#endif