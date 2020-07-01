/*----------------------------------------------------
	File Name: MemoryBlock.h
	Purpose: Declare the functions for MemoryBlock.cpp
	Author: Logan Ryan
	Modified: 30/06/20
------------------------------------------------------
	Copyright 2020 Logan Ryan.
----------------------------------------------------*/

#pragma once
#include "EntityDisplayApp.h"
#include <iostream>

class EntityDisplayApp;

class MemoryBlock : public EntityDisplayApp {
public:
	// Constructor
	MemoryBlock();

	// Destructor
	~MemoryBlock();

	// Get the data from the named shared memory block
	Entity getEntityData(int index);

	// Get the size from the named shared memory block
	int getSize();
};