/*-----------------------------------------------------
	File Name: EntityEditorApp.cpp
	Purpose: Display the controls to edit the entities.
	Author: Logan Ryan
	Modified: 29/06/2020
-------------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------------*/

#include "EntityEditorApp.h"
#include <random>
#include <time.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "MemoryBlock.h"

// Access the named shared memory blocks.
MemoryBlock m_memoryBlock;

//-------------
// Constructor.
//-------------
EntityEditorApp::EntityEditorApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_numberOfEntities(1), 
m_entities(new Entity[m_numberOfEntities]), m_usedElements(1), m_allocatedElements(1) {

}

//------------
// Destructor.
//------------
EntityEditorApp::~EntityEditorApp() {

}

//----------------
// Set up the app.
//----------------
bool EntityEditorApp::Startup() {

	// Create the window.
	InitWindow(m_screenWidth, m_screenHeight, "EntityEditorApp");

	// Set the target frames per second to 60.
	SetTargetFPS(60);

	// Generate random numbers every time the app starts.
	srand(time(nullptr));

	// Create the starting entities
	for (int i = 0; i < m_numberOfEntities; i++) {
		// Generate a random x pos.
		m_entities[i].x = rand() % m_screenWidth;

		// Generate a random y pos.
		m_entities[i].y = rand() % m_screenHeight;

		// Set the size to 10
		m_entities[i].size = 10;

		// Generate a random speed.
		m_entities[i].speed = rand() % 100;

		// Generate a random rotation.
		m_entities[i].rotation = rand() % 360;

		// Generate a random colour.
		m_entities[i].r = rand() % 255;
		m_entities[i].g = rand() % 255;
		m_entities[i].b = rand() % 255;
	}

	// Create the named shared memory blocks
	m_memoryBlock.SetUp(m_numberOfEntities);

	return true;
}

//------------------
// Shutdown the app.
//------------------
void EntityEditorApp::Shutdown() {

	// Close the named shared memory blocks
	m_memoryBlock.UnMap(m_numberOfEntities);
	
	CloseWindow();        // Close window and OpenGL context
}

//--------------------
// Add another entity.
//--------------------
void EntityEditorApp::Add()
{
	// If there is no more space left for the new entity
	if (m_allocatedElements == m_usedElements)
	{
		// Increase the size of the array
		m_numberOfEntities = m_numberOfEntities * 2;

		// Create new array
		Entity* newArr = new Entity[m_numberOfEntities];

		// Copy information into the new array
		for (int i = 0; i < m_allocatedElements; i++)
		{
			newArr[i] = m_entities[i];
		}

		// Empty the array
		delete[] m_entities;

		// Copy the information back into the array
		m_entities = newArr;

		// Recreate the named shared memory blocks
		m_memoryBlock.UnMap(m_allocatedElements);
		m_memoryBlock.SetUp(m_numberOfEntities); 

		// Increase the size of the array
		m_allocatedElements *= 2;
	}

	// Generate random values for the new entity
	m_entities[m_usedElements].x = rand() % m_screenWidth;
	m_entities[m_usedElements].y = rand() % m_screenHeight;
	m_entities[m_usedElements].size = 10;
	m_entities[m_usedElements].speed = rand() % 100;
	m_entities[m_usedElements].rotation = rand() % 360;
	m_entities[m_usedElements].r = rand() % 255;
	m_entities[m_usedElements].g = rand() % 255;
	m_entities[m_usedElements].b = rand() % 255;

	// Move to the next available space
	m_usedElements += 1;
}

