/*---------------------------------------------------------
	File Name: DoubleLinkedList.cpp
	Purpose: Control the Double Linked List in the program.
	Author: Logan Ryan
	Modified: 26/06/2020
-----------------------------------------------------------
	Copyright 2020 Logan Ryan.
---------------------------------------------------------*/

#include "DoubleLinkedList.h"
#include <cstddef>
#include <cassert>
#include <iostream>

#define NDEBUG

//--------------------
// Default Constructor
//--------------------
DoubleLinkedList::DoubleLinkedList()
{
	m_front = nullptr;
	m_back = nullptr;
	m_selected = m_front;
}

//-------------------
// Default Destructor
//-------------------
DoubleLinkedList::~DoubleLinkedList()
{

}

//----------------------------------------------------
// Add a new value to the front of the list.
//	value (int): What value are we adding to the list?
//----------------------------------------------------
void DoubleLinkedList::pushFront(int value)
{
	// Create a new node
	node* newNode;
	newNode = new node();

	// Set its data to the inputed value
	newNode->data = value;

	// Set the new nodes prev to null
	newNode->prev = nullptr;

	// Set the new nodes next point to the original front
	newNode->next = m_front;

	// If the list is empty
	if (m_front == nullptr)
	{
		// Set the new node the back as well
		m_back = newNode;
	}
	else
	{
		// Otherwise, set the original front nodes prev point to the new node
		m_front->prev = newNode;
	}

	// Set the new node to be the front node
	m_front = newNode;

	// Set the selected node equal to the front node
	m_selected = m_front;
}

//------------------------------------------
// Add a new value to the end of the list.
//	value (int): What value are we removing?
//------------------------------------------
void DoubleLinkedList::pushBack(int value)
{
	// create a new node
	node* newNode;
	newNode = new node();

	// Set its data to the inputed value
	newNode->data = value;

	// Make the new nodes prev point to the original back
	newNode->prev = m_back;

	// Make the new nodes next to null
	newNode->next = nullptr;

	// if list is empty
	if (m_back == nullptr)
	{
		// Make the new node the front node as well
		m_front = newNode;
	}
	else
	{
		// Otherwise just make the original back nodes next point to the new node
		m_back->next = newNode;
	}

	// Set the new node to be the back node
	m_back = newNode;

	// Set the selected node equal to the front node
	m_selected = m_front;
}

//----------------------------------------------------------------------------
// Add a new value one before the specified node.
//	specifiedNode (node*): Which node are we putting the new node in front of?
//	value (int): What value are we adding?
//----------------------------------------------------------------------------
void DoubleLinkedList::insertBefore(node* specifiedNode, int value)
{
	// Create a new node
	node* newNode;
	newNode = new node();

	// Set the data to be the input value
	newNode->data = value;

	// If the specified node's does have a next node
	if (specifiedNode->prev != nullptr)
	{
		// Set the specified nodes prev nodes next pointing to the new node
		specifiedNode->prev->next = newNode;
	}

	// Set the new nodes next pointer pointing to the specified node
	newNode->next = specifiedNode;

	// Set the new nodes prev pointer pointing to the specified node's prev node
	newNode->prev = specifiedNode->prev;

	// Set the specified node's prev pointer pointing to the new node
	specifiedNode->prev = newNode;

	// if node is to be inserted before first node
	if (specifiedNode == m_front)
	{
		// Set it to be the front node
		m_front = newNode;
	}

	// Set the selected node to be the front node
	m_selected = m_front;
}

//--------------------------------------------------------------------------
// Add a new value one after the specified node.
//	specifiedNode (node*): Which node are we putting the new node behind of?
//	value (int): What value are we adding?
//--------------------------------------------------------------------------
void DoubleLinkedList::insertAfter(node* specifiedNode, int value)
{
	// Create a new node
	node* newNode;
	newNode = new node();

	// Set the data to be the input value
	newNode->data = value;

	// If the specified node does have a next node
	if (specifiedNode->next != nullptr)
	{
		// Set the specified nodes prev nodes next pointing to the new node
		specifiedNode->next->prev = newNode;
	}

	// Set the new nodes prev pointer pointing to the iterator
	newNode->prev = specifiedNode;

	// Set the new nodes next pointer pointing to the iterators next node
	newNode->next = specifiedNode->next;

	// Set the iterators prev pointer pointing to the new node
	specifiedNode->next = newNode;

	// if node is to be inserted before last node
	if (specifiedNode == m_back)
	{
		// Set it to be the back node
		m_back = newNode;
	}

	// Set the selected node to be the front node
	m_selected = m_front;
}

