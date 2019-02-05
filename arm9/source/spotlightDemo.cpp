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
#define MAX_SPREAD M_PI/2
#define MIN_SPREAD M_PI/32

SpotLightDemo::SpotLightDemo() : lightX(128), lightY(96), angle(M_PI/4), spread(M_PI/16) {}
SpotLightDemo::~SpotLightDemo() {}

float normalizeAngle(float x) {
    // Wrap angle in [-pi, pi]
    x = fmod(x + M_PI, FULL_ROTATION);
    return x >= 0 ? (x - M_PI) : (x + M_PI);
}

int clamp(int n, int min, int max) {
    return std::max(min, std::min(n, max));
}

void SpotLightDemo::PrepareFrame(VramBatcher &batcher) {
	WindowingDemo::PrepareFrame(batcher);
	float leftAngle = normalizeAngle(angle + spread);
	float rightAngle = normalizeAngle(angle - spread);

    int top = 0, bottom = SCREEN_HEIGHT - 1;

    if (rightAngle >= 0 && leftAngle >= 0) {
        bottom = lightY;
    } else if (leftAngle <= 0 && rightAngle <= 0) {
        top = lightY;
    }
    top = clamp(top, 0, SCREEN_HEIGHT - 1);
    bottom = clamp(bottom, 0, SCREEN_HEIGHT - 1);

	WIN0_Y0 = top;
	WIN0_Y1 = bottom;

    float tanLeft = std::tan(leftAngle);
    float tanRight = std::tan(rightAngle);

	for (int scanline = top; scanline < bottom; ++scanline) {
        int left = lightX, right = lightX;
        if (leftAngle > 0 && rightAngle > 0) {
            left += (lightY - scanline) / tanLeft;
            right += (lightY - scanline) / tanRight;
        } else if (leftAngle < 0 && rightAngle < 0) {
            left += (lightY - scanline) / tanRight;
            right += (lightY - scanline) / tanLeft;
        } else if (leftAngle > 0 && rightAngle < 0) {
            if (lightY > scanline)
                left += (lightY - scanline) / tanLeft;
            else
                left += (lightY - scanline) / tanRight;
            right = SCREEN_WIDTH - 1;
        } else {
            if (lightY > scanline)
                right += (lightY - scanline) / tanRight;
            else
                right += (lightY - scanline) / tanLeft;
            left = 0;
        }
        left = clamp(left, 0, SCREEN_WIDTH - 1);
        right = clamp(right, 0, SCREEN_WIDTH - 1);
        batcher.AddPoke(scanline, left, &WIN0_X0);
        batcher.AddPoke(scanline, right, &WIN0_X1);
	}
}

void SpotLightDemo::AcceptInput() {
	WindowingDemo::AcceptInput();
	auto keys = keysCurrent();

	if (keys & KEY_L) {
		angle -= 0.02;
        angle = normalizeAngle(angle);
		printf("Angle: %f\n", angle);
	} else if (keys & KEY_R) {
		angle += 0.02;
        angle = normalizeAngle(angle);
		printf("Angle: %f\n", angle);
	}

	if (keys & KEY_X && spread < MAX_SPREAD) {
		spread += 0.02;
		printf("Spread: %f\n", spread);
	} else if (keys & KEY_Y && spread > MIN_SPREAD) {
		spread -= 0.02;
        if (spread < MIN_SPREAD)
        {
            spread = MIN_SPREAD;
        }
		printf("Spread: %f\n", spread);
	}

	if (keys & KEY_UP) {
		--lightY;
        printf("Light XY: %d, %d\n", lightX, lightY);
	} else if (keys & KEY_DOWN) {
		++lightY;
        printf("Light XY: %d, %d\n", lightX, lightY);
	}

	if (keys & KEY_LEFT) {
		--lightX;
        printf("Light XY: %d, %d\n", lightX, lightY);
	} else if (keys & KEY_RIGHT) {
		++lightX;
        printf("Light XY: %d, %d\n", lightX, lightY);
	}
}
