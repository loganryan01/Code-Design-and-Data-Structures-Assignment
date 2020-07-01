/*----------------------------------------------------------------
	File Name: DoubleLinkedList.h
	Purpose: Contain the functions for the DoubleLinkedList class.
	Author: Logan Ryan
	Modified: 26/06/2020
------------------------------------------------------------------
	Copyright 2020 Logan Ryan.
----------------------------------------------------------------*/

#pragma once

struct node
{
	// Data that is within the node
	int data;

	// A reference to the previous node
	node* prev;

	// A reference to the next node
	node* next;
};

class DoubleLinkedList
{
private:
	// points to first node of list
	node* m_front;

	// points to selected node of list
	node* m_selected;

	// points to last node of list
	node* m_back;

public:
	// Default Constructor
	DoubleLinkedList();

	// Default Destructor
	~DoubleLinkedList();

	// Add a new value to the front of the list.
	void pushFront(int value);

	// Add a new value to the end of the list.
	void pushBack(int value);

	// Add a new value one before the specified node.
	void insertBefore(node* specifiedNode, int value);

	// Add a new value one after the specified node.
	void insertAfter(node* specifiedNode, int value);

	// Gets the first node in the list.
	node* begin();

	// Gets the selected node in the list.
	node* currentNode();

	// Gets the last node in the list.
	node* end();

	// Gets the value of the first node, assert if no elements.
	int first();

	// Gets the value of the selected node, assert if no elements.
	int currentValue();

	// Gets the value of the last node, assert if no elements.
	int last();

	// Gets the number of nodes that exists in the list.
	int count();

	// Remove a specific node.
	void erase(node* node);

	// Remove all elements with matching value.
	void remove(int value);

	// Remove the last node of the list.
	void popBack();

	// Remove the first node of the list.
	void popFront();

	// Checks if the list is empty.
	bool empty();

	// Remove all nodes in the list.
	void clear();

	// Sort the list in ascending order.
	void sort();

	// Move to the next node on the list.
	void moveToNext();

	// Move to the previous node on the list.
	void moveToPrev();

	// Get the value of the next node.
	int getPrevValue();

	// Get the value of the previous node. 
	int getNextValue();
};

