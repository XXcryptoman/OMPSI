#include "OMPsiSender.h"
#include "CuckooHasher.h" 
#include "ChaChaPermutation.h"
#include "bch511.h"

#include <array>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <thread>

namespace OMPSI {

	void OMPsiSender::run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& senderSet)  
            {
	
		                Timer timer;
                                u64 width=512;
                                u64 stepSize=65536;
                                u64 statSecPara=40;

                             ///////////////////// / Base OTs  /////////////////////////////
                               
   
                                IknpOtExtReceiver otExtReceiver;
		                otExtReceiver.genBaseOts(prng, ch);
		                BitVector choices(width);
		                std::vector<block> otMessages(width);
		                prng.get(choices.data(), choices.sizeBytes());
		                otExtReceiver.receive(choices, otMessages, prng, ch);
		            
                               
                                timer.setTimePoint("Sender base OT finished");

                             /////////////////////  Initialization //////////////////////////
                                //Initialization for the parameter of  simple hashing
                                 CuckooHasher mBins;                                 
                                 mBins.init(receiverSize, senderSize);                                    
                                 auto mNumStash=mBins.mMaxStashSize ;
                           

                                //Initialization for 3 hash h_1,h_2,h_3
                                 std::array<AES, 3> AESHASH;
                                 block commonKey;
                                 std::array<PRNG,3> commonprng;

                                 ChaChaPermutation  ChaChaP;



                             
                            /////////////////////  Simplehash ///////////////////////////  
                                   for (u64 i = 0; i < AESHASH.size(); i++)
                                   {
                                      commonprng[i].SetSeed(commonSeed[i]);
                                      commonprng[i].get((u8*)&commonKey, sizeof(block));
                                      AESHASH[i].setKey(commonKey);                                    


                                   }
   
                                   std::array<std::vector<block>, 3> aesHashBuffs;
                                  
                                      



                                   aesHashBuffs[0].resize(senderSize);
		                              aesHashBuffs[1].resize(senderSize);
		                               aesHashBuffs[2].resize(senderSize);
                               


                                  
                               


                                   for(u64 i=0; i<senderSize;i+=stepSize)
                                   {
                                       auto currentStepSize=senderSize-i <stepSize? senderSize-i : stepSize ;
                                       AESHASH[0].ecbEncBlocks(senderSet.data() + i, currentStepSize, aesHashBuffs[0].data() + i);
		                                   AESHASH[1].ecbEncBlocks(senderSet.data() + i, currentStepSize, aesHashBuffs[1].data() + i);
		                                   AESHASH[2].ecbEncBlocks(senderSet.data() + i, currentStepSize, aesHashBuffs[2].data() + i);
                                    }
			 
                                   
                                 
                                                        
                                 
                                   timer.setTimePoint("Simplehash finished");



                         



                             /////////////////////  OT Extension /////////////////////

                                   u64 numbin=mBins.mBinCount+mNumStash;
                                   u64 numbinround=((numbin+7)/8)*8;
                                   u64 numbinInbyte=numbinround/8;

                                   u64 numOtExt=numbinround+statSecPara;
                                   u64 numOtExtInbyte=numOtExt/8;

                                   u8* ColQ[width];
                                   std::vector<std::array<u8, 64>> RowQ(numOtExt);

                                   
                                   u8* SentBuff= new u8[64*senderSize+2]; 
                                   
                                   u8  *bug=new u8[1];
                                   memset(bug,0,1);

                                                                 
                                   
                                   
                                   

                                    





                                  

                                   for(u64 i=0;i<width;i+=8)
                                   {
                                          for(u64 j=i; j<i+8;j++)
                                           {
                                               ColQ[j]=new u8[numOtExtInbyte];
                                               PRNG  prng0(otMessages[j]);
                                               prng0.get(ColQ[j], numOtExtInbyte);
                                           }
                                          
                                          for(u64 k=0;k<numOtExt; k++)
                                          {
                                              RowQ[k][i>>3]=0;                                          
                                              for (u8 j=0; j<8; j++)
                                              {
                                                   RowQ[k][i>>3]|=(u8)((bool)(ColQ[i+j][k>>3] &( 1<<(~(k &7) )) ))<<(7-j) ;
                                              }
                                                                             
                                           }
                                   }
       
                                  


                              
                                   



                                  //transform bitvector to bytevector
                                   u8* choicesInbyte= new u8[64];
                                   for(u64 i=0;i<width;i+=8)
                                   {
                                          choicesInbyte[i>>3]=0;
                                          for(u64 j=0; j<8;j++)
                                          {
                                                 choicesInbyte[i>>3]|=(u8)((bool) choices[j+i])<<(7-j);
                                          }
                                   }

                                  

                                  


                                   
                                  timer.setTimePoint("ColQ is transformed to RowQ");
                              

                                    
                               
                     

                               //   u8* TempMask= new u8[64];
 
                                  u8* RecvBuff= new u8[64*senderSize];
                              //    u8* RecvBuff1= new u8[64*numOtExt];                                          
                                                                  
                                  auto binStart=0;
                                  auto binEnd=mBins.mBinCount;



                                  



                                //    ch.recv(RecvBuff1, 64*numOtExt); 

                                   for (u64 stepIdx=binStart; stepIdx<binEnd; stepIdx+=stepSize)
                                   {
                                        auto currentStepSize=binEnd-stepIdx<stepSize ? binEnd-stepIdx : stepSize; 
                                        auto stepEnd=stepIdx+currentStepSize;
                                          
                                        ch.recv(RecvBuff, 64*currentStepSize); 
                                        ch.asyncSend(bug,1);                        
                                      
                                        for(u64 bIdx=stepIdx,i=0; bIdx<stepEnd; bIdx++ ,i++)
                                        {                                                 
                                              for(u64 j=0;j<64; j++)
                                                  RowQ[bIdx][j]^=(RecvBuff[i*64+j]&choicesInbyte[j]);
                                              // for(u64 j=0;j<64; j++)
                                              //     RowQ[bIdx][j]^=(RecvBuff1[bIdx*64+j]&choicesInbyte[j]);
                                      
                                        }
                                   }
                    
                                  auto stashStart= binEnd;   
                                  auto stashEnd=stashStart+mNumStash;   



                                 


                               
                            
                                   ch.recv(RecvBuff, 64*mNumStash);
                                   ch.asyncSend(bug,1);
                                   for(u64 sIdx=stashStart,  i=0; sIdx<stashEnd; sIdx++,i++ )
                                   {
                                          for(u64 j=0;j<64; j++)
                                                RowQ[sIdx][j]^=(RecvBuff[i*64+j]&choicesInbyte[j]); 
                                      //    for(u64 j=0;j<64; j++)
                                      //           RowQ[sIdx][j]^=(RecvBuff1[sIdx*64+j]&choicesInbyte[j]);                                           
                         
                                   }
                                  
                             
                                  auto  checkStart= numbinround;   
                                  auto  checkEnd=checkStart+statSecPara;



                                



                               
                                ch.recv(RecvBuff, 64*statSecPara);
                                ch.asyncSend(bug,1);

                               for(u64 cIdx=checkStart,  i=0; cIdx<checkEnd; cIdx++,i++)
                               {
                                     for(u64 j=0;j<64; j++)
                                          RowQ[cIdx][j]^=(RecvBuff[i*64+j]&choicesInbyte[j]);   
                                  //   for(u64 j=0;j<64; j++)
                                    //      RowQ[cIdx][j]^=(RecvBuff1[cIdx*64+j]&choicesInbyte[j]);
       
                               }





                               timer.setTimePoint("OT Extension finished");





                           /////////////////////  Consistency Check /////////////////////

                              mCode.load(bch511_binary, sizeof(bch511_binary));
                              //stepSize
                              u8* RecvBuff2= new u8[64*statSecPara];  
                              
                              u8* tempQ= new u8[64];
                              u8* tempIn=new u8[10];

                         //   u8* checkSeed=new u8[sizeof(block)];  

                              u8* challenge= new u8[numbinInbyte];
                              u8* codeword= new u8[64];
                       

                               PRNG prngcheck;
                              for(auto i=0;i<statSecPara;i++)
                              {
                                    
                                     prngcheck.SetSeed(aesHashBuffs[1][i]); // In fact it needs the true random seed here
                                     
                               
                                     
                                   //   memcpy(SentBuff, (u8*)(aesHashBuffs[1].data()+i), sizeof(block)); 
                                     
                                   //   ch.asyncSend(SentBuff, sizeof(block));
                                     ch.asyncSend((u8*)(aesHashBuffs[1].data()+i), sizeof(block));

                                     prngcheck.get(challenge, numbinInbyte);



                                      memset(tempQ,0, 64);  
                                    
                                      for (u64 stepIdx=0; stepIdx<numbin; stepIdx+=8)
                                      {
                                                auto currentStepSize=numbin-stepIdx<8 ? numbin-stepIdx :8; 
                                                auto stepEnd=stepIdx+currentStepSize;

                                                for(auto bIdx=stepIdx; bIdx<stepEnd; bIdx++)
                                                {
                                                            if((bool)(challenge[bIdx>>3] & (1<<~(bIdx & 7)) ) )
                                                            {
                                                                     for(auto k=0;k<64;k++)
                                                                     {
                                                                             tempQ[k]^=RowQ[bIdx][k];                                                                            
                                                                     }
                                                             }       
                                                }
                                       }           
                                                             
                                      for(auto k=0;k<64;k++)
                                               tempQ[k]^=RowQ[numbinround+i][k];
                                       
                                      ch.recv(RecvBuff, 64);   
                                      ch.recv(RecvBuff2, 10);    
                                      
                                    //  memcpy(tempIn, RecvBuff2,10);
                                    //  mCode.encode_bch511(tempIn,codeword);
                                      mCode.encode_bch511(RecvBuff2,codeword);
                                                                          
                                      for(u64 k=0;k<64; k++)
                                      {
                                              codeword[k]&=choicesInbyte[k];
                                              tempQ[k]^=codeword[k];
                                      }
                                                                                                                                                
                                      if(memcmp(tempQ, RecvBuff, 64) != 0)
                                      {
                                          
                                              std::cout << "Consistency Check Fails at "<< i<<std::endl;
                                              exit(0);
                                      }
                              }                     

                                                 

                               

                               timer.setTimePoint("Consistency Check finished");


                   


                           /////////////////////  Evaluation ///////////////////////////////
                               
                     

                            u8* P_output= new u8[64];

                            std::vector<u64>  permute(senderSize);
                            for (u64 i = 0; i < senderSize; i++)
                            {
                                    permute[i]=i;
                            }
                            std::shuffle(permute.begin(), permute.end(), prng);  
                           

                             





                           //debug begin    



                      //     RandomOracle H(sizeof(block));
                      //      u8 hashOutput[sizeof(block)];

                           //debug end
                           
                        

                            
                            
                            

                            for (u64 hashIdx = 0; hashIdx < 3; hashIdx++)
                            {
                                   
                                                                      
                                    for (u64 i = 0; i < senderSize; i++)
	                                  {
                                        u64 addr= *(u64*)&aesHashBuffs[hashIdx][i] % mBins.mBinCount;
                         
                                        u8 HashTemp=(hashIdx+1)<<4;
                                        
                                        memcpy(tempIn, (u8*)(senderSet.data()+i) ,10);
			                                  tempIn[9]^=HashTemp;
                                        mCode.encode_bch511(tempIn,codeword);
                                        for(u64 k=0;k<64; k++)
                                        {
                                            codeword[k]&=choicesInbyte[k];
                                            codeword[k]^=RowQ[addr][k] ;
                                        }
                                             
                                        ChaChaP.ChaChaP(codeword,P_output);           
                                        memcpy(SentBuff+permute[i]*sizeof(block), P_output,sizeof(block));	
		                                }
                                  
                                 
                                     

                                      
                                       ch.asyncSend(SentBuff, sizeof(block)*senderSize);
                                      


                                     // ch.asyncSend(hashOutput,sizeof(block));

                                        //debug begin
                                     

                                     //   H.Reset();
			             //    H.Update(SentBuff,sizeof(block)*senderSize);
			             //    H.Final(hashOutput);


                                       ch.recv(bug,1);


                                                                       
                                       //debug end


                             }




                            

                           //  Deal with Stash bin

                            for (u64 stashIdx = 0; stashIdx < mNumStash; stashIdx++)
                            {
                                           for (u64 i = 0; i < senderSize; i++)
	                                   {
                               
			                                    // memcpy(tempIn, (u8*)(senderSet.data()+i) ,10);
                                             mCode.encode_bch511((u8*)(senderSet.data()+i),codeword);
                                             for(u64 k=0;k<64; k++)
                                             {
                                                     codeword[k]&=choicesInbyte[k];
                                                     codeword[k]^=RowQ[mBins.mBinCount+stashIdx][k] ;
                                             }
                                                   
                                             ChaChaP.ChaChaP(codeword,P_output);           
                                             memcpy(SentBuff+permute[i]*sizeof(block), P_output,sizeof(block));	
		                           }
                                
                                    ch.asyncSend(SentBuff, sizeof(block)*senderSize);

                            }
 

                              
                          
                              timer.setTimePoint("Receiver intersection finished");
                              std::cout<< std:: endl;
                              std::cout<<"[*****] This File is Nan Jie Hui's!!!!!![*****]"<<std:: endl;
                              std::cout<< std:: endl;
                              std::cout << timer;
                        
                       } 

         }
