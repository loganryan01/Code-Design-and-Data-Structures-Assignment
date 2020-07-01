/*----------------------------------------------
	File Name: TreeNode.cpp
	Purpose: Controls the nodes within the tree.
	Author: Logan Ryan
	Modified: 28 June 2020
------------------------------------------------
	Copyright 2020 Logan Ryan.
----------------------------------------------*/

#include "TreeNode.h"
#include "raylib.h"
#include <string>

//---------------------------------------------
// Default constructor.
//	value (int): What is the value of the node? 
//---------------------------------------------
TreeNode::TreeNode(int value) : m_value(value), m_left(nullptr), m_right(nullptr)
{
}

//--------------------
// Default destructor.
//--------------------
TreeNode::~TreeNode()
{
}

//----------------------------------------------------
// Draw the node.
//	x (int): What is the x position of the node?
//	y (int): What is the y position of the node?
//	selected (bool): Which node is currently selected?
//----------------------------------------------------
void TreeNode::Draw(int x, int y, bool selected)
{
	static char buffer[10];

	// Convert the value to a char array
	sprintf_s(buffer, "%d", m_value);

	// Draw the circle
	DrawCircle(x, y, 30, YELLOW);

	// If the node is selected, draw a green circle
	// Otherwise just draw a black circle
	if (selected == true)
		DrawCircle(x, y, 28, GREEN);
	else
		DrawCircle(x, y, 28, BLACK);

	// Draw the value inside the circle
	DrawText(buffer, x - 12, y - 10, 12, WHITE);
}