#include "OMPsiReceiver.h"
#include "CuckooHasher.h" //new 
#include "ChaChaPermutation.h"//new
#include "bch511.h"//new 

#include <array>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <iomanip>
#include <bitset>
#include <thread>

namespace OMPSI {

	void OMPsiReceiver::run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& receiverSet){
	        
                                Timer timer;
                                u64 width=512;
                                u64 stepSize=65536;
                                u64 statSecPara=40;
                             ///////////////////// / Base OTs  /////////////////////////////
                               
                                IknpOtExtSender otExtSender;
		                      otExtSender.genBaseOts(prng, ch);
		
		                      std::vector<std::array<block, 2> > otMessages(width);

		                      otExtSender.send(otMessages, prng, ch);

                               
                                timer.setTimePoint("Receiver base OT finished");

                             /////////////////////  Initialization //////////////////////////
                                //Initialization for the parameter of cuckoo hashing
                                 CuckooHasher mBins;                                 
                                 mBins.init(receiverSize, senderSize);                                    
                                 auto mNumStash=mBins.mMaxStashSize;
                           

                                //Initialization for 3 hash h_1,h_2,h_3
                                 std::array<AES, 3> AESHASH;
                                 block commonKey;
                                 std::array<PRNG,3> commonprng;
       
                                 ChaChaPermutation  ChaChaP;



                             
                            /////////////////////  Cuckoohash ///////////////////////////  
                                   for (u64 i = 0; i < AESHASH.size(); i++)
                                   {
                                      commonprng[i].SetSeed(commonSeed[i]);
                                      commonprng[i].get((u8*)&commonKey, sizeof(block));
                                      AESHASH[i].setKey(commonKey);

                                   }


                              
                    


   
                                   std::array<std::vector<block>, 3> aesHashBuffs;
                                   
                                    aesHashBuffs[0].resize(receiverSize);
		                              aesHashBuffs[1].resize(receiverSize);
		                              aesHashBuffs[2].resize(receiverSize);


                                   for(u64 i=0; i<receiverSize;i+=stepSize)
                                   {
                                       auto currentStepSize=receiverSize-i <stepSize? receiverSize-i : stepSize ;
                                       AESHASH[0].ecbEncBlocks(receiverSet.data() + i, currentStepSize, aesHashBuffs[0].data() + i);
		                                 AESHASH[1].ecbEncBlocks(receiverSet.data() + i, currentStepSize, aesHashBuffs[1].data() + i);
		                                 AESHASH[2].ecbEncBlocks(receiverSet.data() + i, currentStepSize, aesHashBuffs[2].data() + i);
                                   }
			 
                                    mBins.insertItems(aesHashBuffs);                                          

                                 
                              

                                timer.setTimePoint("Cuckoohash finished");

                             /////////////////////  OT Extension /////////////////////
                                   
                                   mCode.load(bch511_binary, sizeof(bch511_binary));

                                   u64 numbin=mBins.mBinCount+mNumStash;
                                   u64 numbinround=((numbin+7)/8)*8;
                                   u64 numbinInbyte=numbinround/8;

                                   u64 numOtExt=numbinround+statSecPara;
                                   u64 numOtExtInbyte=numOtExt/8;

                                   u8* ColT0[width];
                                   u8* ColT1[width];
                                   std::vector<std::array<u8, 64>> RowT0(numOtExt);
                                   std::vector<std::array<u8, 64>> RowT1(numOtExt);
                                   

                                  

                                  u8* codeword= new u8[64];
                                  u8*  TempMask= new u8[64];

                                
 
                                  u8* SentBuff= new u8[64*numOtExt];
                              //    u8* SentBuff1= new u8[64*numOtExt];
      
                          
                                 




                                  
                              
                                  u8*  Input=new u8[numOtExt*10];                                
                                  u8* bug=new u8[1];
                                 
                                  u8* P_output=new u8[64];
                               

                             
                                  u8* RecvBuff= new u8[64*senderSize];                                    
                                   
                                  


                                   for(u64 i=0;i<width;i+=8)
                                   {
                                          for(u64 j=i; j<i+8;j++)
                                          {
                                               ColT0[j]=new u8[numOtExtInbyte];
                                               ColT1[j]=new u8[numOtExtInbyte];
                                               PRNG  prng0(otMessages[j][0]);
                                               prng0.get( ColT0[j], numOtExtInbyte);
                                               PRNG  prng1(otMessages[j][1]);
                                               prng1.get( ColT1[j], numOtExtInbyte);
                                          }
                                          
                                          for(u64 k=0;k<numOtExt; k++)
                                          {
                                              RowT0[k][i>>3]=0; 
                                              RowT1[k][i>>3]=0; 
                                              for (u8 j=0; j<8; j++)
                                              {
                                                   RowT0[k][i>>3]|=(u8)((bool)(ColT0[i+j][k>>3] &( 1<<(~(k &7) )) ))<<(7-j);
                                                   RowT1[k][i>>3]|=(u8)((bool)(ColT1[i+j][k>>3] &( 1<<(~(k &7) )) ))<<(7-j);    
                                              }
                                                                             
                                          }
                                   }
       

                                   
 

                                 


                                  


                              

                                  std::array<std::unordered_map<u64, std::pair<block, u64>>, 3> localMasks;
                             
                                 localMasks[0].reserve(mBins.mBinCount);  // by h1		
	   	                        localMasks[1].reserve(mBins.mBinCount);  // by h2		
		                           localMasks[2].reserve(mBins.mBinCount);  //by h3

                               


                              



                                timer.setTimePoint("ColT0 ColT1 are transformed to RowT0 RowT1");
                              
             



                                  block outputMask;

                                  auto binStart=0;
                                  auto binEnd=mBins.mBinCount;


                             
                                
                   
                                   
                                  for (u64 stepIdx=binStart; stepIdx<binEnd; stepIdx+=stepSize)
                                  {
                                          
                                             auto currentStepSize=binEnd-stepIdx<stepSize ? binEnd-stepIdx : stepSize; 
                                             auto stepEnd=stepIdx+currentStepSize;



                                          
                                             for(u64 bIdx=stepIdx, i=0; bIdx<stepEnd; ++bIdx, i++)
                                             {
                                                     auto& item=mBins.mBins[bIdx];
                                                  
                                                
                                                     if (item.isEmpty()==false)
                                                     {
                                                                               
                                                           
                                                           u8 HashTemp=(item.mHashIdx+1)<<4;
                                                          
                                                      
                                                           memcpy(Input+bIdx*10, (u8*)(receiverSet.data()+item.mIdx) ,10);
                                                            
                                                           Input[bIdx*10+9]^=HashTemp;
 
                                                           mCode.encode_bch511(Input+bIdx*10,codeword);
                                                          
                                                           
                                                           for(u64 j=0;j<64; j++)
                                                                 TempMask[j]=RowT0[bIdx][j]^RowT1[bIdx][j]^codeword[j];
                                                        
                                                            memcpy(SentBuff+i*64, TempMask,64);
                                                        
                                                        //   memcpy(SentBuff1+bIdx*64, TempMask,64);



                                                           
                                                           ChaChaP.ChaChaP(RowT0[bIdx].data(),P_output);
                                                     
                                                           // Compute P(x)^x  
                                                           for (auto k=0; k<sizeof(block); k++)
                                                           {
                                                                P_output[k]^=RowT0[bIdx][k];
                                                           }
                                                        
                                                           outputMask=*(block*) P_output; 
                                                           localMasks[item.mHashIdx].emplace(*(u64*) P_output, std::pair<block, u64>(outputMask, item.mIdx));
                                                     }
                                                     else
                                                     {
                                                          
                                                           memset(Input+bIdx*10,0,10);
                                                        
                                                           mCode.encode_bch511(Input+bIdx*10,codeword);
                                                           
                                                           for(u64 j=0;j<64; j++)
                                                                 TempMask[j]=RowT0[bIdx][j]^RowT1[bIdx][j]^codeword[j];
                                                           memcpy(SentBuff+i*64, TempMask,64);
                                                       //  memcpy(SentBuff1+bIdx*64, TempMask,64);

                                                     }   
                                                                                                      
                                             }    
  
                                             ch.asyncSend(SentBuff, 64*currentStepSize);
                                             ch.recv(bug,1);   

                                            
                                  }
                                     
                   
                                


                                

                                 auto stashStart= binEnd;   
                                 auto  stashEnd=stashStart+mNumStash;


                                 
                                  


                      

                                  u8* stashMask=new u8[mNumStash*sizeof(block)];

                                  for(u64 sIdx=stashStart, i=0; sIdx<stashEnd; sIdx++,i++ )
                                  {
                                            auto& item = mBins.mStash[i];
                                            // not empty
                                            if( item.isEmpty() == false) 
                                             {

                                                
                                                      memcpy(Input+sIdx*10, (u8*)(receiverSet.data()+item.mIdx),10);
                                                     
                                                      mCode.encode_bch511(Input+sIdx*10,codeword);
                                                      for(u64 j=0;j<64; j++)
                                                            TempMask[j]=RowT0[sIdx][j]^RowT1[sIdx][j]^codeword[j];
                                                    
                                                                                                          
                                                      ChaChaP.ChaChaP(RowT0[sIdx].data(),P_output);
                                                          // Compute P(x)^x  
                                                       for(auto k=0; k<sizeof(block); k++)
                                                            P_output[k]^=RowT0[sIdx][k];
                                                      
                                                     
                                                       memcpy(stashMask+i*sizeof(block),P_output,sizeof(block));   

                                                           
                                                       memcpy(SentBuff+i*64, TempMask,64);

                                                  //   memcpy(SentBuff1+sIdx*64, TempMask,64);

                                               
                                                         
                                             }
                                             else
                                             { 
                                                      
                                                       memset(Input+sIdx*10,0,10);
                                                    


                                                       mCode.encode_bch511(Input+sIdx*10,codeword);
                                                       for(u64 j=0;j<64; j++)
                                                                TempMask[j]=RowT0[sIdx][j]^RowT1[sIdx][j]^codeword[j];
                                                    
                                                      memcpy(SentBuff+i*64, TempMask,64);

                                                  //  memcpy(SentBuff1+sIdx*64, TempMask,64);
                                             } 
                                  }
                                  
                                  ch.asyncSend(SentBuff, 64*mNumStash);
                                  ch.recv(bug,1);
                        

                               
                               auto  checkStart= numbinround;   
                               auto  checkEnd=checkStart+statSecPara;

                              
                                 


                              
                               PRNG  prngcheck(aesHashBuffs[0][1]);
                               for(u64 cIdx=checkStart, i=0; cIdx<checkEnd; cIdx++,i++)
                               {
                                          
                                     //     prngcheck.SetSeed(aesHashBuffs[0][i]);
                                          prngcheck.get(Input+cIdx*10, 10);
                                          
                                          Input[cIdx*10+9]=0;
                                          mCode.encode_bch511(Input+cIdx*10,codeword);
                                          for(u64 j=0;j<64; j++)
                                                TempMask[j]=RowT0[cIdx][j]^RowT1[cIdx][j]^codeword[j];

                                          memcpy(SentBuff+i*64, TempMask,64);

                                     //   memcpy(SentBuff1+cIdx*64, TempMask,64);
                               }
                               ch.asyncSend(SentBuff, 64*statSecPara);
                               ch.recv(bug,1);
                              //   ch.asyncSend(SentBuff1, 64*numOtExt);

              
                                



                               timer.setTimePoint("OT Extension finished");



                  


                           /////////////////////  Consistency Check /////////////////////

                              
                         //     u8* SentBuff2= new u8[64*statSecPara];  
                              u8* tempT0= new u8[64];
                              u8* tempIn = new u8[10];
                          //    u8* tempcoderword = new u8[64];


                              u8* challenge= new u8[numbinInbyte];
                     

                               
                              for(auto i=0;i<statSecPara;i++)
                              {
                                       
                                      ch.recv(RecvBuff, sizeof(block));



                                      block tempSeed=*(block*) RecvBuff;
                                      prngcheck.SetSeed(tempSeed);
                                      prngcheck.get(challenge, numbinInbyte);
                                       


                                      memset(tempT0,0, 64);
                                      memset(tempIn,0, 10);
                                      for (u64 stepIdx=0; stepIdx<numbin; stepIdx+=8)
                                      {
                                                auto currentStepSize=numbin-stepIdx<8 ? numbin-stepIdx :8; 
                                                auto stepEnd=stepIdx+currentStepSize;

                                                for(auto bIdx=stepIdx; bIdx<stepEnd; bIdx++)
                                                {
                                                            if((bool)(challenge[bIdx>>3] & (1<<~(bIdx & 7)) ) )
                                                            {
                                                                     for(auto k=0;k<64;k++)
                                                                          tempT0[k]^=RowT0[bIdx][k];
                                                                     for(auto k=0;k<10;k++)
                                                                          tempIn[k]^=Input[bIdx*10+k];
                                                                     
                                                            }       
                                                }
                                       }           
                                                             
                                       for(auto k=0;k<64;k++)
                                                tempT0[k]^=RowT0[numbinround+i][k];
                                       for(auto k=0;k<10;k++)
                                                tempIn[k]^=Input[(numbinround+i)*10+k];
                              
                                       ch.asyncSend(tempT0, 64);
                                       ch.asyncSend(tempIn, 10);
                              }
                              
                              


                             timer.setTimePoint("Consistency Check finished");



                             // debug begin
                          //   std::cout<< std::endl;
                          //   std:: cout<< "The Consistency Check is finished"<< std:: endl;                                   
                          //   std::cout<< std::endl;
                            //debug end


                           /////////////////////  Evaluation ///////////////////////////////
                               
                              u64 psi=0;
                              

                              //debug begin
                           //   u8* Empty=new u8[2];
                          //    memset(Empty,0,2);
                              
                           //   u8* SentBufftest[3];
                              
                          //    RandomOracle H(sizeof(block));
                          //    u8 hashOutput[sizeof(block)];
                         
                         
                              // debug end

                             
                          
                             for (u64 hashIdx = 0; hashIdx < 3; hashIdx++)
                             {
                                   ch.recv(RecvBuff, sizeof(block)*senderSize);
                                   



                                  //debug begin  
                                   
                                 //  ch.recv(TempRecvBuff,sizeof(block));


                                   ch.asyncSend(bug,1); 
                                   
                            /*      H.Reset();
			                     H.Update(RecvBuff,sizeof(block)*senderSize);
			                     H.Final(hashOutput);

                                    std::cout<<"the hash value of the"<<hashIdx+1<<"-th sendbuffer is"<< std:: endl; 
                                   std::cout<< std:: endl;
                                     for(auto i=0;i<sizeof(block);i++)
                                           std::cout<<hashOutput[i]<<" ";

                                   std::cout<< std:: endl;

                                   if(memcmp(TempRecvBuff,hashOutput,sizeof(block))==0)
                                          std::cout<<"The check of received data is correct"<<std:: endl;
                                  
                             */      //debug  end

                                 
                                   auto theirMasks=RecvBuff;
                                   for (u64 i = 0; i < senderSize; i++,theirMasks+= sizeof(block))  
				                       {
					                          auto& msk = *(u64*)(theirMasks);
                                           
					                         // check 64 first bits
					                          auto match = localMasks[hashIdx].find(msk);
 
					                         //if match, check for whole bits
                                         if (match==localMasks[hashIdx].end())
                                         {
                                             
                                             continue;
                                         }
                                                     
					                         
					                          
						                       if (memcmp(theirMasks, &(match->second.first), sizeof(block)) == 0) // check full mask
						                       {
							                           mIntersection.push_back(match->second.second);
							                           psi++;
                                             
						                       }
					                          
					 
                                         
				        
                                   }
                              
                                  
                              }



                               

                      


                           //  Deal with Stash bin


                            for (u64 stashIdx = 0; stashIdx < mNumStash; stashIdx++)
                            {
                                    ch.recv(RecvBuff, sizeof(block)*senderSize);
                                 
                                    if (mBins.mStash[stashIdx].isEmpty()== false)
			                     {
					
				                       auto theirMasks =RecvBuff;
				                       for (u64 i = 0; i < senderSize; i++)
				                       {
					                       //check stash
					                       if (memcmp(theirMasks, stashMask+stashIdx*sizeof(block), sizeof(block)) == 0) 
					                       {
						                     mIntersection.push_back(mBins.mStash[stashIdx].mIdx);
						                     psi++;
					                       }
					
					                      theirMasks+= sizeof(block);
				                       }				
			                     }
                            }
 



                           


                             if(psi==100)
                             {
                                  std:: cout<< "Receiver intersection computed -correct!\n";
                             }
                             

                           

                              timer.setTimePoint("Receiver intersection finished");

                        

                             
                              std::cout << timer;
                             //////////////// Output communication /////////////////

                             
                              u64 ByteRivseFactor=1;

                              

                              if (senderSize <= (1 << 26))
			                        ByteRivseFactor=4;

		                        if (senderSize <= (1 << 22))
			                        ByteRivseFactor=5;

                              if (senderSize <= (1 << 18))
			                        ByteRivseFactor=6;
                            
                             

                             

                             u64 dummyrecvData=ByteRivseFactor*(3+mNumStash)*senderSize;  
                             
                            
	
		                       u64 sentData = ch.getTotalDataSent();
		                       u64 recvData = ch.getTotalDataRecv()-dummyrecvData;
		                       u64 totalData = sentData + recvData;

                             
                           

		                       std::cout << "Receiver sent communication: " << sentData / std::pow(2.0, 20) << " MB\n";
		                       std::cout << "Receiver received communication: " << recvData / std::pow(2.0, 20) << " MB\n";
		                       std::cout << "Receiver total communication: " << totalData / std::pow(2.0, 20) << " MB\n";

                          } 

              }
