#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;



template<class T>
class List
{
public:
    int Remove(unsigned int index) {
        try {
            _Length--;
            T** NewStartPoint = StartPoint;
            StartPoint = new T * [_Length];
            for (int i = 0, j = 0; i < _Length + 1; i++)
            {
                if (index != i) {
                    StartPoint[j] = NewStartPoint[i];
                    j++;
                }

            }
            delete(NewStartPoint);
            return 1;
        }
        catch (int myNum) {
            return 0;
        }
    }
    int GetIndex(unsigned int i) {
        return (i >= _Length) ? 0 : *StartPoint[i];
    }
    void Read() {
        for (int i = 0; i < _Length; i++) {
            cout << *StartPoint[i] << endl;
        }
    }
    int Length() {
        return _Length;
    }
    void Add(T value)
    {
        MemoryPointCreate(&value);
    }
    int* GetAll() {
        int GetAllList[_Length];
        for (int i = 0; i < _Length; i++) {
            GetAllList[i] = *StartPoint[i];
        }
        return GetAllList;
    }
    ~List() {
        delete _Length;
        delete StartPoint;
    }
private:
    int _Length = 0;
    T** StartPoint;

    void MemoryPointCreate(T* value) {
        T* NPoint = new T[1];
        *NPoint = *value;
        MemoryExpansion(NPoint);
    }
    void MemoryExpansion(T* NValue) {
        if (_Length > 0) {
            _Length++;
            T** NewStartPoint = StartPoint;
            StartPoint = new T * [_Length];
            for (int i = 0; i < _Length - 1; i++)
            {
                StartPoint[i] = NewStartPoint[i];
            }
            StartPoint[_Length - 1] = NValue;
            delete(NewStartPoint);
        }
        else {
            _Length++;
            StartPoint = new T * [_Length];
            StartPoint[0] = NValue;
        }
    }
};

int FileAnalysis(string* AddressRead, List<string>* FileLines) {
    if (!(*AddressRead).empty()) {
        ifstream FRead(*AddressRead, ios::in | ios::binary);// Read File
        string buf;

        if (FRead) {
            while (getline(FRead, buf)) {
                int LineCont = 0;
                string Sentence = "";
                for (int i = 0; i < buf.length(); i++) {
                    if (32 <= (int)buf[i] && (int)buf[i] <= 126 || buf[i] == ' ' || buf[i] == '*') {
                        Sentence += buf[i];
                        LineCont = 1;
                    }
                    else {
                        if (LineCont == 1)
                        {
                            LineCont = 0;
                            FileLines->Add(Sentence);
                            Sentence = "";
                        }
                    }
                }
            }
        }
        FRead.close();
        return 1;
    }
    return 0;
}
int main()
{
    string FileAddressesRead;
    // string FileAddressesWrite;
    List<string> FileLines;
    List<string> FileExtension;
    List<string> WindowsFunctionsAnddllFiles;
    List<string> Links;

    FileAddressesRead = L'C:/Users/SanalMak/Desktop/Analiz edilenler/analiz1/71257279-042b-371d-a1d3-fbf8d2fadffa.exe';
    //  FileAddressesWrite = L'C: / Users / SanalMak / Desktop / Analiz edilenler / analiz1 / deneme.txt';

    FileAnalysis(&FileAddressesRead, &FileLines);

}
