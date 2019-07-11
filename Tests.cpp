#include "seadHash.h"

int main()
{
	sead::HashCRC32 h;
	h.initialize();
	printf("0x%x\n", h.calcStringHash("test"));
	printf("0x%x\n", h.calcHash("test", 4));
	return 0;
}