#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "crc_class.h"

using namespace std;

const int FrameLen = 12160;//the length of the message you want to send
const int NoiseLen = 64;//the length of noise you want to add
const int expeNum = 1000;//the number of experimentation you want to have

int main()
{
    crc ins;//an instance of CRC
    ins.oriMsgLen = FrameLen;
    ins.noiseLen = NoiseLen;

    ins.generator = ins.getContentFromFile(ins.generatorFile);//get the generator
    ins.degree = ins.generator.size() - 1;

    for(int i = 0; i < expeNum; i++){
        ins.makeOriMsg();//generate the original message randomly
        ins.oriMsg = ins.getContentFromFile(ins.oriMsgFile);
        ins.paddedMsg = ins.paddingOriMsg(ins.oriMsg);//padding '0's
        ins.check = ins.cmpCheck(ins.oriMsg, ins.generator);//compute the check
        ins.transmittedMsg = ins.getTransmittedMsg();//the message sent actually
        ins.interruptedMsg = ins.interrupte(ins.transmittedMsg);//add noise
        if(ins.interruptedMsg == ins.transmittedMsg){//find how many noise added
            cout << "equal!" << endl;
        }else{
            ins.numInterrupt++;
        }
        ins.remainder = ins.cmpCheck(ins.interruptedMsg, ins.generator);//compute the remainder of the transmitted messsage
        ins.isError(ins.remainder);//receiver determine if the message has error
    }
    //output the result of experimentation
    cout << ins.numInterrupt << endl;
    cout << "The detectation ratio is: " << ins.numError/(double)ins.numInterrupt << endl;
    cout << ins.numError << " transmitted message have error.\n" << endl;
    return 0;
}
