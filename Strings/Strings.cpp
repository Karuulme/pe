#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

void FileReadAndWrite(ifstream* FRead, ofstream* FWrite) {
    char buf[50];
    FRead->read(buf, sizeof(buf));
    if (FRead) {
        while (FRead) {
            if (FRead->read(buf, sizeof(buf)))
            {
                int LineCont = 0, Linelengh = 0;
                string Sentence="";
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
                            if (Sentence.length() > 2)
                            {
                                cout << Sentence;
                                cout << endl;

                            }
                            Linelengh = 0;
                            Sentence = "";
                            //  FWrite->write("\0", sizeof(buf[i]));
                            
                        }
                    }
                }
 
            }
        }
    }
}
int main()
{
    ifstream fileRead("C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe", ios::in | ios::binary);// Okunacak Dosya
    ofstream FileWrite("C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/deneme.txt"); // Yazılacak dosya

    FileReadAndWrite(&fileRead, &FileWrite);

    fileRead.close();
    FileWrite.close();
    return 0;
}

