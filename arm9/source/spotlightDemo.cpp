#include "spotlightDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/window.h>
#include <cmath>

SpotLightDemo::SpotLightDemo() {}
SpotLightDemo::~SpotLightDemo() {}

void SpotLightDemo::Load() {
	setupDefaultBG();
	REG_DISPCNT |= DISPLAY_WIN0_ON;
}
void SpotLightDemo::Unload() {
	REG_DISPCNT &= ~DISPLAY_WIN0_ON;
}

void SpotLightDemo::PrepareFrame(VramBatcher &batcher) {
	float leftAngle = angle - spread;
	float rightAngle = angle + spread;

	if (leftAngle == 0 && rightAngle == 0) {
		//180 degree light, degenerate case
		if (angle < 0) {
			//light on the bottom side
			windowSetBounds(WINDOW_0, 0, SCREEN_WIDTH, lightY, SCREEN_HEIGHT);
		} else {
			//light on the top side
			windowSetBounds(WINDOW_0, 0, SCREEN_WIDTH, 0, lightY);
		}
		return;
	}

	batcher.AddPoke(0, 0, &WIN0_Y0);
	batcher.AddPoke(0, SCREEN_HEIGHT, &WIN0_Y1);

	float sinLeft = std::sin(leftAngle);
	float sinRight = std::sin(rightAngle);

	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {

		float yLen = scanline - lightY;

		float leftD = scanline / sinLeft;
		float leftXLen = std::sqrt(leftD*leftD - yLen*yLen);
		float leftXF = leftXLen + lightX;

		int leftX = (leftXF < 0 ? 0 : (leftXF > SCREEN_WIDTH ? SCREEN_WIDTH : leftXF));

		float rightD = scanline / sinRight;
		float rightXLen = std::sqrt(rightD*rightD - yLen*yLen);
		float rightXF = rightXLen + lightX;

		int rightX = (rightXF < 0 ? 0 : (rightXF > SCREEN_WIDTH ? SCREEN_WIDTH : rightXF));

		if (leftAngle <= 0 && rightAngle >= 0) {
			//left up, right down (right)
			//left is above, right is bellow
			//right side of the window is the right screen border
			if (scanline < lightY) {
				batcher.AddPoke(scanline, leftX, &WIN0_X0);
			} else if (scanline > lightY) {
				batcher.AddPoke(scanline, rightX, &WIN0_X0);
			} else {
				batcher.AddPoke(scanline, lightX, &WIN0_X0);
			}
			batcher.AddPoke(scanline, SCREEN_WIDTH, &WIN0_X1);
		} else if (leftAngle >=0 && rightAngle <=0) {
			//left down, right up (left)
			//left is bellow, right is above
			//left side of the window is the left screen border
			batcher.AddPoke(scanline, 0, &WIN0_X0);
			if (scanline < lightY) {
				batcher.AddPoke(scanline, rightX, &WIN0_X1);
			} else if (scanline > lightY) {
				batcher.AddPoke(scanline, leftX, &WIN0_X1);
			} else {
				batcher.AddPoke(scanline, lightX, &WIN0_X1);
			}
		} else if (leftAngle < 0 && rightAngle < 0) {
			//both pointing up (up)
			//left is on the left side of the screen and right is on the right side of the screen
			batcher.AddPoke(scanline, leftX, &WIN0_X0);
			batcher.AddPoke(scanline, rightX, &WIN0_X1);
		} else if( leftAngle >0 && rightAngle>0) {
			//left down, right down (down)
			//left is on the right side of the screen and right is on the left side of the screen
			batcher.AddPoke(scanline, rightX, &WIN0_X0);
			batcher.AddPoke(scanline, leftX, &WIN0_X1);
		} 
	}
}