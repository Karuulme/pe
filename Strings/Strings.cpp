#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;
string HexBase(char str) {
    int TenBase = (int)str;
    string Basees[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F" };
    int bolum = (int)(TenBase / 16);
    string kalan = Basees[TenBase % 16];
    string donusDegeri = to_string(bolum) + kalan;
    return donusDegeri;
}
int BinaryCharacter(char* arr, char Binary) {

    for (int i = 0; i < 256; i++) {
        if (arr[i] == Binary)return i;
    }
    return 32;
}
int main()
{
    char Characteres[256];
    for (int i = 0; i < 256; i++) {
        Characteres[i] = (char)i;
    }
    //setlocale(LC_ALL, "Turkish");
    ifstream FileRead("C:/Users/SanalMak/Desktop/malware kurs içeriği/Örnek Zararlılar/virusler/Practical Malware Analysis Labs/BinaryCollection/Chapter_10L/Lab10-01.exe", ios::binary | ios::in);
    ofstream FileWeite("C:/Users/SanalMak/Desktop/malware kurs içeriği/Örnek Zararlılar/virusler/Practical Malware Analysis Labs/BinaryCollection/Chapter_10L/Lab10-01.txt");
    if (FileRead.is_open()) {
        string buf = "";
        while (getline(FileRead, buf))
        {
            string bufBinary = "";
            char Line[8];
            for (int i = 0, j = 0; i < buf.length(); i++, j++) {
                if (31 < (int)buf[i] && (int)buf[i] != 127) {
                    bufBinary += " " + HexBase((Characteres, (char)buf[i])) + " ";
                    Line[j] = buf[i];
                }
                else {
                    bufBinary += "_";
                    Line[j] = '.';
                }
                if (j == 7) {
                    FileWeite << bufBinary << " ---------- ";
                    cout << bufBinary << " ---------- ";
                    for (int j = 0; j < 8; j++) {
                        FileWeite << Line[j];
                        cout << Line[j];
                    }
                    j = 0;
                    FileWeite << endl;
                    cout << endl;
                    bufBinary = "";
                }

            }
        }
    }
}