#include "seadHash.h"

namespace sead
{
	bool HashCRC16::sInitialized;
	u16  HashCRC16::sTable[256];

	void HashCRC16::initialize()
	{
		for (int i = 0; i < 256; i++)
		{
			u16 val = i;

			for (int j = 0; j < 8; j++)
			{
				if (val & 1)
				{
					val >>= 1;
					val ^= 0xA001;
				}
				else
					val >>= 1;
			}

			sTable[i] = val;
		}

		sInitialized = true;
	}

	u16 HashCRC16::calcHash(void const *data, u32 length)
	{
		if (!sInitialized)
			initialize();

		u16 hash = 0;

		for (u32 i = 0; i < length; i++)
			hash = sTable[((u8 *)data)[i] ^ (hash & 0xFF)] ^ (hash >> 8);

		return hash;
	}

	u16 HashCRC16::calcStringHash(char const *string)
	{
		if (!sInitialized)
			initialize();

		u16 hash = 0;

		while (*string)
			hash = sTable[*string++ ^ (hash & 0xFF)] ^ (hash >> 8);

		return hash;
	}

	bool HashCRC32::sInitialized;
	u32  HashCRC32::sTable[256];

	void HashCRC32::initialize()
	{
		for (int i = 0; i < 256; i++)
		{
			u32 val = i;

			for (int j = 0; j < 8; j++)
			{
				if (val & 1)
				{
					val >>= 1;
					val ^= 0xEDB88320;
				}
				else
					val >>= 1;
			}

			sTable[i] = val;
		}

		sInitialized = true;
	}

	u32 HashCRC32::calcHash(void const *data, u32 length)
	{
		if (!sInitialized)
			initialize();

		u32 hash = ~0;

		for (u32 i = 0; i < length; i++)
			hash = sTable[((u8 *)data)[i] ^ (hash & 0xFF)] ^ (hash >> 8);

		return ~hash;
	}

	u32 HashCRC32::calcStringHash(char const *string)
	{
		if (!sInitialized)
			initialize();

		u32 hash = ~0;

		while (*string)
			hash = sTable[*string++ ^ (hash & 0xFF)] ^ (hash >> 8);

		return ~hash;
	}
}