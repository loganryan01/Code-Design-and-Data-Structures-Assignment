/*-----------------------------------------------------------------
	File Name: EntityEditorApp.h
	Purpose: Declare all the functions for the EntityEditorApp.cpp.
	Author: Logan Ryan
	Modified: 29/06/2020
-------------------------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------------------------*/

#pragma once
#include <vector>


// The information about the entity
struct Entity {
	// x and y position of the entity
	float x = 0, y = 0;

	// Rotation of the entity
	float rotation = 0;

	// Speed of the entity
	float speed = 0;

	// Colour of the entity
	unsigned char r = 0, g = 0, b = 0;

	// Size of the entity
	float size = 1;
};

class EntityEditorApp {
public:
	// Constructor
	EntityEditorApp(int screenWidth = 800, int screenHeight = 450);
	
	// Destructor
	~EntityEditorApp();

	// Set up the app.
	bool Startup();

	// Shutdown the app.
	void Shutdown();

	// Add another entity.
	void Add();

	// Update the app
	void Update(float deltaTime);

	// Draw the entities
	void Draw();

protected:
	// The width of the window
	int m_screenWidth;

	// The height of the window
	int m_screenHeight;

	// The number of Entities that exisits
	int m_numberOfEntities;
	int m_usedElements;

	// The number of entities that the array can hold
	int m_allocatedElements;

	// The entities that have been created
	Entity* m_entities;
};

