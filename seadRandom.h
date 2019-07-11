#include "common.h"

namespace sead
{
	class Random
	{
	public:
		void init();
		void init(u32 seed);
		void init(u32 seed1, u32 seed2, u32 seed3, u32 seed4);
		u32  getU32();
		u64  getU64();
		void getContext(u32 *seed1, u32 *seed2, u32 *seed3, u32 *seed4) const;

	private:
		u32  mContext[4];
	};
}