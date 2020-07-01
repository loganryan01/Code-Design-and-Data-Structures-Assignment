// Inter-ProcessCommunication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

struct MyData
{
    int i;
    float f;
    char c;
    bool b;
    double d;
};

int main()
{
    MyData myData = { 99, 7.56f, 'A', true, 69.42 };

    // open a neamed shared memory block
    HANDLE fileHandle = CreateFileMapping(
            INVALID_HANDLE_VALUE, // a handle to an existing virtual file, or invalid
            nullptr, // optional security attributes
            PAGE_READWRITE, // read/write access control
            0, sizeof(MyData), // size pf the memory block,
            L"MySharedMemory");

    if (fileHandle == nullptr)
    {
        std::cout << "Could not create file mapping object: " << GetLastError() << std::endl;
        return 1;
    }

    // map the memory from the shared block to a pointer we can manipulate
    MyData* data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));

    if (data == nullptr)
    {
        std::cout << "Could not map view of file: " << GetLastError() << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }

    // write to the memory block
    *data = myData;
    
    // wait for a keypress to close
    _getch();

    // unmap the memory block since we're done with it
    UnmapViewOfFile(data);

    // close the shared file
    CloseHandle(fileHandle);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
