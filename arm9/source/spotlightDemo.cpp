#include "spotlightDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/window.h>
#include <cmath>
#include <nds/arm9/input.h>

#define M_PI       3.14159265358979323846

SpotLightDemo::SpotLightDemo() : lightX(128), lightY(0), angle(M_PI/2), spread(M_PI/8) {}
SpotLightDemo::~SpotLightDemo() {}

void SpotLightDemo::Load() {
	setupDefaultBG();
	REG_DISPCNT |= DISPLAY_WIN0_ON;

	WIN_IN = BIT(0);
	WIN_OUT = 0;
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
			//windowSetBounds(WINDOW_0, 0, SCREEN_WIDTH-1, lightY, SCREEN_HEIGHT-1);
		} else {
			//light on the top side
			//windowSetBounds(WINDOW_0, 0, SCREEN_WIDTH-1, 0, lightY);
		}
		//return;
	}

	int top = lightY;
	if (top < 0) top = 0;
	int bottom = SCREEN_HEIGHT;

	WIN0_Y0=top;
	WIN0_Y1=bottom-1;

	float tanLeft = std::tan(leftAngle);
	float tanRight = std::tan(rightAngle);

	//printf("%f %f\n", cosLeft, cosRight);

	for (int scanline = top; scanline < bottom; ++scanline) {

		float yLen = scanline - lightY;

		float leftXLen = yLen*tanLeft;
		//leftXLen = 20;
		float leftXF = leftXLen + lightX;

		int leftX = (leftXF < 0 ? 0 : (leftXF > SCREEN_WIDTH-1 ? SCREEN_WIDTH-1 : leftXF));

		float rightXLen = yLen*tanRight;
		//rightXLen = 20;
		float rightXF = rightXLen + lightX;

		int rightX = (rightXF < 0 ? 0 : (rightXF > SCREEN_WIDTH-1 ? SCREEN_WIDTH-1 : rightXF));


		if (leftAngle >= 0 && rightAngle <= 0) {
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
			batcher.AddPoke(scanline, SCREEN_WIDTH-1, &WIN0_X1);
		} else if (leftAngle <= 0 && rightAngle >= 0) {
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

void SpotLightDemo::AcceptInput() {
	auto keys = keysCurrent();

	if (keys & KEY_L) {
		angle -= 0.02;
	} else if (keys & KEY_R) {
		angle += 0.02;
	}

	if (keys & KEY_X) {
		spread += 0.02;
	} else if (keys & KEY_Y) {
		spread -= 0.02;
	}

	if (keys & KEY_UP) {
		--lightY;
	} else if (keys & KEY_DOWN) {
		++lightY;
	}

	if (keys & KEY_LEFT) {
		--lightX;
	} else if (keys & KEY_RIGHT) {
		++lightX;
	}
}
