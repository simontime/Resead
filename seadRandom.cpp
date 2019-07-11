#include "seadRandom.h"

namespace sead
{
	void Random::init()
	{
		init(GetTickCount());
	}

	void Random::init(u32 seed)
	{
		mContext[0] = 0x6C078965 * (seed        ^ (seed        >> 30)) + 1;
		mContext[1] = 0x6C078965 * (mContext[0] ^ (mContext[0] >> 30)) + 2;
		mContext[2] = 0x6C078965 * (mContext[1] ^ (mContext[1] >> 30)) + 3;
		mContext[3] = 0x6C078965 * (mContext[2] ^ (mContext[2] >> 30)) + 4;
	}
	
	void Random::init(u32 seed1, u32 seed2, u32 seed3, u32 seed4)
	{
		if ((seed1 | seed2 | seed3 | seed4) == 0) // seeds must not be all zero.
		{
			seed1 = 1;
			seed2 = 0x6C078967;
			seed3 = 0x714ACB41;
			seed4 = 0x48077044;
		}

		mContext[0] = seed1;
		mContext[1] = seed2;
		mContext[2] = seed3;
		mContext[3] = seed4;
	}

	u32 Random::getU32()
	{
		u32 n = mContext[0] ^ (mContext[0] << 11);

		mContext[0] = mContext[1];
		mContext[1] = mContext[2];
		mContext[2] = mContext[3];
		mContext[3] = n ^ (n >> 8) ^ mContext[3] ^ (mContext[3] >> 19);

		return mContext[3];
	}

	u64 Random::getU64()
	{
		u32 n1 = mContext[0] ^ (mContext[0] << 11);
		u32 n2 = mContext[1];
		u32 n3 = n1 ^ (n1 >> 8) ^ mContext[3];

		mContext[0] = mContext[2];
		mContext[1] = mContext[3];
		mContext[2] = n3 ^ (mContext[3] >> 19);
		mContext[3] = n2 ^ (n2 << 11) ^ ((n2 ^ (n2 << 11)) >> 8) ^ mContext[2] ^ (n3 >> 19);

		return ((u64)mContext[2] << 32) | mContext[3];
	}

	void Random::getContext(u32 *seed1, u32 *seed2, u32 *seed3, u32 *seed4) const
	{
		*seed1 = mContext[0];
		*seed2 = mContext[1];
		*seed3 = mContext[2];
		*seed4 = mContext[3];
	}
}