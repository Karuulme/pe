#include <Windows.h>
#include <stdio.h>
#include <iostream>
//#include <errhandlingapi.h>
using namespace std;

int main()
{
    IMAGE_NT_HEADERS    ntHeaders;
    //            ->
    //            DWORD                   Signature;
    //            IMAGE_FILE_HEADER       FileHeader;
    //            IMAGE_OPTIONAL_HEADER32 OptionalHeader;
    IMAGE_OPTIONAL_HEADER   optinalHeader;
    //                 ->
    //                 WORD                 Magic;
    //                 BYTE                 MajorLinkerVersion;
    //                 BYTE                 MinorLinkerVersion;
    //                 DWORD                SizeOfCode;
    //                 DWORD                SizeOfInitializedData;
    //                 DWORD                SizeOfUninitializedData;
    //                 DWORD                AddressOfEntryPoint;
    //                 DWORD                BaseOfCode;
    //                 DWORD                BaseOfData;
    //                 DWORD                ImageBase;
    //                 DWORD                SectionAlignment;
    //                 DWORD                FileAlignment;
    //                 WORD                 MajorOperatingSystemVersion;
    //                 WORD                 MinorOperatingSystemVersion;
    //                 WORD                 MajorImageVersion;
    //                 WORD                 MinorImageVersion;
    //                 WORD                 MajorSubsystemVersion;
    //                 WORD                 MinorSubsystemVersion;
    //                 DWORD                Win32VersionValue;
    //                 DWORD                SizeOfImage;
    //                 DWORD                SizeOfHeaders;
    //                 DWORD                CheckSum;
    //                 WORD                 Subsystem;
    //                 WORD                 DllCharacteristics;
    //                 DWORD                SizeOfStackReserve;
    //                 DWORD                SizeOfStackCommit;
    //                 DWORD                SizeOfHeapReserve;
    //                 DWORD                SizeOfHeapCommit;
    //                 DWORD                LoaderFlags;
    //                 DWORD                NumberOfRvaAndSizes;
    //                 IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
    IMAGE_DATA_DIRECTORY    dataDirectory;
    //                -> 
    //                DWORD VirtualAddress;
    //                DWORD Size;
    IMAGE_SECTION_HEADER    sectionHeader;
    //                ->
    //                BYTE  Name[IMAGE_SIZEOF_SHORT_NAME];
    //               union {
    //                    DWORD PhysicalAddress;
    //                    DWORD VirtualSize;
    //                } Misc;
    //                DWORD VirtualAddress;
    //                DWORD SizeOfRawData;
    //                DWORD PointerToRawData;
    //                DWORD PointerToRelocations;
    //                DWORD PointerToLinenumbers;
    //                WORD  NumberOfRelocations;
    //                WORD  NumberOfLinenumbers;
    //                DWORD Characteristics;
    PIMAGE_DOS_HEADER dosHeader;   //   DOS başlığı
    //            ->
    //            WORD   e_magic;                     // Magic number
    //            WORD   e_cblp;                      // Bytes on last page of file
    //            WORD   e_cp;                        // Pages in file
    //            WORD   e_crlc;                      // Relocations
    //            WORD   e_cparhdr;                   // Size of header in paragraphs
    //            WORD   e_minalloc;                  // Minimum extra paragraphs needed
    //            WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    //            WORD   e_ss;                        // Initial (relative) SS value
    //            WORD   e_sp;                        // Initial SP value
    //            WORD   e_csum;                      // Checksum
    //            WORD   e_ip;                        // Initial IP value
    //            WORD   e_cs;                        // Initial (relative) CS value
    //            WORD   e_lfarlc;                    // File address of relocation table
    //            WORD   e_ovno;                      // Overlay number
    //            WORD   e_res[4];                    // Reserved words
    //            WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    //            WORD   e_oeminfo;                   // OEM information; e_oemid specific
    //            WORD   e_res2[10];                  // Reserved words
    //            LONG   e_lfanew;                    // File address of new exe header
    IMAGE_FILE_HEADER fileHeader;
    //             ->
    DWORD FileSize, PeHeaderAddress, Signature;
    HANDLE fileHandle;
    HANDLE maphandle;
    LPVOID lpBase;
    LPCWSTR fileAddress = L"C:/Users/Karuu/Desktop/ConsoleApplication.exe";

    fileHandle = CreateFile((LPCWSTR)fileAddress, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        cout << "Hata :" << GetLastError() << endl;
        return 1;
    }
    maphandle = CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (maphandle == NULL) {
        cout << "Hata :" << GetLastError() << endl;
        return 2;
    }
    lpBase = MapViewOfFile(maphandle, FILE_MAP_READ, 0, 0, 0);
    if (lpBase == NULL) {
        cout << "Hata :" << GetLastError() << endl;
        return 3;
    }
    cout << "Hata Yok!" << endl;
    dosHeader = (PIMAGE_DOS_HEADER)lpBase;

    cout << dosHeader->e_lfanew;
    HANDLE lpBase;
    HANDLE  mpBase;

    LPCWSTR fileAddress = L"C:/Users/Karuu/Desktop/pe-master/Strings/ConsoleApplication.exe";
    fileHandle = CreateFile(fileAddress, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE)return 1;
    lpBase = CreateFileMapping(&fileHandle, NULL, PAGE_READONLY, 0, 0, 0);
    if (lpBase)return 2;
    mpBase = MapViewOfFile(&lpBase, FILE_MAP_READ, 0, 0, 0);
    if (mpBase) return 3;
    cout << "Hata Yok!" << endl;
    dosHeader = (PIMAGE_DOS_HEADER)mpBase;

    cout << dosHeader->e_crlc;
    CloseHandle(fileHandle);
    CloseHandle(lpBase);
    CloseHandle(mpBase);
    return 0;
    CloseHandle(fileHandle);
    return 0;
}