#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class crc{
public:
	string oriMsg;
	string generator;
	string paddedMsg;
	string check;
	string remainder;
	string transmittedMsg;
	string interruptedMsg;

	int oriMsgLen;
	int generatorLen;
	int degree;
	int noiseLen;
	int numError = 0;
	int numRight = 0;
	int numInterrupt = 0;
	double dtcRatio;

	const char* oriMsgFile = "originalMessage";
	const char* generatorFile = "generator";
	const char* checkFile = "check";
	const char* transmittedMsgFile = "transmittedMseeage";
	const char* remainderFile = "remainder";

	string getContentFromFile(const char*);
	void putContentToFile(const char*, string);
	void makeOriMsg();
	int XOR(int, int);
	int* str2int(int*, string);
	string int2str(int* intArray, int len);
	string cmpCheck(string oriMsg, string generator);
	void isError(string remainder);
	string interrupte(string);
	string paddingOriMsg(string oriMsg);
    string getTransmittedMsg();
};
