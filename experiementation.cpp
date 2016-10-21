#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MsgLen = 12160;
const int NoiLen = 32;

void makeOriMsg();
string getContent(char* );
void putContent(char* , string);
int XOR(int , int );
void display(int* a, int len);
int* str2int(int* intArray, string str);
string int2str(int* intArray, int len);
string cmpR(string message, string generator);
void isError(string remainder);
string interrupte(string);

int main()
{
    char* msgFile = "message";
    char* genFile = "generator";
    char* remainderFile = "remainder";
    string message;
    string padded;
    string remainder;
    string gen = getContent("generator");
    string noiseMsg;
    const int degree = gen.size() - 1;
    const int expeNum = 1000;
    for(int i = 0; i < expeNum; i++){
        makeOriMsg();
        message = getContent(msgFile);
        padded = message.append(degree, '0');
        remainder = cmpR(message, gen);
        noiseMsg = interrupte(message);
        remainder = cmpR(noiseMsg, gen);
        putContent(remainderFile, remainder);
        isError(remainder);
        cout << "No. " << i + 1 << " experimentation is finished!" << endl;
    }
    return 0;
}

string interrupte(string oriMsg)
{
    srand(time(NULL));
    int pos = rand() % MsgLen;

    for(int i = 0; i < NoiLen; i++){
        if(oriMsg[i] == '0') oriMsg[i] = '1';
        if(oriMsg[i] == '1') oriMsg[i] = '0';
    }
    return oriMsg;
}

void isError(string remainder)
{
    for(int i = 0; i < remainder.size(); i++){
        if(remainder[i] == 1){
            cout << "The transmitted message has error!\n" << endl;
            return;
        }
    }
    cout << "The transmitted message has no error!\n" << endl;
    return;
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

string getContent(char* fileName)
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

void putContent(char* fileName, string content)
{
    ofstream output;
    output.open(fileName, ios::out);
    output << content;
    output.close();
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

void display(int* a, int len)
{
    for(int i = 0; i < len; i++){
        cout << a[i];
    }
    cout << endl;
}

string cmpR(string message, string generator)
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
