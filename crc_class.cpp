#ifdef CRC_CLASS_CPP
#define CRC_CLASS_CPP

#include <iostream>
#include <stdlib>
#include <fstream>
#include <string>

using namespace std;

class crc{
	string oriMsg;
	string generator;
	string paddedMsg;	
	string check;
	string remainder;
	string transmittedMsg;

	int oriMsgLen;
	int generatorLen;
	int degree;
	int noiseLen;

	const char* oriMsgFile = "originalMessage";
	const char* generatorFile = "generator";
	const char* checkFile = "check";
	const char* transmittedMsgFile = "transmittedMseeage";
	const char* remainderFile = "remainder";

	string getContentFromFile(char*);
	void putContentToFile(char*);
	void makeOriMsg();
	int XOR(int, int);
	int* str2int(int*, string);
	string int2str(int* intArray, int len);
	string cmpCheck(string oriMsg, string generator);
	void isError(string remainder);
	string interrupte(string);
}

string getContentFromFile(char* fileName)
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

void putContentToFile(char* fileName, string content)
{
    ofstream output;
    output.open(fileName, ios::out);
    output << content;
    output.close();
}

void makeOriMsg()
{
	int* randInt = (int*)malloc(sizeof(int) * MsgLen);
    srand(time(NULL));
    for(int i = 0; i < MsgLen; i++){
       randInt[i] = rand() % 2;
    }
    string OriMsg = int2str(randInt, MsgLen);
    putContent("message", OriMsg);
}

int XOR(int a, int b)
{
    if(a == b) return 0;
    return 1;
} 

int* str2int(int* intArray, string str)
{
    intArray = (int*)malloc(str.size() * sizeof(int));
    for(int i = 0; i < str.size(); i++){
        intArray[i] = str[i] - '0';
    }
    return intArray;
}

string int2str(int* intArray, int len)
{
    string str;
    for(int i = 0; i < len; i++){
        str += intArray[i] + '0';
    }
    return str;
}

string cmpCheck(string message, string generator)
{
    int i;
    int pos;
    int degree = generator.size() - 1;
    message.append(degree, '0');
    //cout << "converted message: " << message << endl;

    int *msg;
    int *gen;
    gen = str2int(gen, generator);
    msg = str2int(msg, message);

    for(pos = 0; pos < message.size() - 2 * (degree - 1); pos++){
        //cout << "position: " << pos << endl;
        if(msg[pos] != 1) continue;
        for(i = 0; i < generator.size(); i++){
            msg[pos + i] = XOR(msg[pos + i], gen[i]);
        }
        //display(msg, message.size());
        //cout << "processed!" << endl;
    }

    string remainder = int2str(msg, message.size());
    //cout << remainder << endl;
    remainder = remainder.substr(message.size() - degree, degree);
    //cout << "remainder: " << remainder << endl;
    return remainder;
}
#endif
