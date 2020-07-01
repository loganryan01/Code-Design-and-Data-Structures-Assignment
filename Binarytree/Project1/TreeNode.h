/*--------------------------------------------------------------------
	File Name: TreeNode.h
	Purpose: Contain the function declarations for the TreeNode class.
	Author: Logan Ryan
	Modified: 28 June 2020
----------------------------------------------------------------------
	Copyright 2020 Logan Ryan.
--------------------------------------------------------------------*/

#pragma once

class TreeNode
{
public:
	// Default constructor
	TreeNode(int value);

	// Default destructor
	~TreeNode();

	// Check if the node has a left or right child
	bool HasLeft() { return (m_left != nullptr); }
	bool HasRight() { return (m_right != nullptr); }

	// Get the data in the node
	int GetData() { return m_value; }

	// Get the left node of the subtree
	TreeNode* GetLeft() { return m_left; }

	// Get the right node of the subtree
	TreeNode* GetRight() { return m_right; }

	// Set the data in the node
	void SetData(int value) { m_value = value; }

	// Set the left node of the subtree
	void SetLeft(TreeNode* node) { m_left = node; }

	// Set the right node of the subtree
	void SetRight(TreeNode* node) { m_right = node; }

	// Draw the node
	void Draw(int x, int y, bool selected = false);

private:
	// this could also be a pointer to another object if you like
	int m_value;

	// node's children
	TreeNode* m_left;
	TreeNode* m_right;
};

