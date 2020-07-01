/*--------------------------------------------------------------
	File Name: Main.cpp
	Purpose: Load the textures and display them onto the window.
	Author: Logan Ryan
	Modified: 29/06/2020
----------------------------------------------------------------
	Copyright Logan Ryan 2020.
--------------------------------------------------------------*/

#include "raylib.h"
#include "HashTable.h"
#include <string>

// Create the Hash Table
HashTable<std::string, Texture2D> textureCache(20);

//-----------------------------------------------------------------------------------------
// Load the texture from the memory.
//	filename (const char*): The name of the file.
//	return (Texture2D): Returns the texture that has been found or added to the hash table.
//-----------------------------------------------------------------------------------------
Texture2D LoadTextureCached(const char* filename)
{
	// Check if the texture already exisits in the hash table
	if (textureCache.HasValue(filename))
		return textureCache.GetValue(filename); // Return that chosen texture if it exists in the hash table

	// Load the texture from file via raylib
	Texture2D texture = LoadTexture(filename); 

	// Then add it to the hash table
	textureCache.SetValue(filename, texture);
	return texture; // Return the texture
}

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	// Width of the window
	int screenWidth = 800;

	// Height of the window
	int screenHeight = 450;

	// Create the window
	InitWindow(screenWidth, screenHeight, "Hash Table");

	// Set the app to run at 60 frames per second
	SetTargetFPS(60);

	// Add this texture to the hash table
	Texture2D texture = LoadTextureCached("./assets/bulletBlue.png"); 

	// Load the texture again from the hash table
	Texture2D texture1 = LoadTextureCached("./assets/bulletBlue.png");
	Texture2D texture2 = LoadTextureCached("./assets/bulletBlue.png");
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		// Set background to white
		ClearBackground(RAYWHITE);

		// Draw the texture that was added to the hash table
		DrawTexture(texture, 0, 0, WHITE);

		// Draw the texture that was loaded from the hash table
		DrawTexture(texture1, 400, 0, WHITE);
		DrawTexture(texture2, 405 + texture1.width, 0, WHITE);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	// Unload the textures
	UnloadTexture(texture);
	UnloadTexture(texture1);
	UnloadTexture(texture2);
	
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}