#include "seadRandom.h"

int main()
{
	sead::Random r;
	r.init(0xcafebabe);
	printf("Random number: 0x%I32x\n", r.getU32());
	printf("Random number: 0x%I64x\n", r.getU64());
	return 0;
}