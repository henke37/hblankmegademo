#ifndef SUPERPARALLAXDEMO_H
#define SUPERPARALLAXDEMO_H

#include "demo.h"
#include <vector>

class SuperParallaxDemo : public Demo {
public:
	SuperParallaxDemo();
	virtual ~SuperParallaxDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();

	class ParallaxRegion {
	public:
		ParallaxRegion();
		~ParallaxRegion();

		int top;
		int bottom;
		float scrollRate;
		float wobbleRate;
		float wobbleAmplitude;
		float wobblePhase;
		float wobbleLinePhase;

		void tick();
	};

	std::vector<ParallaxRegion> regions;

private:
};

#endif#pragma once
