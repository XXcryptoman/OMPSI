#pragma once

#include "Defines.h"

#include <vector>

namespace OMPSI {

	class OMPsiReceiver {
	public:
      
                                 OMPsiReceiver () {}

                                 std::vector<u64> mIntersection;                                
                                 LinearCode mCode;
                                 
                                
		

		void run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& receiverSet);

	};

}
