#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void FileReadAndWrite(string* FReadName,string *FWriteName) {
    ifstream FRead(*FReadName, ios::in | ios::binary);// Read File
    ofstream FWrite(*FWriteName, ios::out | ios::app);// Write File
    if (FRead.is_open()) {
        string buf;
        while (getline(FRead, buf)) {
            for (int i = 0; i < buf.length(); i++) {
                if (32 <= (int)buf[i] && (int)buf[i] <= 126) {
                    FWrite<< buf[i];
                }
            }
            FWrite<<endl;
            cout << endl;
        }
    }
    FRead.close();
    FWrite.close();
}
int main()
{
    string FileRead = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe";
    string FileWrite = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/deneme.txt";
    FileReadAndWrite(&FileRead,&FileWrite);

    return 0;
     
}

