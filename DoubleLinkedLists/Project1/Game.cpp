/*---------------------------------------------------
	File Name: Game.cpp
	Purpose: Control what is going on in the program.
	Author: Logan Ryan
	Modified: 26/06/2020
-----------------------------------------------------
	Copyright 2020 Logan Ryan.
---------------------------------------------------*/

#include "Game.h"
#include <stdlib.h>

//--------------------
// Default Constructor
//--------------------
Game::Game()
{

}

//-------------------
// Default Destructor
//-------------------
Game::~Game()
{

}

//-----------------------------------------------------------
// Check if the window is still open.
//	return (bool): Returns whether the window is open or not.
//-----------------------------------------------------------
bool Game::isWindowClosed()
{
	return WindowShouldClose();
}

//--------------------
// Set up the program.
//--------------------
void Game::initialisation()
{
	// The width of the window
	int screenWidth = 800;

	// The height of the window
	int screenHeight = 450;

	// Set the name of the window
	InitWindow(screenWidth, screenHeight, "Double Linked List");

	SetTargetFPS(60);

	m_list.pushBack(rand() % 100);
	m_list.pushBack(rand() % 100);
	m_list.pushBack(rand() % 100);
	m_list.pushBack(rand() % 100);
	m_list.pushBack(rand() % 100);
}

//------------------------------
// Update the program regularly.
//------------------------------
void Game::update()
{
	// Get the mouse positions
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	// If the user is on the main menu, "add before" menu or "add after" menu
	if (m_mainMenu || m_addBefore || m_addAfter || m_removeByNode)
	{
		// Allow the user to use the arrow keys to move through the list
		moveThroughList();
	}

	// If the user clicks the first button
	if (mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addOther == true ||
		mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addMenu == true ||
		mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_mainMenu == true ||
		mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeMenu == true ||
		mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeOther == true)
	{
		// If the user is at the "remove other" menu
		if (m_removeOther)
		{
			m_removeOther = false;
			m_removeByValue = true;
			m_textBox = true;
			
		}
		
		// If the user is at the "remove" menu
		if (m_removeMenu)
		{
			// Go to the "remove front" menu
			m_removeMenu = false;
			m_list.popFront();
			m_mainMenu = true;
		}
		
		// If the user is at the "add other" menu
		if (m_addOther)
		{
			// Go to the "add before" menu
			m_addOther = false;
			m_addBefore = true;
		}

		// If the user is at the "add" menu
		if (m_addMenu)
		{
			// Go to the "add front" menu
			m_addMenu = false;
			m_addFront = true;
			m_textBox = true;
		}

		// If the user is at the main menu
		if (m_mainMenu)
		{
			// Go to the "add" menu
			m_addMenu = true;
			m_mainMenu = false;
		}
	}

	// If the user clicks the second button
	if (mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addOther == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addMenu == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeMenu == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeOther == true)
	{
		// If the user is at the "remove other" menu
		if (m_removeOther)
		{
			m_removeOther = false;
			m_removeByNode = true;
		}
		
		// If the user is at the "remove" menu
		if (m_removeMenu)
		{
			m_removeMenu = false;
			m_list.popBack();
			m_mainMenu = true;
		}
		
		// If the user is at the "add other" menu
		if (m_addOther)
		{
			// Go to the "add after" menu
			m_addOther = false;
			m_addAfter = true;
		}
		
		// If the user is at the "add" menu
		if (m_addMenu)
		{
			// Go to the "add back" menu
			m_addMenu = false;
			m_addBack = true;
			m_textBox = true;
		}
	}

	// If the user clicks the third button
	if (mouseX >= 337 && mouseX <= 503 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addMenu == true ||
		mouseX >= 337 && mouseX <= 503 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeMenu == true ||
		mouseX >= 337 && mouseX <= 503 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeOther == true ||
		mouseX >= 230 && mouseX <= 365 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_mainMenu == true)
	{
		// If the user is at the main menu
		if (m_mainMenu)
		{
			m_list.sort();
		}
		
		// If the user is at the "remove other" menu
		if (m_removeOther)
		{
			m_removeOther = false;
			m_list.clear();
			m_mainMenu = true;
		}
		
		// If the user is at the "add" menu
		if (m_addMenu)
		{
			// Go to the "add other" menu
			m_addMenu = false;
			m_addOther = true;
		}
		
		// If the user is at the "remove other" menu
		if (m_removeMenu)
		{
			// Go to the "remove other" menu
			m_removeMenu = false;
			m_removeOther = true;
		}
	}

	// If the user chooses the "-" button
	if (mouseX >= 120 && mouseX <= 210 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_mainMenu == true)
	{
		// Go to the "remove" menu
		m_removeMenu = true;
		m_mainMenu = false;
	}

	// If the user chooses the "exit" button
	if (mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_addMenu == true ||
		mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeMenu == true ||
		mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && IsMouseButtonPressed(0) && m_removeOther == true)
	{
		// If the user is at the "remove" menu 
		if (m_removeMenu)
		{
			// Go back to the main menu
			m_removeMenu = false;
			m_mainMenu = true;
		}
		
		// If the user is at the "add" menu
		if (m_addMenu)
		{
			// Go back to the main menu
			m_addMenu = false;
			m_mainMenu = true;
		}

		// If the user is at the "remove other" menu
		if (m_removeOther)
		{
			// Go back to the "remove" menu
			m_removeOther = false;
			m_removeMenu = true;
		}
	}

	// If the user is at the "add before" or "add after" or "remove by node" menu and have pressed the space bar
	if (IsKeyPressed(KEY_SPACE) && m_addBefore ||
		IsKeyPressed(KEY_SPACE) && m_addAfter ||
		IsKeyPressed(KEY_SPACE) && m_removeByNode)
	{
		// Go to the text box screen to get the value for the new node
		if (m_addBefore || m_addAfter)
		{
			m_textBox = true;
		}
		
		// Remove the selected node and return to the main menu
		if (m_removeByNode)
		{
			m_list.erase(m_list.currentNode());
			m_removeByNode = false;
			m_mainMenu = true;
		}
	}

	// If the text box screen is open, use the logic to update the contents inside the box
	if (m_textBox)
	{
		inputBoxUpdate();
	}
}

