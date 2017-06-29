#ifndef SUPERPARALLAXDEMO_H
#define SUPERPARALLAXDEMO_H

#include "demo.h"
#include <vector>

typedef volatile signed long vs32;
typedef volatile signed short vs16;

struct BgPointerRecord {
	vu16* hOffset;
	vu16* vOffset;
	vu16* bgcnt;
	struct AffinePtrs {
		vs16 *A, *B, *C, *D;
		vs32 *X, *Y;
	} affine;
};
extern BgPointerRecord BgPointers[4];

class SuperParallaxDemo : public Demo {
public:
	SuperParallaxDemo();
	virtual ~SuperParallaxDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();

	int yPos;
	int xPos;

	class ParallaxRegion {
	public:
		ParallaxRegion();
		~ParallaxRegion();

		int top;
		int bottom;

		int depth;

		int mapBase;

		float scrollRate;
		float wobbleRate;
		float wobbleAmplitude;
		float wobblePhase;
		float wobbleLinePhase;

		void tick();

		void applyForScanline(int scanline, BgPointerRecord &bgPtrs, int xPos, int yPos, VramBatcher &);
	};

	std::vector<ParallaxRegion> regions;

private:
};

#endif#pragma once
