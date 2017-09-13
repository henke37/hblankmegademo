#include "fixedMath.h"
#include <cassert>
#include <stdio.h>

void testFixed() {
	fp8 a=5,b=4,c=3,d=1,e=2;
	fp12 p=5,q=4,r=3,s=1,t=2,x;
	FixedAngle h,j,i;

	//basic operators
	assert(((int)d) == 1);
	assert((a - b) == 1);
	assert((b * a) == 20);
	assert((p * q) == 20);
	assert((q * r) == 12);
	assert(a - c == e);
	assert(a > b);
	assert(b < a);
	
	//modifying operators
	assert(c - 2==1_fp8);
	assert(c==3_fp8);
	c+=12_fp8;//3+12=15
	assert(c==15);
	c-=10;
	assert(c==5);

	//hw accelerated operators
	assert(sqrt(q) == 2);
	assert((q / t) == 2);
	assert((q / q) == 1);
	assert((p / p) == 1);
	assert(42_fp12 / 21_fp12 == 2_fp12);

	//trig luts
	//fprintf(stderr, "%i\n", (90_fixedAngle).raw);
	//h=asin(1_fp12/2_fp12);
	//fprintf(stderr, "%i\n%f", h.raw, (float)h);
	
	assert(sin(0_fixedAngle) == 0);
	assert(cos(0_fixedAngle) == 1);
	assert(sin(90_fixedAngle) == 1_fp12);
	assert(cos(90_fixedAngle) == 0_fp12);

	//failing tests
	//assert(5_fp12 % 4_fp12 == 1_fp12);
	//assert((fp12)(p << 2) == 10);
}