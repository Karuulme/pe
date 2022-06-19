#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
string ReadAddress;
string WriteAddress;
DWORD WINAPI FileThread(LPVOID lpParam) {
	if (!ReadAddress.empty() && !WriteAddress.empty()) {
		ifstream FRead(ReadAddress, ios::in | ios::binary);// Read File
		ofstream FWrite(WriteAddress, ios::out | ios::app);// Write File
		char buf[50];
		FRead.read(buf, sizeof(buf));
		if (FRead && FWrite) {
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
		return 1;
		FRead.close();
		FWrite.close();
	}
	return 0;
}
int main()
{
	HANDLE hThread;
	DWORD ThreadID;
	ReadAddress = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe";
	WriteAddress = "C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/deneme.txt";
	hThread = CreateThread(NULL, 0, FileThread, NULL, 0, &ThreadID);
	if (hThread) {
		cout << " Başarıyla oluşturuldu ";
		cout << endl;
		cout << ThreadID;
	}
	CloseHandle(hThread);
}
