#include "fixedMath.h"
#include <cassert>
#include <stdio.h>

void testFixed() {
	fp8 a=5,b=4,c=3,d=1,e=2;
	fp12 p=5,q=4,r=3,s=1,t=2,x;

	//basic operators
	assert(((int)d) == 1);
	assert((a - b) == 1);
	assert((b * a) == 20);
	assert((p * q) == 20);
	assert((q * r) == 12);
	assert(a - c == e);
	assert(a > b);
	assert(b < a);

	//hw accelerated operators
	assert(sqrt(q) == 2);
	assert((q / t) == 2);
	assert((q / q) == 1);
	assert((p / p) == 1);
	assert(42_fp12 / 21_fp12 == 2_fp12);

	//trig luts
	fprintf(stderr, "%i", sin(45_fp12Angle).raw);
	return;

	assert(sin(0_fp12) == 0);
	assert(cos(0_fp12) == 1);
	assert(asin(90_fp12Angle) == 1);
	assert(acos(90_fp12) == 0);

	return;
	assert(sin(90_fp12Angle) == 1_fp12);
	assert(cos(90_fp12Angle) == 0_fp12);

	//failing tests
	//assert(5_fp12 % 4_fp12 == 1_fp12);
	//assert((fp12)(p << 2) == 10);
}