//-----------------------------------
// Draw the objects onto the program.
//-----------------------------------
void Game::draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// Draw the main menu page
	if (m_mainMenu)
	{
		drawMainMenu();
	}

	// Draw the "add" menu page
	if (m_addMenu)
	{
		drawAddMenu();
	}

	// Draw the "add other" menu page
	if (m_addOther)
	{
		drawAddOtherMenu();
	}

	// Draw the "add before" menu page
	if (m_addBefore || m_addAfter || m_removeByNode)
	{
		drawSelectNodeMenu();
	}

	// Draw the "remove" menu page
	if (m_removeMenu)
	{
		drawRemoveMenu();
	}

	// Draw the "remove other" menu page
	if (m_removeOther)
	{
		drawRemoveOtherMenu();
	}

	// Highlight the buttons when the mouse hover overs them
	highlightButtons();

	// If the user is at the "textbox" screen
	if (m_textBox)
	{
		// Draw the textbox screen
		inputBox();
	}
		
	EndDrawing();
}

//---------------------------
// Navigate through the list.
//---------------------------
void Game::moveThroughList()
{
	// If the user presses the left arrow key
	if (IsKeyPressed(KEY_LEFT))
	{
		// Go to the previous node of the currently selected node
		m_list.moveToPrev();
	}

	// If the user presses the right arrow key
	if (IsKeyPressed(KEY_RIGHT))
	{
		// Go to the next node of the currently selected node
		m_list.moveToNext();
	}
}

