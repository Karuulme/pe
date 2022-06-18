#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

void FileReadAndWrite(string* FReadName, string* FWriteName) {
    ifstream FRead(*FReadName, ios::in | ios::binary);// Read File
    ofstream FWrite(*FWriteName, ios::out | ios::app);// Write File
    char buf[50];
    FRead.read(buf, sizeof(buf));
    if (FRead) {
        while (FRead) {
            if (FRead.read(buf, sizeof(buf)))
            {
                int LineCont = 0, Linelengh = 0;
                string Sentence = "";
                for (int i = 0; i < sizeof(buf); i++) {
                    if (32 <= (int)buf[i] && (int)buf[i] <= 126) {
                        Sentence += buf[i];
                        Linelengh++;
                        LineCont = 1;
                    }
                    else {
                        if (LineCont == 1)
                        {
                            LineCont = 0;
                            if (Sentence.length() > 1)
                            {
                                cout << Sentence;
                                FWrite << Sentence;
                                FWrite << endl;
                                cout << endl;

                            }
                            Linelengh = 0;
                            Sentence = "";
                        }
                    }
                }

            }
        }
    }
    FRead.close();
    FWrite.close();
}
int main()
{
    string fileRead = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe";
    string FileWrite = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/deneme.txt";

FileReadAndWrite(&fileRead, &FileWrite);

return 0;
}