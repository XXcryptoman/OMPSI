#pragma once

#include "Defines.h"

#include <vector>

namespace OMPSI {

	class OMPsiSender {
	public:
                               
		OMPsiSender() {}
                        
                                 LinearCode mCode;


		void run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& senderSet);

	};

}