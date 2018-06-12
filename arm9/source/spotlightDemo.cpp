#include "spotlightDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/window.h>
#include <cmath>
#include <nds/arm9/input.h>

#define M_PI       3.14159265358979323846
#define FULL_ROTATION M_PI*2
#define D45 FULL_ROTATION/8
#define MD45 FULL_ROTATION/-8
#define D135 (FULL_ROTATION/4+D45)
#define MD135 -D135
#define MAX_SPREAD FULL_ROTATION/2
#define MIN_SPREAD FULL_ROTATION/64

SpotLightDemo::SpotLightDemo() : lightX(128), lightY(96), angle(M_PI/2), spread(M_PI/8) {}
SpotLightDemo::~SpotLightDemo() {}

float yPosForAngleAndSide(float angle, int side) {
	return side / std::tan(angle);
}

void SpotLightDemo::PrepareFrame(VramBatcher &batcher) {
	WindowingDemo::PrepareFrame(batcher);
	float leftAngle  = angle - spread;
	float rightAngle = angle + spread;
	if (leftAngle  >  FULL_ROTATION/2) leftAngle  -= FULL_ROTATION;
	if (rightAngle >  FULL_ROTATION/2) rightAngle -= FULL_ROTATION;
	if (leftAngle  < -FULL_ROTATION/2) leftAngle  += FULL_ROTATION;
	if (rightAngle < -FULL_ROTATION/2) rightAngle += FULL_ROTATION;


	float tanLeft  = std::tan(-leftAngle);
	float tanRight = std::tan(-rightAngle);
	float cosLeft  = std::cos(leftAngle);
	float cosRight = std::cos(rightAngle);
	float normLeft  = -1 / tanLeft;
	float normRight = -1 / tanRight;

	int top;
	int bottom;

	bool pointsLeft=false, pointsRight=false, pointsUp=false, pointsDown=false;

	if (angle < D45 && angle > MD45) {
		pointsRight = true;
		puts("right");
		top    = lightY + yPosForAngleAndSide(leftAngle,  SCREEN_WIDTH - lightX);
		bottom = lightY + yPosForAngleAndSide(rightAngle, SCREEN_WIDTH - lightX);
		if (top > lightY) top = lightY;
		if (bottom < lightY) bottom = lightY;
	} else if (angle > MD135 && angle < MD45) {
		pointsUp = true;
		puts("up");
		top = 0;
		bottom = lightY;
	} else if (angle > D45 && angle < D135) {
		pointsDown = true;
		puts("down");
		top = lightY;
		bottom = SCREEN_HEIGHT;
	} else {
		pointsLeft = true;
		puts("left");
		top    = lightY + yPosForAngleAndSide(rightAngle, lightX);
		bottom = lightY + yPosForAngleAndSide(leftAngle,  lightX);
		if (top > lightY) top = lightY;
		if (bottom < lightY) bottom = lightY;
	}

	if (top < 0) top = 0;
	if (bottom > SCREEN_HEIGHT) bottom = SCREEN_HEIGHT;
	if (top > bottom) {
		printf("top > bottom! %i %i\n", top, bottom);
	}

	WIN0_Y0=top;
	WIN0_Y1=bottom-1;


	bool pointsSideways = pointsLeft || pointsRight;


	//printf("%f %f\n", cosLeft, cosRight);

	for (int scanline = top; scanline < bottom; ++scanline) {

		float yLen = lightY - scanline;


		float xLenLeft  = pointsSideways ? (yLen*normLeft) : (yLen*tanLeft);
		float xLenRight = pointsSideways ? (yLen*normRight) : (yLen*tanRight);

		float leftXF  = lightX+xLenLeft;
		float rightXF = lightX+xLenRight;

		int leftX  = (leftXF  < 0 ? 0 : (leftXF  > SCREEN_WIDTH - 1 ? SCREEN_WIDTH - 1 : leftXF ));
		int rightX = (rightXF < 0 ? 0 : (rightXF > SCREEN_WIDTH - 1 ? SCREEN_WIDTH  -1 : rightXF));

		if (scanline == 100) {
			printf("%i %i\n", leftX, rightX);
		}

		if (pointsRight) {
			
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
		} else if (pointsLeft) {
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
		} else if (pointsUp) {
			//both pointing up (up)
			//left is on the left side of the screen and right is on the right side of the screen
			batcher.AddPoke(scanline, leftX, &WIN0_X0);
			batcher.AddPoke(scanline, rightX, &WIN0_X1);
		} else if(pointsDown) {
			//left down, right down (down)
			//left is on the right side of the screen and right is on the left side of the screen
			batcher.AddPoke(scanline, rightX, &WIN0_X0);
			batcher.AddPoke(scanline, leftX, &WIN0_X1);
		} 
	}
}

void SpotLightDemo::AcceptInput() {
	WindowingDemo::AcceptInput();
	auto keys = keysCurrent();

	if (keys & KEY_L) {
		angle -= 0.02;
		if (angle <= -FULL_ROTATION/2) angle += FULL_ROTATION;
		printf("Angle: %f\n", angle);
	} else if (keys & KEY_R) {
		angle += 0.02;
		if (angle >= FULL_ROTATION/2) angle -= FULL_ROTATION;
		printf("Angle: %f\n", angle);
	}

	if (keys & KEY_X && spread < MAX_SPREAD) {
		spread += 0.02;
		printf("Spread: %f\n", spread);
	} else if (keys & KEY_Y && spread > MIN_SPREAD) {
		spread -= 0.02;
		printf("Spread: %f\n", spread);
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
