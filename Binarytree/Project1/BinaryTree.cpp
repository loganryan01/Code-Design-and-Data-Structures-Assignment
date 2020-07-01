/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//---------------------
// Default Constructor.
//---------------------
BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

//--------------------
// Default Destructor.
//--------------------
BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

//----------------------------------------------------------------
// Check if the tree is empty.
//	return (bool): Returns true if there are no nodes in the tree.
//----------------------------------------------------------------
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

//-------------------------------------------------------------------------------
// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
//	a_nValue (int): What value will be in the node?
//-------------------------------------------------------------------------------
void BinaryTree::Insert(int a_nValue)
{
	// Create a new node
	TreeNode* newNode = new TreeNode(a_nValue);
	
	// If the tree is empty,
	if (IsEmpty())
	{
		// Set the root to equal the node
		m_pRoot = newNode;
		return;
	}

	// Otherwise, recur down the tree
	TreeNode* pCurrent = m_pRoot;
	TreeNode* pParent = nullptr;

	// While the current node does not equal null
	while (pCurrent != nullptr)
	{
		// The parent node becomes the current node.
		pParent = pCurrent;

		// If the value is less than the current nodes data
		if (a_nValue < pCurrent->GetData())
		{
			// The current node becomes the left child of the current node
			pCurrent = pCurrent->GetLeft();

			// If that child is null
			if (pCurrent == nullptr)
			{
				// Place the new node in the current node position
				pCurrent = newNode;

				// Connect the parent node to the new node
				pParent->SetLeft(pCurrent);

				// Exit the function
				return;
			}
		}
		else if (a_nValue == pCurrent->GetData())
		{
			// If the value already exists in the tree,
			// Exit the function
			break;
		}
		else
		{
			// The current node becomes the right child of the current node
			pCurrent = pCurrent->GetRight();

			// If that child is null
			if (pCurrent == nullptr)
			{
				// Place the new node in the current node position
				pCurrent = newNode;

				// Connect the parent node to the new node
				pParent->SetRight(pCurrent);
				
				// Exit the function
				break;
			}
		}
	}
}

//------------------------------------------------------------
// Find the node by value.
//	a_nValue (int): What is the value that we are looking for?
//	return (TreeNode*): Returns the node and its parent.
//------------------------------------------------------------
TreeNode* BinaryTree::Find(int a_nValue)
{
	// The current node
	TreeNode* pCurrent = nullptr;

	// The parent node of the current node
	TreeNode* pParent = nullptr;

	// Return the node
	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

//------------------------------------------------------------------------------------------------------------
// Find a node and its parent by searching by value.
//	a_nSearchValue (int): What is the value that we are looking for?
//	ppOutNode (TreeNode*&): The node that we are looking for?
//	ppOutParent (TreeNode*&): The parent of the node that we are looking for?
//	return (bool): Returns the node and its parent if it has been found, or return false if it doesn't exists.
//------------------------------------------------------------------------------------------------------------
bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	// Starting from the root of the tree
	ppOutNode = m_pRoot;
	ppOutParent = nullptr;

	// Go through the whole tree
	while (ppOutNode != nullptr)
	{
		// If the node has been found
		if (a_nSearchValue == ppOutNode->GetData())
		{
			// Return the node and its parent
			return (ppOutNode && ppOutParent);
		}
		else
		{
			// The parent becomes the current node
			ppOutParent = ppOutNode;
			
			// If the search value is less than the current node's value
			if (a_nSearchValue < ppOutNode->GetData())
			{
				// The current node becomes its left child
				ppOutNode = ppOutNode->GetLeft();
			}
			else
			{
				// The current node becomes its right child
				ppOutNode = ppOutNode->GetRight();
			}
		}
	}

	// If the node does not exists, return false
	return false;
}

