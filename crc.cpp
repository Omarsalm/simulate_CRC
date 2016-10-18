#include <cstdlib>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

string getContent(char* );
void putContent(char* , string);
string getM();
int XOR(int , int );
void display(int* a, int len);
string cmpR(string message, string generator);


int main()
{
    string generator = getContent("generator");
    cout <<"generator: " <<  generator << endl;

    string message = getContent("message");
    cout << "message: " << message << endl;

    string padded = message.append(generator.size() - 1, '0');
    cout << "padded message: " << padded << endl;

    string remainder = cmpR(message, generator);
    cout << "remainder: " << remainder << endl;
    putContent("remainder", remainder);

    string processed = padded.replace(padded.size() - (generator.size() - 1), generator.size() - 1, remainder);
    cout << "processed message: " << processed << endl;
    putContent("processed", processed);
    processed = getContent("processed");
    remainder = cmpR(processed, generator);
    cout << "the remainder of processed message: " << remainder << endl;
    return 0;
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


    for(pos = 0; pos < message.size() - 2 * (generator.size() - 2); pos++){
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
    remainder = remainder.substr(message.size() - (generator.size() - 1), generator.size() - 1);
    //cout << "remainder: " << remainder << endl;
    return remainder;
}
