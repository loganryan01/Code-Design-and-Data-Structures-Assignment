/*------------------------------------------------------------
	File Name: MemoryBlock.cpp
	Purpose: Save all the data to a named shared memory block.
	Author: Logan Ryan
	Modified: 29/06/2020
--------------------------------------------------------------
	Copyright 2020 Logan Ryan
------------------------------------------------------------*/

#include "MemoryBlock.h"
#include <windows.h>
#include <conio.h>
#include <string>

// Files for the entities
HANDLE* hMapFiles;

// File to store the size
HANDLE hSize;

Entity* entity;
int* arraySize;

//-------------
// Constructor.
//-------------
MemoryBlock::MemoryBlock()
{
	hMapFiles = new HANDLE[m_usedElements];
}

//------------
// Destructor.
//------------
MemoryBlock::~MemoryBlock()
{

}

//---------------------------------------------
// Set up the named shared memory blocks.
//	size (int): How many files are we creating?
//---------------------------------------------
void MemoryBlock::SetUp(int size)
{
	// Create a named shared memory block to store the number of entities
	hSize = CreateFileMapping(
		INVALID_HANDLE_VALUE, // a handle to an existing virtual file, or invalid
		nullptr, // optional security attributes
		PAGE_READWRITE, // read/write access control
		0, sizeof(int), // size of the memory block,
		"Size");

	// The name of the shared memory block for the entities
	std::string name1 = "fe18a527-161f-49f5-bcc8-b514c3cedc2b";

	// Create the named shared memory blocks for the entities
	for (int j = 0; j < size; j++)
	{
		// Add the index number to the name of the shared memory block
		std::string filemapEntityName = name1 + std::to_string(j);

		// Create the named shared memory block for the current entity
		hMapFiles[j] = CreateFileMapping(
			INVALID_HANDLE_VALUE, // a handle to an existing virtual file, or invalid
			nullptr, // optional security attributes
			PAGE_READWRITE, // read/write access control
			0, sizeof(Entity), // size of the memory block,
			filemapEntityName.c_str()); 
	}
}

//-----------------------------------------------------------------------
// Write the data of the entities to the named shared memory blocks.
//	m_entity (Entity): Which entity are we writing into the memory block?
//	index (int): Which memory block are we writing the entity data into?
//-----------------------------------------------------------------------
void MemoryBlock::WriteEntities(Entity m_entity, int index)
{
	// Map the memory from the shared block to a pointer we can manipulate
	entity = (Entity*)MapViewOfFile(hMapFiles[index], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Entity));

	// If the file could not be viewed then close the handle and exit the function.
	if (entity == nullptr)
	{
		CloseHandle(hMapFiles[index]);
		return;
	}

	// Write to the memory block
	*entity = m_entity;
}

//------------------------------------------------------------
// Write the size of the array to a named shared memory block.
//	size (int): How many entities are there?
//------------------------------------------------------------
void MemoryBlock::WriteSize(int size)
{
	// Map the memory from the shared block to a pointer we can manipulate
	arraySize = (int*)MapViewOfFile(hSize, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	// If the file could not be viewed then close the handle and exit the function.
	if (arraySize == nullptr)
	{
		CloseHandle(hSize);
		return;
	}

	// Write to the memory block
	*arraySize = size;
}

//------------------------------------------
// Close the named shared memory blocks.
//	size (int): How many entities are there?
//------------------------------------------
void MemoryBlock::UnMap(int size)
{
	// Unmap the memory block since we're done with it
	UnmapViewOfFile(entity);
	
	// For each shared file that exists
	for (int j = 0; j < size; j++)
	{
		// Close the shared file
		CloseHandle(hMapFiles[j]);
	}

	// Unmap the memory block since we're done with it
	UnmapViewOfFile(arraySize);

	// Close the shared file
	CloseHandle(hSize);
}