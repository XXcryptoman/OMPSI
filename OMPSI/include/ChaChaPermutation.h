#pragma once
#include "Defines.h"

namespace OMPSI
{	
        class ChaChaPermutation
        {
          public:
                   ChaChaPermutation();
                   ~ChaChaPermutation();

                  void ChaChaP(u8* input,u8* output);
        };
}
