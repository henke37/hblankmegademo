#include "fixedMath.h"
#include <cassert>

void testFixed() {
	fp8 a=5,b=4,c=3,d=1,e=2;
	fp12 p=5,q=4,r=3,s=1,t=2,x;


	assert(((int)d) == 1);
	assert((a - b) == 1);
	assert((b * a) == 20);
	assert((p * q) == 20);
	assert((q * r) == 12);
	assert(a - c == e);
	assert(a > b);
	assert(b < a);
	assert(sqrt(q) == 2);
	assert((q / t) == 2);
	assert((fp12)(p << 2) == 10);
}