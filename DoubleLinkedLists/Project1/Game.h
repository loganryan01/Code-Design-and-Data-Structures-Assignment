/*----------------------------------------------------
	File Name: Game.h
	Purpose: Contain the functions for the Game class.
	Author: Logan Ryan
	Modified: 26/06/2020
------------------------------------------------------
	Copyright 2020 Logan Ryan.
----------------------------------------------------*/

#pragma once

#include "raylib.h"
#include "DoubleLinkedList.h"

class Game
{
public:
	// Default Constructor
	Game();

	// Default Destructor
	~Game();

	// Check if the window is still open
	bool isWindowClosed();

	// Set up the program
	void initialisation();

	// Update the program regularly
	void update();

	// Draw the objects onto the program
	void draw();

private:
	// Navigate through the list
	void moveThroughList();

	// Update the input box
	void inputBoxUpdate();
	
	// Draw the list
	void drawList();

	// Draw the main menu
	void drawMainMenu();

	// Draw the "add" menu
	void drawAddMenu();

	// Draw the "add other" menu
	void drawAddOtherMenu();

	// Draw the "select node" menu
	void drawSelectNodeMenu();

	// Draw the "remove" menu
	void drawRemoveMenu();

	// Draw the "remove other" menu
	void drawRemoveOtherMenu();

	// Highlight the buttons
	void highlightButtons();

	// Draw the input box
	void inputBox();

	// Is the user at the main menu?
	bool m_mainMenu = true;

	// Is the user at the "add" menu?
	bool m_addMenu = false;

	// Is the user at the "remove" menu?
	bool m_removeMenu = false;

	// Is the user at the "add front" menu?
	bool m_addFront = false;

	// Is the user at the "add back" menu?
	bool m_addBack = false;

	// Is the user at the "add other" menu?
	bool m_addOther = false;

	// Is the user at the "add before" menu?
	bool m_addBefore = false;

	// Is the user at the "add after" menu?
	bool m_addAfter = false;

	// Is the user at the "remove front" menu?
	bool m_removeFront = false;

	// Is the user at the "remove back" menu?
	bool m_removeBack = false;

	// Is the user at the "remove other" menu?
	bool m_removeOther = false;

	// Is the user at the "remove by node" menu?
	bool m_removeByNode = false;

	// Is the user at the "remove by value" menu?
	bool m_removeByValue = false;

	// Did the user choose to remove all the nodes?
	bool m_removeAll = false;

	// Is the user at the "text box" menu?
	bool m_textBox = false;

	// The data that is inside the text box
	char m_data[10] = "\0";

	// How many letters are inside the text box?
	int m_letterCount = 0;

	// How many frames has the underscore char been displayed
	int m_framesCounter = 0;

	// The double linked list.
	DoubleLinkedList m_list;
};

