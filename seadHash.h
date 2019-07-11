#include "common.h"

namespace sead
{
	class HashCRC32
	{
	public:
		static void initialize();
		static u32  calcHash(void const *data, u32 length);
		static u32  calcStringHash(char const *string);

		static bool sInitialized;
		static u32  sTable[256];
	};
}