//----------------------
// Update the input box.
//----------------------
void Game::inputBoxUpdate()
{
	// Get the key that user inputs
	int key = GetKeyPressed();

	// Check if the correct key has been pushed
	while (key > 0)
	{
		// Check if it is a number key and the input box is empty
		if ((key >= KEY_ZERO) && (key <= KEY_NINE) && (m_letterCount < 9))
		{
			// Set the key to the position
			m_data[m_letterCount] = (char)key;
			
			// Move to the next position
			m_letterCount++;
		}

		// Get the next key
		key = GetKeyPressed();
	}

	// If the user presses the backspace key
	if (IsKeyPressed(KEY_BACKSPACE) && m_letterCount > 0)
	{
		// Go back one space
		m_letterCount--;

		// Set it to empty
		m_data[m_letterCount] = '\0';

		// If the box is empty
		if (m_letterCount < 0)
		{
			// Just leave it empty
			m_letterCount = 0;
		}
	}

	// If the user presses the enter key
	if (IsKeyPressed(KEY_ENTER))
	{
		// Convert the char array to an int
		int i;
		i = atoi(m_data);

		// If the user is at the "add front" menu
		if (m_addFront == true)
		{
			// Add it to the front of the list
			m_list.pushFront(i);
		}

		// If the user is at the "add back" menu
		if (m_addBack == true)
		{
			// Add it to the back of the list
			m_list.pushBack(i);
		}

		// If the user is at the "add before" menu
		if (m_addBefore == true)
		{
			// Insert the node before the selected node
			m_list.insertBefore(m_list.currentNode(), i);
		}

		// If the user is at the "add after" menu
		if (m_addAfter == true)
		{
			// Insert the node after the selected node
			m_list.insertAfter(m_list.currentNode(), i);
		}

		// if the user is at the "remove by value" menu
		if (m_removeByValue == true)
		{
			// Remove all the nodes that have the same value
			m_list.remove(i);
		}

		// Go back to the main menu
		m_textBox = false;
		m_addFront = false;
		m_addBack = false;
		m_addBefore = false;
		m_addAfter = false;
		m_removeByValue = false;
		m_mainMenu = true;
	}

	// Increase frames counter by 1
	m_framesCounter++;
}

//---------------
// Draw the list.
//---------------
void Game::drawList()
{
	// Draw the next node
	if (m_list.getPrevValue() != NULL)
	{
		// Get the next node value
		int i = m_list.getPrevValue();

		// Convert to char array to display the value
		char display[10];
		_itoa_s(i, display, 10);

		// If the prev value is the first value of the list
		if (i == m_list.first())
		{
			// Set the text to be green
			DrawText(display, 235, 225, 20, GREEN);
		}
		else
		{
			// Otherwise just set the text to be black
			DrawText(display, 235, 225, 20, BLACK);
		}
	}

	// Draw the current node
	if (m_list.currentValue() != NULL)
	{
		// Get the selected node value
		int i = m_list.currentValue();

		// Convert to char array to display the value
		char display[10];
		_itoa_s(i, display, 10);

		// If the value is the first value of the list
		if (i == m_list.first() && i != m_list.last())
		{
			// Set the text to be green
			DrawText(display, 347, 225, 20, GREEN);
		}

		// If the value is the first and the last value of the list
		else if (i == m_list.first() && i == m_list.last())
		{
			// Set the text to be blue
			DrawText(display, 347, 225, 20, BLUE);
		}

		// If the value is the last value of the list
		else if (i != m_list.first() && i == m_list.last())
		{
			// Set the text to be red
			DrawText(display, 347, 225, 20, RED);
		}
		else
		{
			// Otherwise just set the text to be black
			DrawText(display, 347, 225, 20, BLACK);
		}
	}

	// Draw the next node
	if (m_list.getNextValue() != NULL)
	{
		// Get the next node value
		int i = m_list.getNextValue();

		// Convert to char array to display the value
		char display[10];
		_itoa_s(i, display, 10);

		// If the next value is the last value of the list
		if (i == m_list.last())
		{
			// Set it to be red
			DrawText(display, 460, 225, 20, RED);
		}
		else
		{
			// Otherwise just set the text to be black
			DrawText(display, 460, 225, 20, BLACK);
		}
	}
}

