#include "OMPSI/include/Defines.h"
#include "OMPSI/include/utils.h"
#include "OMPSI/include/OMPsiSender.h"
#include "OMPSI/include/OMPsiReceiver.h"


#include "OMPSI/include/CuckooHasher.h" 
#include "OMPSI/include/ChaChaPermutation.h"
#include "OMPSI/include/bch511.h"


#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Network/Endpoint.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Common/CLP.h>
#include <cryptoTools/Common/Log.h>

#include <vector>
#include <cstdlib>

using namespace std;
using namespace OMPSI;

//  block* commonSeed= new block[3];
//PRNG prngcommon1(oc::toBlock(123456));
//PRNG prngcommon2(oc::toBlock(123456));
const block commonSeed1=oc::toBlock(123451);
const block commonSeed2=oc::toBlock(123452);
const block commonSeed3=oc::toBlock(123453);


u64 senderSize;
u64 receiverSize;

string ip;

u64 Counter=10000;


void runSender() {
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

    vector<block> commonSeed(3);
    commonSeed[0]=commonSeed1;
    commonSeed[1]=commonSeed2;
	commonSeed[2]=commonSeed3;


        u8* tempsenderSet=new u8[16];   
	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));
	for(auto i = 0; i < senderSize; ++i)
        {
             prng.get(tempsenderSet,16);
             memset(tempsenderSet+9,0,7);
	     senderSet[i]=*(block*) tempsenderSet;
                                 
	}        
                
                   
	OMPsiSender psiSender;
	psiSender.run(prng, ch, senderSize, receiverSize,commonSeed, senderSet);
	//run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& senderSet) 
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiver() {
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

    u8* tempreceiverSet=new u8[16];


    
    vector<block> commonSeed(3);
    commonSeed[0]=commonSeed1;
    commonSeed[1]=commonSeed2;
	commonSeed[2]=commonSeed3;

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(123));
	
	
        for (auto i = 0; i < 100; ++i)
        {
             prng.get(tempreceiverSet,16);
             memset(tempreceiverSet+9,0,7);
	     receiverSet[i]=*(block*) tempreceiverSet;
                                 
	}     

	PRNG prng2(oc::toBlock(456));
	
	
        for (auto i =100; i < receiverSize; ++i)
        {
             prng2.get(tempreceiverSet,16);
             memset(tempreceiverSet+9,0,7);
	     receiverSet[i]=*(block*) tempreceiverSet;
                                 
	}        
          
	OMPsiReceiver psiReceiver;
	psiReceiver.run(prng, ch, senderSize, receiverSize,commonSeed,receiverSet);
	//run(PRNG& prng, Channel& ch, const u64& senderSize, const u64& receiverSize, std::vector<block>& commonSeed, std::vector<block>& receiverSet);
	ch.close();
	ep.stop();
	ios.stop();
}



