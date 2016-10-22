#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "crc_class.h"

using namespace std;

const int FrameLen = 12160;
const int NoiseLen = 16;
const int expeNum = 1000;

int main()
{
    crc ins;//an instance of CRC
    ins.oriMsgLen = FrameLen;
    ins.noiseLen = NoiseLen;

    ins.generator = ins.getContentFromFile(ins.generatorFile);
    ins.degree = ins.generator.size() - 1;

    for(int i = 0; i < expeNum; i++){
        ins.makeOriMsg();
        ins.oriMsg = ins.getContentFromFile(ins.oriMsgFile);
        ins.paddedMsg = ins.paddingOriMsg(ins.oriMsg);
        ins.check = ins.cmpCheck(ins.oriMsg, ins.generator);
        ins.transmittedMsg = ins.getTransmittedMsg();
        ins.interruptedMsg = ins.interrupte(ins.transmittedMsg);
        if(ins.interruptedMsg == ins.transmittedMsg){
            cout << "equal!" << endl;
        }else{
            ins.numInterrupt++;
        }
        ins.remainder = ins.cmpCheck(ins.interruptedMsg, ins.generator);
        ins.isError(ins.remainder);
        //cout << "No. " << i + 1 << " experimentation is finished!" << endl;
    }
    cout << ins.numInterrupt << endl;
    cout << "The detectation ratio is: " << ins.numError/(double)ins.numInterrupt << endl;
    cout << ins.numError << " transmitted message have error.\n" << endl;
    return 0;
}
