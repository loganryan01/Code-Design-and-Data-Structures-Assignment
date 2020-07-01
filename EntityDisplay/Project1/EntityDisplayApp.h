/*---------------------------------------------------------
	File Name: EntityDisplayApp.h
	Purpose: Declare the functions for EntityDisplayApp.cpp
	Author: Logan Ryan
	Modified: 30/06/20
-----------------------------------------------------------
	Copyright 2020 Logan Ryan.
---------------------------------------------------------*/

#pragma once
#include <vector>

// Information about the entity
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

class EntityDisplayApp 
{
public:
	// Constructor
	EntityDisplayApp(int screenWidth = 800, int screenHeight = 450);

	// Destructor
	~EntityDisplayApp();

	// Set up the application
	bool Startup();

	// Close the application
	void Shutdown();

	// Update the application
	void Update(float deltaTime);

	// Draw the entities
	void Draw();

protected:
	// Width of the window
	int m_screenWidth;

	// Height of the window
	int m_screenHeight;

	// an array of an unknown number of entities
	std::vector<Entity> m_entities;
};