//--------------------
// Draw the main menu.
//--------------------
void Game::drawMainMenu()
{
	// Draw the buttons for the main menu
	DrawRectangleLines(10, 10, 100, 50, BLACK);
	DrawText("+", 45, 13, 50, LIGHTGRAY);

	DrawRectangleLines(120, 10, 100, 50, BLACK);
	DrawText("-", 160, 13, 50, LIGHTGRAY);

	DrawRectangleLines(230, 10, 135, 50, BLACK);
	DrawText("Sort", 240, 13, 50, LIGHTGRAY);

	// Draw the list
	drawList();
}

//---------------------
// Draw the "add" menu.
//---------------------
void Game::drawAddMenu()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);

	// Draw the buttons for the "add" menu
	DrawRectangleLines(10, 10, 166, 50, BLACK);
	DrawText("Front", 20, 13, 50, LIGHTGRAY);

	DrawRectangleLines(186, 10, 141, 50, BLACK);
	DrawText("Back", 196, 13, 50, LIGHTGRAY);

	DrawRectangleLines(337, 10, 166, 50, BLACK);
	DrawText("Other", 347, 13, 50, LIGHTGRAY);

	DrawRectangleLines(660, 10, 135, 50, BLACK);
	DrawText("Exit", 682, 13, 50, LIGHTGRAY);
}

//---------------------------
// Draw the "add other" menu.
//---------------------------
void Game::drawAddOtherMenu()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);

	// Draw the buttons for the "add other" menu
	DrawRectangleLines(10, 10, 196, 64, BLACK);
	DrawText("Before", 20, 13, 50, LIGHTGRAY);

	DrawRectangleLines(216, 10, 160, 64, BLACK);
	DrawText("After", 226, 13, 50, LIGHTGRAY);

	DrawRectangleLines(660, 10, 135, 50, BLACK);
	DrawText("Exit", 682, 13, 50, LIGHTGRAY);
}

//-----------------------------
// Draw the "select node" menu.
//-----------------------------
void Game::drawSelectNodeMenu()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);

	// Tell the user to choose a node
	DrawText("CHOOSE A NODE!", 270, 100, 30, RED);
	
	// Draw the nodes
	drawList();

	// Tell the user to press the space bar when they have made thier decision
	DrawText("Press SPACE to Continue", 267, 350, 20, GRAY);
}

//------------------------
// Draw the "remove" menu.
//------------------------
void Game::drawRemoveMenu()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);

	// Draw the buttons for the "remove" menu
	DrawRectangleLines(10, 10, 166, 50, BLACK);
	DrawText("Front", 20, 13, 50, LIGHTGRAY);

	DrawRectangleLines(186, 10, 141, 50, BLACK);
	DrawText("Back", 196, 13, 50, LIGHTGRAY);

	DrawRectangleLines(337, 10, 166, 50, BLACK);
	DrawText("Other", 347, 13, 50, LIGHTGRAY);

	DrawRectangleLines(660, 10, 135, 50, BLACK);
	DrawText("Exit", 682, 13, 50, LIGHTGRAY);
}

//------------------------------
// Draw the "remove other" menu.
//------------------------------
void Game::drawRemoveOtherMenu()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);

	// Draw the buttons for the "remove other" menu
	DrawRectangleLines(10, 10, 166, 50, BLACK);
	DrawText("Value", 20, 13, 50, LIGHTGRAY);

	DrawRectangleLines(186, 10, 141, 50, BLACK);
	DrawText("Node", 196, 13, 50, LIGHTGRAY);

	DrawRectangleLines(337, 10, 100, 50, BLACK);
	DrawText("All", 347, 13, 50, LIGHTGRAY);

	DrawRectangleLines(660, 10, 135, 50, BLACK);
	DrawText("Exit", 682, 13, 50, LIGHTGRAY);
}

