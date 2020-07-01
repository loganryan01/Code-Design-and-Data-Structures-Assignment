/*---------------------------------
	File Name: EntityDisplayApp.cpp
	Purpose: Display the entities.
	Author: Logan Ryan
	Modified: 30 June 2020
-----------------------------------
	Copyright 2020 Logan Ryan
---------------------------------*/

#include "EntityDisplayApp.h"
#include "raylib.h"

#include "MemoryBlock.h"

//------------------
// Global Variables.
//------------------
MemoryBlock m_memoryBlock;

//-------------------------------------------------------
// Constructor.
//	screenWidth (int): What is the width of the window?
//	screenheight (int): What is the height of the window?
//-------------------------------------------------------
EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

//------------
// Destructor.
//------------
EntityDisplayApp::~EntityDisplayApp() {

}

//-----------------------------
// Set up the application.
//	return (bool): Return true.
//-----------------------------
bool EntityDisplayApp::Startup() {

	// Create the window.
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	
	// Set the target frames per second to 60
	SetTargetFPS(60);

	// Get the number of entities
	int arraySize = m_memoryBlock.getSize(); 

	// For every entity in the vector
	for (int j = 0; j < arraySize; j++)
	{
		// Get the data of the entity and add it to the vector
		m_entities.push_back(m_memoryBlock.getEntityData(j));
	}

	return true;
}

//-----------------------
// Close the application.
//-----------------------
void EntityDisplayApp::Shutdown() {

	CloseWindow();        // Close window and OpenGL context
}

//------------------------------------------------
// Update the application.
//	deltaTime (float): How strong is the computer?
//------------------------------------------------
void EntityDisplayApp::Update(float deltaTime) {
	
	// Get the number of entities
	int numberOfEntities = m_memoryBlock.getSize();

	// Empty the vector
	m_entities.clear();

	// Then fill it with the new information about the entities
	for (int j = 0; j < numberOfEntities; j++)
	{
		m_entities.push_back(m_memoryBlock.getEntityData(j)); 
	}
}

//-------------------
// Draw the entities.
//-------------------
void EntityDisplayApp::Draw() {

	// Setup canvas to start drawing
	BeginDrawing();

	// Set background colour to white
	ClearBackground(RAYWHITE);

	// Draw entities
	for (auto& entity : m_entities) {
		DrawRectanglePro(Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// Output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	// End canvas drawing
	EndDrawing();
}