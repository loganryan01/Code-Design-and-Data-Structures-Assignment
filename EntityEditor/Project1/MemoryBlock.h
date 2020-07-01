/*-------------------------------------------------------------
	File Name: MemoryBlock.h
	Purpose: Declare all the functions for the MemoryBlock.cpp.
	Author: Logan Ryan
	Modified: 29/06/2020
---------------------------------------------------------------
	Copyright 2020 Logan Ryan
-------------------------------------------------------------*/

#pragma once
#include "EntityEditorApp.h"

class EntityEditorApp;

class MemoryBlock : public EntityEditorApp
{
public:
	// Constructor
	MemoryBlock();

	// Destructor
	~MemoryBlock();

	// Set up the named shared memory blocks
	void SetUp(int size);

	// Write the data of the entities to the named shared memory blocks.
	void WriteEntities(Entity m_entity, int index);

	// Write the size of the array to a named shared memory block
	void WriteSize(int size);

	// Close the named shared memory blocks
	void UnMap(int size);
};

