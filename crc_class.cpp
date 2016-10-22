#ifndef CRC_CLASS_CPP
#define CRC_CLASS_CPP
#include "crc_class.h"

string crc::interrupte(string oriMsg)
{
    string str = oriMsg;
    srand(time(NULL));
    int pos = rand() % oriMsgLen;
    for(int i = 0; i < noiseLen; i++){
        if(str[i] == '0'){
            str[i] = '1';
            continue;
        }
        if(str[i] == '1'){
            str[i] = '0';
            continue;
        }
    }
    return str;
}

void crc::isError(string remainder)
{
    if(transmittedMsg == interruptedMsg){
        numRight++;
        return;
    }
    else{
        numError++;
        return;
    }
//    for(int i = 0; i < remainder.size(); i++){
//        if(remainder[i] == '1'){
//            //cout << "The transmitted message has error!\n" << endl;
//            numError++;
//            return;
//        }
//    }
//    //cout << "The transmitted message has no error!\n" << endl;
//    numRight++;
}

string crc::getTransmittedMsg()
{
    return oriMsg + check;
}

string crc::paddingOriMsg(string oriMsg)
{
	return oriMsg.append(degree, '0');
}

string crc::getContentFromFile(const char* fileName)
{
    string content;
    string line;

    ifstream input;
    input.open(fileName, ios::in);
    if(input.is_open()){
        while(getline(input, line)){
            content += line;
        }
    }
    input.close();
    return content;
}

void crc::putContentToFile(const char* fileName, string content)
{
    ofstream output;
    output.open(fileName, ios::out);
    output << content;
    output.close();
}

void crc::makeOriMsg()
{
	int* randInt = (int*)malloc(sizeof(int) * oriMsgLen);
    srand(time(NULL));
    for(int i = 0; i < oriMsgLen; i++){
       randInt[i] = rand() % 2;
    }
    string str = int2str(randInt, oriMsgLen);
    putContentToFile(oriMsgFile, str);
}

int crc::XOR(int a, int b)
{
    if(a == b) return 0;
    return 1;
}

int* crc::str2int(int* intArray, string str)
{
    intArray = (int*)malloc(str.size() * sizeof(int));
    for(int i = 0; i < str.size(); i++){
        intArray[i] = str[i] - '0';
    }
    return intArray;
}

string crc::int2str(int* intArray, int len)
{
    string str;
    for(int i = 0; i < len; i++){
        str += intArray[i] + '0';
    }
    return str;
}

string crc::cmpCheck(string message, string generator)
{
    int i;
    int pos;
    int degree = generator.size() - 1;
    message.append(degree, '0');

    int *msg;
    int *gen;
    gen = str2int(gen, generator);
    msg = str2int(msg, message);

    for(pos = 0; pos < message.size() - 2 * (degree - 1); pos++){
        if(msg[pos] != 1) continue;
        for(i = 0; i < generator.size(); i++){
            msg[pos + i] = XOR(msg[pos + i], gen[i]);
        }

    }

    string remainder = int2str(msg, message.size());
    remainder = remainder.substr(message.size() - degree, degree);
    return remainder;
}
#endif