//-----------------------
// Highlight the buttons.
//-----------------------
void Game::highlightButtons()
{
	// Get the mouses position
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	
	// If the mouses position is over the 1st button
	if (mouseX >= 10 && mouseX <= 100 && mouseY >= 10 && mouseY <= 50 && m_mainMenu == true ||
		mouseX >= 10 && mouseX <= 176 && mouseY >= 10 && mouseY <= 50 && m_addMenu == true ||
		mouseX >= 10 && mouseX <= 176 && mouseY >= 10 && mouseY <= 50 && m_removeMenu == true ||
		mouseX >= 10 && mouseX <= 176 && mouseY >= 10 && mouseY <= 50 && m_removeOther == true ||
		mouseX >= 10 && mouseX <= 206 && mouseY >= 10 && mouseY <= 50 && m_addOther == true)
	{
		// Highlight the box with a green box
		if (m_mainMenu)
		{
			DrawRectangleLines(10, 10, 100, 50, GREEN);
		}

		if (m_addOther)
		{
			DrawRectangleLines(10, 10, 196, 64, GREEN);
		}

		if (m_addMenu == true || m_removeMenu == true || m_removeOther == true)
		{
			DrawRectangleLines(10, 10, 166, 50, GREEN);
		}
	}

	// If the mouses position is over the 2nd button
	if (mouseX >= 120 && mouseX <= 210 && mouseY >= 10 && mouseY <= 50 && m_mainMenu == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && m_addMenu == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && m_removeMenu == true ||
		mouseX >= 186 && mouseX <= 327 && mouseY >= 10 && mouseY <= 50 && m_removeOther == true ||
		mouseX >= 10 && mouseX <= 206 && mouseY >= 10 && mouseY <= 50 && m_addOther == true)
	{
		// Highlight the box with a green box
		if (m_mainMenu == true)
		{
			DrawRectangleLines(120, 10, 100, 50, GREEN);
		}

		if (m_addMenu == true || m_removeMenu == true || m_removeOther == true)
		{
			DrawRectangleLines(186, 10, 141, 50, GREEN);
		}
	}

	// If the mouses position is over the 3rd button
	if (mouseX >= 230 && mouseX <= 365 && mouseY >= 10 && mouseY <= 50 && m_mainMenu == true ||
		mouseX >= 337 && mouseX <= 503 && mouseY >= 10 && mouseY <= 50 && m_addMenu == true ||
		mouseX >= 337 && mouseX <= 503 && mouseY >= 10 && mouseY <= 50 && m_removeMenu == true ||
		mouseX >= 337 && mouseX <= 437 && mouseY >= 10 && mouseY <= 50 && m_removeOther == true)
	{
		// Highlight the box with a green box
		if (m_mainMenu == true)
		{
			DrawRectangleLines(230, 10, 135, 50, GREEN);
		}

		if (m_addMenu == true || m_removeMenu == true)
		{
			DrawRectangleLines(337, 10, 166, 50, GREEN);
		}

		if (m_removeOther == true)
		{
			DrawRectangleLines(337, 10, 100, 50, GREEN);
		}
	}

	// Highlight the "exit" button if the mouse is over the button
	if (mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && m_addMenu == true ||
		mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && m_removeMenu == true ||
		mouseX >= 660 && mouseX <= 765 && mouseY >= 10 && mouseY <= 50 && m_removeOther == true)
	{
		DrawRectangleLines(660, 10, 135, 50, GREEN);
	}
}

//--------------------
// Draw the input box.
//--------------------
void Game::inputBox()
{
	// Clear the screen
	DrawRectangle(0, 0, 800, 450, RAYWHITE);
	
	// Tell the user to input a number
	DrawText("INPUT A NUMBER!", 310, 180, 20, GRAY);

	// Draw the text box
	DrawRectangle(289, 200, 222, 40, GRAY);
	DrawRectangleLines(289, 200, 222, 40, RED);

	// Draw the text
	DrawText(m_data, 294, 200, 40, MAROON);
	if (((m_framesCounter / 20) % 2) == 0 && m_letterCount < 9)
	{
		DrawText("_", 297 + MeasureText(m_data, 40), 200, 40, MAROON);
	}

	// Tell the user to press the enter key when they are done
	DrawText("Press ENTER to Continue", 266, 240, 20, GRAY);
}