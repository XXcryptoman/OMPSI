#pragma once
#include "Defines.h"

namespace OMPSI
{	
	class CuckooHasher
	{
	public:
		CuckooHasher();
		~CuckooHasher();

		struct Bin
		{
			Bin()
				:mIdx(-1),
				mHashIdx(0)
			{}

			Bin(u64 i, u8 v)
				: mIdx(i)
				, mHashIdx(v) {}

			u64 mIdx;
			u8 mHashIdx;


			bool isEmpty() const
			{
				return mIdx == u64(-1);
			}
		}; 


		u64 mBinCount, mCuckooSize, mSimpleSize, mMaxStashSize,  mTotalTries;

		std::vector<Bin> mBins;
		std::vector<Bin> mStash;
		
		// void print() const;

                u64 get_stash_size(u64 neles);


		void init(u64 cuckooSize, u64 simpleSize);
		void insertItem(u64 IdxItem, std::array<std::vector<block>, 3>& hashs, u8 hashIdx , u64 numTries);
		void insertItems(std::array<std::vector<block>,3>& hashs);
	};

}
