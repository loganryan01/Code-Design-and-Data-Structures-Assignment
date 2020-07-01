// Inter-ProcessCommunication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    // gain access to a named shared memory block that already exists
    HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");

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

    // write out what is in the memory block
    std::cout << "MyData = { ";
    std::cout << data->i << ", ";
    std::cout << data->f << ", ";
    std::cout << data->c << ", ";
    std::cout << data->b << ", ";
    std::cout << data->d;
    std::cout << " };" << std::endl;

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