//-----------------------------------------------------------
// Gets the first node in the list.
//	return (node*): Returns an iterator to the first element.
//-----------------------------------------------------------
node* DoubleLinkedList::begin()
{
	return m_front;
}

//--------------------------------------------------------------
// Gets the selected node in the list.
//	return (node*): Returns an iterator to the selected element.
//--------------------------------------------------------------
node* DoubleLinkedList::currentNode()
{
	return m_selected;
}

//----------------------------------------------------------
// Gets the last node in the list.
//	return (node*): Returns an iterator to the last element.
//----------------------------------------------------------
node* DoubleLinkedList::end()
{
	return m_back;
}

//---------------------------------------------------------
// Gets the value of the first node, assert if no elements.
//	return (int): Returns the value of the first node.
//---------------------------------------------------------
int DoubleLinkedList::first()
{
	if (m_front != nullptr)
	{
		return m_front->data;
	}
	else
	{
		// Tell the user that there is no elements in the list
		assert(m_front == nullptr);
		std::cout << "There are no elements in the list." << std::endl;
	}
	
	return NULL;
}

//------------------------------------------------------------
// Gets the value of the selected node, assert if no elements.
//	return (int): Returns the value of the selected node.
//------------------------------------------------------------
int DoubleLinkedList::currentValue()
{
	if (m_selected != nullptr)
	{
		return m_selected->data;
	}
	else
	{
		// Tell the user that there is no elements in the list
		assert(m_selected == nullptr);
		std::cout << "There are no elements in the list." << std::endl;
	}

	return NULL;
}

//--------------------------------------------------------
// Gets the value of the last node, assert if no elements.
//	return (int): Returns the value of the last node.
//--------------------------------------------------------
int DoubleLinkedList::last()
{
	if (m_back != nullptr)
	{
		return m_back->data;
	}
	else
	{
		// Tell the user that there is no elements in the list
		assert(m_back == nullptr);
		std::cout << "There are no elements in the list." << std::endl;
	}

	return NULL;
}

//-------------------------------------------------------------------
// Gets the number of nodes that exists in the list.
//	return (int): Returns the number of nodes that exist in the list.
//-------------------------------------------------------------------
int DoubleLinkedList::count()
{
	// Holds how many nodes there are
	int length = 0;
	struct node* current;

	// Starting from the front of the list, add 1 to length for every node it finds.
	for (current = m_front; current != nullptr; current = current->next)
	{
		length++;
	}

	return length;
}

//------------------------
// Remove a specific node.
//------------------------
void DoubleLinkedList::erase(node* specifiedNode)
{
	// if node to be deleted is first node of list
	if (specifiedNode->prev == nullptr)
	{
		// The next node will be front of list
		m_front = specifiedNode->next;
		m_front->prev = nullptr;
	}

	// if node to be deleted is last node of list
	else if (specifiedNode->next == nullptr)
	{
		// The previous node will be last of list
		m_back = specifiedNode->prev;
		m_back->next = nullptr;
	}
	else
	{
		// Previous node's next will point to current node's next
		specifiedNode->prev->next = specifiedNode->next;
		// Next node's prev will point to current node's prev
		specifiedNode->next->prev = specifiedNode->prev;
	}

	// Delete the node
	delete(specifiedNode);

	// Set the selected node to be the front node
	m_selected = m_front;
}

//------------------------------------------
// Remove all elements with matching value.
//	value (int): What value are we removing?
//------------------------------------------
void DoubleLinkedList::remove(int value)
{
	// Which node are we up to?
	struct node* current = m_front;

	// Hold the node to be deleted.
	struct node* nodeToBeDeleted = nullptr;

	// If the list is empty
	if (m_front == nullptr)
	{
		return;
	}

	// Go through the list
	while (current != nullptr)
	{
		// If the data matches the value
		if (current->data == value)
		{
			// if the node is the first node in the list
			if (current == m_front)
			{
				// Set the node to be deleted to the current one.
				nodeToBeDeleted = current;

				// Set the new front to be the next node
				m_front = current->next;
				m_front->prev = nullptr;

				// Move to the next node
				current = current->next;

				// delete the node
				delete(nodeToBeDeleted);
			}
			else if (current == m_back)
			{
				// Set the node to be deleted to the current one.
				nodeToBeDeleted = current;
				
				// Set the new back to be the prev node
				m_back = current->prev;
				m_back->next = nullptr;

				// delete the node
				delete(nodeToBeDeleted);

				// End search
				current = nullptr;
			}
			else
			{
				// Set the node to be deleted to the current one.
				nodeToBeDeleted = current;

				// Change the links of the nodes
				current->prev->next = current->next;
				current->next->prev = current->prev;

				// Move to the next node
				current = current->next;

				// delete the node
				delete(nodeToBeDeleted);
			}
		}
		else 
		{
			// Move to the next node
			current = current->next;
		}
	}

	// Set the selected node to be the front node
	m_selected = m_front;
}

