#include "ChaChaPermutation.h"
#include <numeric>
#include <algorithm>

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 20

namespace OMPSI
{
             ChaChaPermutation:: ChaChaPermutation()
             {
    
             }
 
             ChaChaPermutation:: ~ChaChaPermutation()
             {
    
             }
         
             void ChaChaPermutation:: ChaChaP(u8* input, u8* output)
             {
                         
	        u32* x=new u32[16];
              
	        for (u64 i = 0; i < 16; i++)	
		     memcpy((u8*)(x+i),input+4*i,4);
	          // memcpy((u8*)(&x[i]),input+4*i,4);
                         // 10 loops × 2 rounds/loop = 20 rounds
	        for (auto i = 0; i < ROUNDS; i += 2) 
                {
		
                  // Odd round
		  QR(x[0], x[4], x[ 8], x[12]); // column 0
		  QR(x[1], x[5], x[ 9], x[13]); // column 1
		  QR(x[2], x[6], x[10], x[14]); // column 2
		  QR(x[3], x[7], x[11], x[15]); // column 3
		
                  // Even round
		  QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
		  QR(x[1], x[6], x[11], x[12]); // diagonal 2
		  QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
		  QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
	         }
                        
                for (u64 i = 0; i < 16; i++)	
		     memcpy(output+4*i,(u8*)(x+i),4);
              //     memcpy(output+4*i,(u8*)(&x[i]),4);
	                         
             }

}