//---------------------------------------------------------
// Remove a node by value.
//	a_nValue (int): What is the value that we are removing.
//---------------------------------------------------------
void BinaryTree::Remove(int a_nValue)
{
	// Find the value in the tree, obtaining a pointer to the node and its parent
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	FindNode(a_nValue, pCurrent, pParent);

	// If the current node is the left child of the parent node
	if (pParent != nullptr && pParent->GetLeft() == pCurrent)
	{
		// If there is no left child for the current node then get the right child
		if (pCurrent->GetLeft() == nullptr)
		{
			// Set the left child of the parent to the current nodes right child
			pParent->SetLeft(pCurrent->GetRight());
		}
		else
		{
			// Set the left child of the parent to the current nodes left child
			pParent->SetLeft(pCurrent->GetLeft());

			// Set the right grandchild of the parent node to be the current nodes right child
			pParent->GetLeft()->SetRight(pCurrent->GetRight());
		}
	}
	// If the current node is the right child
	else if (pParent != nullptr && pParent->GetRight() == pCurrent)
	{
		// If there is no right child for the current node then get the left child
		if (pCurrent->GetRight() == nullptr)
		{
			// Set the right child of the parent to the current nodes left child
			pParent->SetRight(pCurrent->GetLeft());
		}
		else
		{
			// Set the right child of the parent to the current nodes right child
			pParent->SetRight(pCurrent->GetRight());

			// Set the left grandchild of the parent node to be the current nodes left child
			pParent->GetRight()->SetLeft(pCurrent->GetLeft());
		}
	}
	// If the current node is the root of the tree
	else if (pCurrent == m_pRoot)
	{
		// If the root has two children
		if (pCurrent->GetRight() != nullptr && pCurrent->GetLeft() != nullptr)
		{
			// Get the inorder successor 
			TreeNode* inorderSuccessor = MinValueNode(m_pRoot->GetRight());

			// Set the current node to be the inorder successor
			FindNode(inorderSuccessor->GetData(), pCurrent, pParent);

			// Set the root's data to be the inorder successor
			m_pRoot->SetData(inorderSuccessor->GetData());

			// If the current node is the parents left child
			if (pParent->GetLeft() == pCurrent)
			{
				// Set the left child of the parent node to be nullptr
				pParent->SetLeft(nullptr);
			}
			// If the right child of the root is the node to be deleted
			else if (m_pRoot->GetRight() == pCurrent)
			{
				// Set the right child to be the current node's right child
				m_pRoot->SetRight(pCurrent->GetRight());
			}
		}
		// If the root has a right child
		else if (pCurrent->GetRight() != nullptr && pCurrent->GetLeft() == nullptr)
		{
			// Set the root to be the right child
			m_pRoot = pCurrent->GetRight();
		}
		// If the root has a left child
		else if (pCurrent->GetRight() == nullptr && pCurrent->GetLeft() != nullptr)
		{
			// Set the root to be the left child
			m_pRoot = pCurrent->GetLeft();
		}
		// If the root has no children
		else if (pCurrent->GetRight() == nullptr && pCurrent->GetLeft() == nullptr)
		{
			// Set the root to be null
			m_pRoot = nullptr;
		}
	}

	// Delete the chosen node
	pCurrent->SetLeft(nullptr);
	pCurrent->SetRight(nullptr);
	delete pCurrent;
}

//-----------------------------------
// Print the binary tree in preorder.
//-----------------------------------
void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

//-----------------------------------------------------
// Print the binary tree in preorder.
//	pNode (TreeNode*): Which node are we starting from?
//-----------------------------------------------------
void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{
	if (pNode == NULL)
		return;

	// first print data of node 
	cout << pNode->GetData() << " ";

	// then recur on left subtree 
	PrintOrderedRecurse(pNode->GetLeft());

	// now recur on right subtree 
	PrintOrderedRecurse(pNode->GetRight());
}

//----------------------------------
// Print the binary tree in inorder.
//----------------------------------
void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

//-----------------------------------------------------
// Print the binary tree in inorder.
//	pNode (TreeNode*): Which node are we starting from?
//-----------------------------------------------------
void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{
	// If the node is empty
	if (pNode == nullptr)
		// Exit the function
		return;

	// First recur on left child
	PrintUnorderedRecurse(pNode->GetLeft());

	// Then print the data of node
	cout << pNode->GetData() << " ";

	// Now recur on right child
	PrintUnorderedRecurse(pNode->GetRight());
}

//--------------------------------------------------
// Find the minimum value of the tree.
//	node (TreeNode*): Which node are we starting on?
//--------------------------------------------------
TreeNode* BinaryTree::MinValueNode(TreeNode* node)
{
	TreeNode* current = node;

	// loop down to find the leftmost leaf.
	while (current && current->GetLeft() != nullptr)
		current = current->GetLeft();

	return current;
}

//---------------------------------------------------------
// Draw the branches for the tree.
//	selected (TreeNode*): Which node is currently selected?
//---------------------------------------------------------
void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

//------------------------------------------------------------------------------
// Draw the branches for the tree.
//	pNode (TreeNode*): Which node are we starting from?
//	x (int): What is the x position of the node?
//	y (int): What is the y position of the node?
//	horizontalSpacing (int): How much spacing should there be between the nodes?
//	selected (TreeNode*): Which node is currently selected?
//------------------------------------------------------------------------------
void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	// Half the spacing
	horizontalSpacing /= 2;

	// If there is a node
	if (pNode)
	{
		// If this node has a left child
		if (pNode->HasLeft())
		{
			// Draw a line to connect the nodes
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			// Draw the next branch
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// If this node has a right child
		if (pNode->HasRight())
		{
			// Draw a line to connect the nodes
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			// Draw the next branch
			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		// Draw the node
		pNode->Draw(x, y, (selected == pNode));
	}
}