//----------------------------------------------
// Update the app.
//	deltaTime (float): How fast is the computer?
//----------------------------------------------
void EntityEditorApp::Update(float deltaTime) {


	// select an entity to edit
	static int selection = 0;
	static bool selectionEditMode = false;
	static bool xEditMode = false;
	static bool yEditMode = false;
	static bool rotationEditMode = false;
	static bool sizeEditMode = false;
	static bool speedEditMode = false;
	static Color colorPickerValue = WHITE;

	// mouse position
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if (GuiSpinner(Rectangle{ 90, 25, 125, 25 }, "Entity", &selection, 0, m_usedElements - 1, selectionEditMode)) selectionEditMode = !selectionEditMode;

	int intX = (int)m_entities[selection].x;
	int intY = (int)m_entities[selection].y;
	int intRotation = (int)m_entities[selection].rotation;
	int intSize = (int)m_entities[selection].size;
	int intSpeed = (int)m_entities[selection].speed;


	// display editable stats within a GUI	
	GuiGroupBox(Rectangle{ 25, 70, 480, 220 }, "Entity Properties");

	if (GuiValueBox(Rectangle{ 90, 90, 125, 25 }, "x", &intX, 0, m_screenWidth, xEditMode)) xEditMode = !xEditMode;
	m_entities[selection].x = intX;

	if (GuiValueBox(Rectangle{ 90, 120, 125, 25 }, "y", &intY, 0, m_screenHeight, yEditMode)) yEditMode = !yEditMode;
	m_entities[selection].y = intY;

	m_entities[selection].rotation = GuiSlider(Rectangle{ 90, 150, 125, 25 }, "rotation", TextFormat("%2.2f", m_entities[selection].rotation), m_entities[selection].rotation, 0, 360);
	m_entities[selection].size = GuiSlider(Rectangle{ 90, 180, 125, 25 }, "size", TextFormat("%2.2f", m_entities[selection].size), m_entities[selection].size, 0, 100);
	m_entities[selection].speed = GuiSlider(Rectangle{ 90, 210, 125, 25 }, "speed", TextFormat("%2.2f", m_entities[selection].speed), m_entities[selection].speed, 0, 100);

	colorPickerValue = GuiColorPicker(Rectangle{ 260, 90, 156, 162 }, Color{ m_entities[selection].r, m_entities[selection].g, m_entities[selection].b });
	m_entities[selection].r = colorPickerValue.r;
	m_entities[selection].g = colorPickerValue.g;
	m_entities[selection].b = colorPickerValue.b;

	// add another entity
	if (mouseX >= 90 && mouseX <= 215 && mouseY >= 240 && mouseY <= 265 && IsMouseButtonPressed(0))
	{
		Add();
	}


	// move entities

	for (int i = 0; i < m_usedElements; i++) {
		if (selection == i)
			continue;

		float s = sinf(m_entities[i].rotation) * m_entities[i].speed;
		float c = cosf(m_entities[i].rotation) * m_entities[i].speed;
		m_entities[i].x -= s * deltaTime;
		m_entities[i].y += c * deltaTime;

		// wrap position around the screen
		m_entities[i].x = fmod(m_entities[i].x, m_screenWidth);
		if (m_entities[i].x < 0)
			m_entities[i].x += m_screenWidth;
		m_entities[i].y = fmod(m_entities[i].y, m_screenHeight);
		if (m_entities[i].y < 0)
			m_entities[i].y += m_screenHeight;
	}

	// save to memory block
	for (int i = 0; i < m_numberOfEntities; i++)
	{
		m_memoryBlock.WriteEntities(m_entities[i], i);
	}

	// save the size of the array
	m_memoryBlock.WriteSize(m_usedElements);
}

//-------------------
// Draw the entities.
//-------------------
void EntityEditorApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (int i = 0; i < m_numberOfEntities; i++) {
		DrawRectanglePro(
			Rectangle{ m_entities[i].x, m_entities[i].y, m_entities[i].size, m_entities[i].size }, // rectangle
			Vector2{ m_entities[i].size / 2, m_entities[i].size / 2 }, // origin
			m_entities[i].rotation,
			Color{ m_entities[i].r, m_entities[i].g, m_entities[i].b, 255 });
	}

	DrawRectangleLines(90, 240, 125, 25, GRAY);
	DrawText("Add Entity", 117, 247, 14, DARKGRAY);

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}