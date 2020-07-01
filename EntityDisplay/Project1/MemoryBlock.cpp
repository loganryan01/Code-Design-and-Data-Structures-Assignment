/*-----------------------------------------------
	File Name: MemoryBlock.cpp
	Purpose: Load the data from the memory block.
	Author: Logan Ryan
	Modified: 30 June 2020
-------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------*/

#include "MemoryBlock.h"
#include <Windows.h>
#include <conio.h>
#include <string>

//-----------------
// Global Variables
//-----------------
HANDLE hMapFiles;
HANDLE hSize;

Entity* entities;
int* size;

//-------------
// Constructor.
//-------------
MemoryBlock::MemoryBlock()
{

}

//------------
// Destructor.
//------------
MemoryBlock::~MemoryBlock()
{

}

//-------------------------------------------------
// Get the size from the named shared memory block.
//-------------------------------------------------
int MemoryBlock::getSize()
{
	// Gain access to a named shared memory block that already exists
	hSize = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "Size");
	
	// If the memory block exists
	if (hSize != nullptr)
	{
		// Map the memory from the shared block to a pointer we can manipulate
		size = (int*)MapViewOfFile(hSize, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	}
	
	// If the memory could not be mapped, then return NULL
	if (size == nullptr)
	{
		// If the memory block exists
		if (hSize != nullptr)
		{
			// Close the memory block
			CloseHandle(hSize);
		}

		// The size of the array is 0
		int arraySize = NULL;

		// Return 0
		return arraySize;
	}
	else
	{
		// Convert from pointer to a variable
		int arraySize = *size;

		// Then close the memory block
		if (hSize != 0)
		{
			CloseHandle(hSize);
		}

		// Return the size of the array
		return arraySize;
	}
}

//-------------------------------------------------------
// Get the data from the named shared memory block.
//	index (int): Which entity are we getting the data of?
//-------------------------------------------------------
Entity MemoryBlock::getEntityData(int index)
{
	// The name of the memory block that has all the entity data
	std::string name1 = "fe18a527-161f-49f5-bcc8-b514c3cedc2b";
	std::string filemapEntityName = name1 + std::to_string(index);
	
	// Gain access to a named shared memory block that already exists
	hMapFiles = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, filemapEntityName.c_str());
	
	// If the memory block exists
	if (hMapFiles != nullptr)
	{
		// Map the memory from the shared block to a pointer we can manipulate
		entities = (Entity*)MapViewOfFile(hMapFiles, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Entity));
	}

	// If the memory could not be mapped, then return a blank entity
	if (entities == nullptr)
	{
		// If the memory block exists
		if (hMapFiles != 0)
		{
			// Close the shared file
			CloseHandle(hMapFiles);
		}

		// Create a blank entity
		Entity entity = { 0, 0, 0, 0, 0, 0, 0, 0 };

		// Then return that entity
		return entity;
	}
	else
	{
		// Copy the data to an entity struct
		Entity entity = *entities;

		// If the memory block exists
		if (hMapFiles != 0)
		{
			// close the shared file
			CloseHandle(hMapFiles);
		}

		// Return the entity
		return entity;
	}
}