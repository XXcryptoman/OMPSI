#include "CuckooHasher.h"

#include <random>

#include <numeric>

namespace OMPSI
{


	CuckooHasher::CuckooHasher()
		:mTotalTries(0)
	{
	}

	CuckooHasher::~CuckooHasher()
	{
	}

	
               
        u64 CuckooHasher:: get_stash_size(u64 neles)
        {
		if (neles >= (1 << 24))
			return 2;
		if (neles >= (1 << 20))
			return 3;
		if (neles >= (1 << 16))
			return 4;
		if (neles >= (1 << 12))
			return 6;
		if (neles >= (1 << 8))
			return 12;

		return 12; //other

	   //	throw std::runtime_error("get_stash_size: rt error at " LOCATION);

	 }


       
	void CuckooHasher::init(u64 cuckooSize, u64 simpleSize)
	{
		mCuckooSize = cuckooSize;
		mSimpleSize = simpleSize;
		mBinCount = 1.2*cuckooSize;
		mMaxStashSize = get_stash_size(cuckooSize);
		
		mBins.resize(mBinCount);
	}

	void CuckooHasher::insertItem(u64 IdxItem, std::array<std::vector<block>, 3>& hashs, u8 hashIdx, u64 numTries)
	{ 
		++mTotalTries;

		u64& xrHashVal = *(u64*)&hashs[hashIdx][IdxItem];

		auto addr = (xrHashVal) % mBinCount;


		if (mBins[addr].isEmpty())
		{
			// empty, place it here.
			mBins[addr].mIdx = IdxItem; 
			mBins[addr].mHashIdx = hashIdx;

		}
		else if(numTries <mCuckooSize) 
		{
			// mN times => evict  
			u64 evictIdx = mBins[addr].mIdx;
			u8 idxHash = mBins[addr].mHashIdx;


			mBins[addr].mIdx= IdxItem;
			mBins[addr].mHashIdx = hashIdx;
			
			// increments tries, %3 we use only 3 hash functions!
			insertItem(evictIdx, hashs, (idxHash + 1) % 3, numTries + 1);
		}
		else
		{
			// put in stash			
			mStash.emplace_back(IdxItem, hashIdx);
		}
	}
	void CuckooHasher::insertItems(std::array<std::vector<block>, 3>& hashs)
	{
		for (u64 i = 0; i < hashs[0].size(); ++i)
		{
			insertItem(i,hashs,0,0);
		}

                       

		mStash.resize(mMaxStashSize);
	}
}
