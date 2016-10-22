#include <cstdlib>
#include <iostream>
#include <fstream>
#include "crc_class.h"

using namespace std;

void display(int* a, int len);

int main()
{
    crc ins;

    ins.generator = ins.getContentFromFile(ins.generatorFile);
    cout <<"generator: " <<  ins.generator << endl;
    ins.degree = ins.generator.size() - 1;

    ins.oriMsg = ins.getContentFromFile(ins.oriMsgFile);
    cout << "message: " << ins.oriMsg << endl;

    ins.paddedMsg = ins.paddingOriMsg(ins.oriMsg);
    cout << "padded message: " << ins.paddedMsg << endl;

    ins.check = ins.cmpCheck(ins.paddedMsg, ins.generator);
    cout << "check: " << ins.check << endl;
    ins.putContentToFile(ins.checkFile, ins.check);

    ins.transmittedMsg = ins.getTransmittedMsg();
    cout << "Transmitted message: " << ins.transmittedMsg << endl;
    ins.putContentToFile(ins.transmittedMsgFile, ins.transmittedMsg);

    ins.remainder = ins.cmpCheck(ins.transmittedMsg, ins.generator);
    cout << "the remainder of processed message: " << ins.remainder << endl;
    ins.isError(ins.remainder);
    return 0;
}
