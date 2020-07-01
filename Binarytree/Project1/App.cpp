/*----------------------------
    File Name: App.cpp
    Purpose: Draws the app.
    Author: Logan Ryan
    Modified: 28 June 2020
------------------------------
    Copyright 2020 Logan Ryan.
----------------------------*/

#include "App.h"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "BinaryTree.h"
#include "TreeNode.h"

//---------------------
// Default constructor.
//---------------------
App::App()
{

}

//--------------------
// Default destructor.
//--------------------
App::~App()
{

}

//-------------------
// Create the window.
//-------------------
void App::Startup()
{
    // The width of the window
    int screenWidth = 800;

    // The height of the window
    int screenHeight = 450;

    // Create the window
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Set the target frames per second to be 60.
    SetTargetFPS(60);
}

//------------------
// Close the window.
//------------------
void App::Shutdown()
{
    CloseWindow();        // Close window and OpenGL context
}

//--------------------------
// The logic to run the app.
//--------------------------
void App::Run()
{
    BinaryTree m_binaryTree;
    TreeNode* m_selectedNode = nullptr;

    m_binaryTree.Insert(rand() % 100);
    m_binaryTree.Insert(rand() % 100);
    m_binaryTree.Insert(rand() % 100);
    m_binaryTree.Insert(rand() % 100);
    m_binaryTree.Insert(rand() % 100);

    int valueBoxValue = 0;
    bool valueBoxEditMode = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        // Set the background to white
        ClearBackground(RAYWHITE);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

        // If the value box is empty, display 0
        if (GuiValueBox(Rectangle{ 25, 25, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;

        // If the user clicks the "insert" button
        if (GuiButton(Rectangle{ 160, 25, 125, 30 }, GuiIconText(RICON_OK_TICK, "Insert")))
        {
            // Insert the node
            m_binaryTree.Insert(valueBoxValue);

            // Set the selected node to the new node
            m_selectedNode = m_binaryTree.Find(valueBoxValue);
        }

        // If the user clicks the "remove" button
        if (GuiButton(Rectangle{ 160, 60, 125, 30 }, GuiIconText(RICON_CROSS, "Remove")))
        {
            // Remove the node
            m_binaryTree.Remove(valueBoxValue);
        }

        // If the user clicks the "find" button
        if (GuiButton(Rectangle{ 160, 95, 125, 30 }, GuiIconText(RICON_LENS, "Find")))
        {
            // Find the node and set it to selected
            m_selectedNode = m_binaryTree.Find(valueBoxValue);
        }

        // Draw the binary tree
        m_binaryTree.Draw(m_selectedNode);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}