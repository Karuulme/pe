#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

string FileAddresses[2];// 0. Index Read File , 1. Index Read File

DWORD WINAPI FileThread(LPVOID lpParam) {
	if (!FileAddresses[0].empty() && !FileAddresses[1].empty()) {
		ifstream FRead(FileAddresses[0], ios::in | ios::binary);// Read File
		ofstream FWrite(FileAddresses[1], ios::out | ios::app);// Write File
        string buf;
       // FRead.read(buf, sizeof(buf));
        if (FRead && FWrite) {
            while (getline(FRead,buf)) {
                int LineCont = 0;
                string Sentence = "";
                for (int i = 0; i <buf.length(); i++) {
                    if (32 <= (int)buf[i] && (int)buf[i] <= 126) {
                        Sentence += buf[i];
                        LineCont = 1;
                    }
                    else {
                        if (LineCont == 1)
                        {
                            LineCont = 0;
                            if (Sentence.length() > 1)
                            {
                                FWrite << Sentence;
                                FWrite << endl;

                            }
                            Sentence = "";
                        }
                    }
                }
            }
        }
		FRead.close();
		FWrite.close();
	}
	return 0;
}
int main()
{
	HANDLE hThread;
	DWORD ThreadID;

    FileAddresses[0] = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe";
    FileAddresses[1] = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/deneme.txt";

	hThread = CreateThread(NULL, 0, FileThread, (void*)&FileAddresses, 0, &ThreadID);
	if (hThread) {
		cout << " Başarıyla oluşturuldu ";
		cout << endl;
		cout << ThreadID;
	}
	CloseHandle(hThread);
}