//----------------------------------
// Remove the last node of the list.
//----------------------------------
void DoubleLinkedList::popBack()
{
	// get the last node
	struct node* lastNode = m_back;

	// The previous node will be last of list
	m_back = lastNode->prev;
	m_back->next = nullptr;

	// delete the last node
	delete(lastNode);

	// Set the selected node to be the front node
	m_selected = m_front;
}

//-----------------------------------
// Remove the first node of the list.
//-----------------------------------
void DoubleLinkedList::popFront()
{
	// get the first node
	struct node* firstNode = m_front;

	// The next node will be front of list
	m_front = firstNode->next;
	m_front->prev = nullptr;

	// delete the original first node
	delete(firstNode);

	// Set the selected node to be the front node
	m_selected = m_front;
}

//--------------------------------------------------------
// Checks if the list is empty.
//	return (bool): Returns whether a list is empty or not.
//--------------------------------------------------------
bool DoubleLinkedList::empty()
{
	if (m_front == nullptr && m_back == nullptr)
	{
		return true;
	}
	
	return false;
}

//------------------------------
// Remove all nodes in the list.
//------------------------------
void DoubleLinkedList::clear()
{
	// get the first node
	struct node* nodeToBeDeleted;
	struct node* current = m_front;
	
	// while the front does not equal null
	while (current != nullptr)
	{
		nodeToBeDeleted = current;
		
		// Move to the next node
		current = current->next;
		
		// If that node is null
		if (current != nullptr)
		{
			// Delete the link
			current->prev = nullptr;
		}

		// delete the original first node
		delete(nodeToBeDeleted);
	}

	// Set the selected node to be the front node
	m_front = nullptr;
	m_selected = m_front;
}

//----------------------------------
// Sort the list in ascending order.
//----------------------------------
void DoubleLinkedList::sort()
{
	struct node* current;
	struct node* next;

	// Get the size of the list
	int size = count();

	// So far the list is not sorted
	bool sorted = false;
	while (!sorted)
	{
		// Now say that it is sorted
		sorted = true;

		// Starting from the first node
		current = m_front;
		next = current->next;

		// Go through the list
		for (int i = 0; i < size; i++)
		{
			// If the next node is not empty
			if (next != nullptr)
			{
				// And the current data is greater than the next nodes data
				if (current->data > next->data)
				{
					// The list is not sorted
					sorted = false;
					
					// If the current node is the first node
					if (current == m_front)
					{
						// Switch the nodes by switching thier links
						current->next = next->next;
						next->prev = current->prev;
						next->next->prev = current;

						current->prev = next;
						next->next = current;

						// Set the front node to be the next node
						m_front = next;

						// Move to the next node
						next = next->next->next;
					}

					// If the next node is the last node
					else if (next == m_back)
					{
						// Switch the nodes by switching thier links
						current->next = next->next;
						next->prev = current->prev;
						current->prev->next = next;

						current->prev = next;
						next->next = current;

						// Set the back node to be the current node
						m_back = current;

						// Move to the next node
						next = next->next;
					}
					else
					{
						// Switch the nodes by switching thier links
						current->next = next->next;
						next->prev = current->prev;
						current->prev->next = next;
						next->next->prev = current;

						current->prev = next;
						next->next = current;

						// Move to the next node
						next = next->next;
					}
				}
				else
				{
					// Move to the next node
					current = next;
					next = next->next;
				}
			}
		}
	}
}

//-----------------------------------
// Move to the next node on the list.
//-----------------------------------
void DoubleLinkedList::moveToNext()
{
	if (m_selected->next != nullptr)
	{
		m_selected = m_selected->next;
	}
}

//---------------------------------------
// Move to the previous node on the list.
//---------------------------------------
void DoubleLinkedList::moveToPrev()
{
	if (m_selected->prev != nullptr)
	{
		m_selected = m_selected->prev;
	}
}

//---------------------------------------------------
// Get the value of the next node.
//	return (int): Returns the value of the next node.
//---------------------------------------------------
int DoubleLinkedList::getNextValue()
{
	if (m_selected != nullptr && m_selected->next != nullptr)
	{
		return m_selected->next->data;
	}
	
	return NULL;
}

//-------------------------------------------------------
// Get the value of the previous node. 
//	return (int): Returns the value of the previous node.
//-------------------------------------------------------
int DoubleLinkedList::getPrevValue()
{
	if (m_selected != nullptr && m_selected->prev != nullptr)
	{
		return m_selected->prev->data;
	}
	return NULL;
}