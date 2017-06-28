#include "spotlightDemo.h"
#include "vrambatcher.h"

SpotLightDemo::SpotLightDemo() {}
SpotLightDemo::~SpotLightDemo() {}

void SpotLightDemo::Load() {}
void SpotLightDemo::Unload() {}

void SpotLightDemo::PrepareFrame(VramBatcher &batcher) {
	float leftAngle = angle - spread;
	float rightAngle = angle + spread;

	float cosLeft = cos(leftAngle);
	float sinLeft = sin(leftAngle);

	float cosRight = cos(rightAngle);
	float sinRight = sin(rightAngle);

	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {

		float yLen = scanline - lightY;

		float leftD = scanline / sinLeft;
		float leftXLen = sqrt(leftD*leftD - yLen*yLen);
		float leftX = leftXLen + lightX;

		float rightD = scanline / sinRight;
		float rightXLen = sqrt(rightD*rightD - yLen*yLen);
		float rightX = rightXLen + lightX;

		if (leftAngle <= 0 && rightAngle >= 0) {
			//left up, right down (right)
			//left is above, right is bellow
			//right side of the window is the right screen border
			if (scanline < lightY) {
				batcher.AddPoke(scanline, leftX, WIN0_X0);
			} else if (scanline > lightY) {
				batcher.AddPoke(scanline, rightX, WIN0_X0);
			} else {
				batcher.AddPoke(scanline, lightX, WIN0_X0);
			}
			batcher.AddPoke(scanline, SCREEN_WIDTH, WIN0_X1);
		} else if (leftAngle >=0 && rightAngle <=0) {
			//left down, right up (left)
			//left is bellow, right is above
			//left side of the window is the left screen border
			batcher.AddPoke(scanline, 0, WIN0_X0);
			if (scanline < lightY) {
				batcher.AddPoke(scanline, rightX, WIN0_X1);
			} else if (scanline > lightY) {
				batcher.AddPoke(scanline, leftX, WIN0_X1);
			} else {
				batcher.AddPoke(scanline, lightX, WIN0_X1);
			}
		} else if (leftAngle < 0 && rightAngle < 0) {
			//both pointing up (up)
			//left is on the left side of the screen and right is on the right side of the screen
			batcher.AddPoke(scanline, leftX, WIN0_X0);
			batcher.AddPoke(scanline, rightX, WIN0_X1);
		} else if( leftAngle >0 && rightAngle>0) {
			//left down, right down (down)
			//left is on the right side of the screen and right is on the left side of the screen
			batcher.AddPoke(scanline, rightX, WIN0_X0);
			batcher.AddPoke(scanline, leftX, WIN0_X1);
		} if (leftAngle == 0 && rightAngle == 0) {
			//180 degree light, degenerate case
			if (angle < 0) {
				//light on the bottom side
			} else {
				//light on the top side
			}
		}
	}
}