void experiment(){

	Timer timer;

	LinearCode mCode;
	ChaChaPermutation  ChaChaP;

	mCode.load(bch511_binary, sizeof(bch511_binary));
    
	u8* codeword= new u8[64];
	u8* P_output=new u8[64];

	u8* X=new u8[sizeof(block)];

    memset(X,0,sizeof(block));

    for(auto i=0;i<10;i++)
        X[i]=(u8)(i+1);


    u8* choicesInbyte=new u8[64];
                          
    for(auto i=0;i<64;i++)
        choicesInbyte[i]=(u8)(i+1);


    std::vector<block> choicesInBlock(4);
                      
                      
    for(auto i=0;i<4;i++)
        choicesInBlock[i]=*(block*) (choicesInbyte+i*sizeof(block));


    std::vector<block> RowQInBlock(4);
                      
                      

    u8* RowQInByte=new u8[64];
    memcpy(RowQInByte,choicesInbyte,64);    
                       

    for(auto i=0;i<4;i++)
        RowQInBlock[i]=*(block*) (RowQInByte+i*sizeof(block));
                      
                       
                           

    std::vector<block> InputE(4);

    for(auto i=0;i<4;i++)
        memcpy( (u8*)(InputE.data()+i),X,sizeof(block));
                           

    std::cout<<"The repetition time for our experiment is: "<<Counter<< std:: endl;   

	std::cout<< std:: endl;                             

    RandomOracle H(sizeof(block));
    u8 hashOutput[sizeof(block)];
                           
    AES PseudoCode;
    PseudoCode.setKey(oc::toBlock(123));                         
    std::vector<block> PseudoCodeWord(4);
 


	std::cout<<"[******** Test for the Instantiation of Code+Function *********]"<< std:: endl;



	timer.setTimePoint("Set Time Conuter");
                           
    timer.setTimePoint("The Begin Time ===> Pseudorandom Code + Hash function");

    for(auto k=0;k<Counter;k++)
    {

        PseudoCode.ecbEncBlocks(InputE.data(), 4, PseudoCodeWord.data());
                              
        for(auto i=0;i<4;i++)
            RowQInBlock[i]^=(PseudoCodeWord[i]&choicesInBlock[i]);


            H.Reset();
			H.Update(RowQInBlock.data(),sizeof(block)*4);
			H.Final(hashOutput);                          

    }

                           
    timer.setTimePoint("The End Time ===> Pseudorandom Code + Hash function");
                           

     
                           
    timer.setTimePoint("The Begin Time ===> Linear Code  + robustness function");

    for(auto k=0;k<Counter;k++)
    {
                               
                              
        mCode.encode_bch511(X,codeword);
        for(auto i=0;i<64;i++)
        {
            codeword[i]&=choicesInbyte[i];
            codeword[i]^=RowQInByte[i] ;
        }
                                
                                                                                                                                          
        ChaChaP.ChaChaP(codeword,P_output);

        for(auto i=0;i<sizeof(block);i++)
            P_output[i]^=codeword[i];

    }

                           
    timer.setTimePoint("The End Time ===> Linear Code  + robustness function");
                           
     std::cout << timer;

	 std::cout<<std:: endl; 

    std::cout<<"[******** Test for the Instantiation of Function only *********]"<< std:: endl;                           
                           
  
  
  
    Timer timer2;
  
  
    timer2.setTimePoint("Set Time Conuter");
	
	
	timer2.setTimePoint("The Begin Time ===> Hash function");

    for(auto k=0;k<Counter;k++)
    {

        H.Reset();
		H.Update(RowQInBlock.data(),sizeof(block)*4);
		H.Final(hashOutput);                          

    }

                           
    timer2.setTimePoint("The End Time ===> Hash function");
                           

     
                           
    timer2.setTimePoint("The Begin Time ===> robustness function");

    for(auto k=0;k<Counter;k++)
    {
                               
                                                                                                                                                                        
        ChaChaP.ChaChaP(RowQInByte,P_output);

        for(auto i=0;i<sizeof(block);i++)
            P_output[i]^=RowQInByte[i];

    }

                           
    timer2.setTimePoint("The End Time ===> robustness function");
                           

    std::cout << timer2;

	
}







int main(int argc, char** argv) {
	
	oc::CLP cmd;
	cmd.parse(argc, argv);
	
	cmd.setDefault("ss", 20);
	senderSize = 1 << cmd.get<u64>("ss");
	
	cmd.setDefault("rs", 20);
	receiverSize = 1 << cmd.get<u64>("rs");
	
	
	cmd.setDefault("ip", "localhost");
	ip = cmd.get<string>("ip");
	

	if((bool ) cmd.isSet("exp"))
	{
		Counter=cmd.get<u64>("exp");
		experiment();
		exit(0);
	}
	
	
	bool noneSet = !cmd.isSet("r");
	if (noneSet) {
		std::cout
		<< "=====================================================\n"
		<< "||  One-Sided Malicious Private Set Intersection   ||\n"
		<< "=====================================================\n"
		<< "\n"
		<< "The commands to use this program are in the following:\n"
		<< "\n"
		<< "=====================================================\n"
		<< "1. Run the protocl:\n "
		<< "\n"
		<< "Experimenet flag:\n"
		<< " -r 0    to run a sender.\n"
		<< " -r 1    to run a receiver.\n"
		<< "\n"
		<< "Parameters:\n"
		<< " -ss     log(#elements) on sender side.\n"
		<< " -rs     log(#elements) on receiver side.\n"
		<< " -ip     ip address (and port).\n"
        << "\n"
		<< "=====================================================\n"  
		<< "2. The performance  of our adaptively CCRF: \n"
		<< "\n"
		<< "Parameters:\n"
		<< " -exp  the repetition time on calling functions (e.g. -exp 1000)\n"
		<< "\n";

	} else {
		if (cmd.get<u64>("r") == 0) {
			runSender();
		} else if (cmd.get<u64>("r") == 1) {
			runReceiver();
		}
	}
	
	
	
	return 0;
}
