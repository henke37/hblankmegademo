#include "superParallaxDemo.h"
#include "vrambatcher.h"

SuperParallaxDemo::SuperParallaxDemo() {}
SuperParallaxDemo::~SuperParallaxDemo() {}
void SuperParallaxDemo::Load() {}
void SuperParallaxDemo::Unload() {}

void SuperParallaxDemo::PrepareFrame(VramBatcher &batcher) {


}

SuperParallaxDemo::ParallaxRegion::ParallaxRegion() {
}

SuperParallaxDemo::ParallaxRegion::~ParallaxRegion() {
}

void SuperParallaxDemo::ParallaxRegion::tick() {
	wobblePhase += wobbleRate;
}