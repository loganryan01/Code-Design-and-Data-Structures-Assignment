/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

class BinaryTree
{
public:
	// Default constructor
	BinaryTree();

	// Default destructor
	~BinaryTree();

	// Check if the tree is empty.
	bool IsEmpty() const;

	// Insert a new element into the tree.
	void Insert(int a_nValue);

	// Remove a node by value.
	void Remove(int a_nValue);

	// Find the node by value.
	TreeNode* Find(int a_nValue);

	// Get the Minimum Value Node
	TreeNode* MinValueNode(TreeNode* node);

	void PrintOrdered();
	void PrintUnordered();

	// Draw the node
	void Draw(TreeNode* selected = nullptr);

private:
	//Find the node with the specified value.
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);

	//Used to recurse through the nodes in value order and print their values.
	void PrintOrderedRecurse(TreeNode*);
	void PrintUnorderedRecurse(TreeNode*);

	// Draw the children of the node
	void Draw(TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	//The root node of the tree
	TreeNode* m_pRoot;
};

#endif //_BINARYTREE_H_