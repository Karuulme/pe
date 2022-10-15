#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{


    // TITLE TRANSITIONS  
    //     Gerekmedikçe kullanmıyoruz tabiki, önce araştırın, daha hızlı öğrenirsiniz. takıldığınız noktada bakın :)
    //     ->
    //     MAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)buffer;
    //     PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)((BYTE*)pidh + pidh->e_lfanew);
    //     EFILE_HEADER pifh = (PIMAGE_FILE_HEADER)&pinh->FileHeader;
    //     EOPTIONAL_HEADER pioh = (PIMAGE_OPTIONAL_HEADER)&pinh->OptionalHeader;
    //	   ESECTION_HEADER pish = (PIMAGE_SECTION_HEADER)((BYTE*)pinh + sizeof(IMAGE_NT_HEADERS) + (pifh->NumberOfSections - 1) * sizeof(IMAGE_SECTION_HEADER));


    // MAGE_DOS_HEADER pidh   -> PIMAGE_NT_HEADERS  ->   EFILE_HEADER   ->    EOPTIONAL_HEADER    ->   ESECTION_HEADER


    PIMAGE_NT_HEADERS    ntHeaders;
    //            ->
    //            DWORD                   Signature;
    //            IMAGE_FILE_HEADER       FileHeader;
    //            IMAGE_OPTIONAL_HEADER32 OptionalHeader;
    PIMAGE_OPTIONAL_HEADER   optinalHeader;
    //            ->
    //            WORD                 Magic;
    //            BYTE                 MajorLinkerVersion;
    //            BYTE                 MinorLinkerVersion;
    //            DWORD                SizeOfCode;
    //            DWORD                SizeOfInitializedData;
    //            DWORD                SizeOfUninitializedData;
    //            DWORD                AddressOfEntryPoint;
    //            DWORD                BaseOfCode;
    //            DWORD                BaseOfData;
    //            DWORD                ImageBase;
    //            DWORD                SectionAlignment;
    //            DWORD                FileAlignment;
    //            WORD                 MajorOperatingSystemVersion;
    //            WORD                 MinorOperatingSystemVersion;
    //            WORD                 MajorImageVersion;
    //            WORD                 MinorImageVersion;
    //            WORD                 MajorSubsystemVersion;
    //            WORD                 MinorSubsystemVersion;
    //            DWORD                Win32VersionValue;
    //            DWORD                SizeOfImage;
    //            DWORD                SizeOfHeaders;
    //            DWORD                CheckSum;
    //            WORD                 Subsystem;
    //            WORD                 DllCharacteristics;
    //            DWORD                SizeOfStackReserve;
    //            DWORD                SizeOfStackCommit;
    //            DWORD                SizeOfHeapReserve;
    //            DWORD                SizeOfHeapCommit;
    //            DWORD                LoaderFlags;
    //            DWORD                NumberOfRvaAndSizes;
    //            IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
    PIMAGE_DATA_DIRECTORY    dataDirectory;
    //            -> 
    //            DWORD VirtualAddress;
    //            DWORD Size;
    PIMAGE_SECTION_HEADER    sectionHeader;
    //            ->
    //            BYTE  Name[IMAGE_SIZEOF_SHORT_NAME];
    //            union 
    //		      {
    //              DWORD PhysicalAddress;
    //            	DWORD VirtualSize;
    //            } Misc;
    //            DWORD VirtualAddress;
    //            DWORD SizeOfRawData;
    //            DWORD PointerToRawData;
    //            DWORD PointerToRelocations;
    //            DWORD PointerToLinenumbers;
    //            WORD  NumberOfRelocations;
    //            WORD  NumberOfLinenumbers;
    //            DWORD Characteristics;
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
    PIMAGE_FILE_HEADER fileHeader;
    //            ->
    //            WORD  Machine;
    //            WORD  NumberOfSections;
    //            DWORD TimeDateStamp;
    //            DWORD PointerToSymbolTable;
    //            DWORD NumberOfSymbols;
    //            WORD  SizeOfOptionalHeader;
    //            WORD  Characteristics;
    DWORD FileSize, PeHeaderAddress, Signature;
    HANDLE fileHandle, optHeader, selectHeader;
    HANDLE maphandle;
    LPVOID lpBase;
    //  PIMAGE_EXPORT_DIRECTORY importDirectory;
    IMAGE_IMPORT_DESCRIPTOR* importDescriptor = {};
    DWORD thunk;
    PIMAGE_THUNK_DATA thunkData;

    // LPCWSTR fileAddress = L"C:/Users/Karuu/Desktop/pe calisma/Untitled5.exe";
    LPCWSTR fileAddress = L"C:/Program Files (x86)/Dev-Cpp/devcpp.exe";

    fileHandle = CreateFile(fileAddress, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
    dosHeader = (PIMAGE_DOS_HEADER)lpBase;
    if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
        //  cout<<"Dos exe File"<<endl;
    }
    ntHeaders = (PIMAGE_NT_HEADERS)((BYTE*)dosHeader + (dosHeader->e_lfanew));
    //  cout << ntHeaders->Signature<<endl;
    if (ntHeaders->Signature == IMAGE_NT_SIGNATURE) {
        //  cout<<"PE File"<<endl;
    }

    fileHeader = (PIMAGE_FILE_HEADER) & (ntHeaders->FileHeader);
    optHeader = (PIMAGE_OPTIONAL_HEADER) & (ntHeaders->OptionalHeader);


    sectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)ntHeaders + sizeof(DWORD) + (DWORD)(sizeof(IMAGE_FILE_HEADER)) + (DWORD)ntHeaders->FileHeader.SizeOfOptionalHeader));
    DWORD sectionSize = (DWORD)sizeof(IMAGE_SECTION_HEADER);
    cout << "+ SECTION_HEADER - " << fileHeader->NumberOfSections << endl;


    

    for (int i = 0; i < fileHeader->NumberOfSections; i++, sectionHeader++) { // SECTION NAMES

        printf("- \t%s\n", sectionHeader->Name);
        char name[sizeof(sectionHeader->Name)];
        memcpy(name, sectionHeader->Name, sizeof(sectionHeader->Name));
        string namef = (string)name;
        if (namef == ".idata") {
            DWORD importDirectionRVA = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
            DWORD  rawOffset = (DWORD)lpBase + sectionHeader->PointerToRawData;
            PIMAGE_IMPORT_DESCRIPTOR importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(rawOffset + importDirectionRVA - sectionHeader->VirtualAddress);
            printf("\n******* DLL IMPORTS *******\n");

            for (; importDescriptor->Name != 0; importDescriptor++)  //DLL NAMES
            {
                printf("\t%s\n", rawOffset + (importDescriptor->Name - sectionHeader->VirtualAddress));
                thunk = importDescriptor->OriginalFirstThunk == 0 ? importDescriptor->FirstThunk : importDescriptor->OriginalFirstThunk;
                thunkData = (PIMAGE_THUNK_DATA)(rawOffset + (thunk - sectionHeader->VirtualAddress));

                for (; thunkData->u1.AddressOfData != 0; thunkData++)  //DLL FUNCİTON NAMES
                {
                    if (thunkData->u1.AddressOfData > 0x80000000) {
                        printf("\t\tOrdinal: %x\n", (WORD)thunkData->u1.AddressOfData);
                    }
                    else {
                        printf("\t\t%s\n", (rawOffset + (thunkData->u1.AddressOfData - sectionHeader->VirtualAddress + 2)));
                    }
                }

            }
        }
    }

    CloseHandle(fileHandle);
    return 0;
}