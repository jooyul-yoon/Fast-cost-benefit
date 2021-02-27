#ifndef RBTREE_H
#define RBTREE_H

/** C++ implementation for
   Red-Black Tree Insertion
   This code is adopted from
   the code provided by
   Dinesh Khandelwal in comments **/

#include <iostream>
#include <queue>

using namespace std;

enum Color { RED, BLACK };

struct Node
{
	pair<uint32_t, float> data;
	bool color;
	Node *left, *right, *parent;

	// Constructor 
	Node(pair<uint32_t, float> data)
	{
		this->data = data;
		left = right = parent = nullptr;
		this->color = RED;
	}
};

// Class to represent Red-Black Tree 
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixViolation(Node *&, Node *&);
public:
	// Constructor 
	RBTree() { root = nullptr; }
	void insert(const pair<uint32_t, float> &n);
	void inorder();
	void levelOrder();
	vector<pair<uint32_t, float>> genList();
	pair<uint32_t, float > getMin();
	pair<uint32_t, float > extractMin();
};

// A recursive function to do inorder traversal 
void inorderHelper(Node *root)
{
	if (root == nullptr)
		return;
	inorderHelper(root->left);
	cout << "inorder " << root->data.second << endl;
	inorderHelper(root->right);
}

void listHelper(Node *root, vector<Node *>& nodes)
{
	if (root == nullptr)
		return;
	listHelper(root->left, nodes);
	nodes.push_back(root);
	// cout << root->data.second << endl;
	listHelper(root->right, nodes);
}


/* A utility function to insert
	a new node with given key
   in BST */
Node* BSTInsert(Node* root, Node *pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
		return pt;

	/* Otherwise, recur down the tree */
	if (pt->data.second <= root->data.second)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data.second > root->data.second)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal 
void levelOrderHelper(Node *root)
{
	if (root == NULL)
		return;

	queue<Node *> q;
	q.push(root);

	while (!q.empty())
	{
		Node *temp = q.front();
		cout << temp->data.second << "  ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations  
// caused by BST insertion 
void RBTree::fixViolation(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*  Case : A
			Parent of pt is left child
			of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left)
		{

			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			   The uncle of pt is also red
			   Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color ==
				RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				/* Case : 2
				   pt is right child of its parent
				   Left-rotation required */
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				   pt is left child of its parent
				   Right-rotation required */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color,
					grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		/* Case : B
		   Parent of pt is right child
		   of Grand-parent of pt */
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			/*  Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color ==
				RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				/* Case : 2
				   pt is left child of its parent
				   Right-rotation required */
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
				   pt is right child of its parent
				   Left-rotation required */
				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color,
					grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

// Function to insert a new node with given data 
void RBTree::insert(const pair<uint32_t, float> &data)
{
	Node *pt = new Node(data);

	// Do a normal BST insert 
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations 
	fixViolation(root, pt);
}

pair<uint32_t, float> RBTree::extractMin()
{
	Node* minNode = root;
	Node *parent_pt = NULL;

	if (root->left == nullptr && root->right == nullptr) {
		pair<uint32_t, float> temp = root->data;
		root = NULL;
		return temp;
	}

	while (minNode->left != nullptr) {
		parent_pt = minNode;
		minNode = minNode->left;
		parent_pt = minNode->parent;
		// cout << "parent : " << minNode->parent->data.second << endl;
		// cout << "minNode: " << minNode->data.second << endl;
	}
	

	// Case A: No Child
	if (minNode->right == nullptr) {
		// cout << "No Child" << endl;
		minNode->parent->left = nullptr;
	}

	// Case B: Child exist
	else {
		// cout << "Yes Child" << endl;
		if (minNode->color == 0) {
			Node* rightChild = minNode->left;
			minNode->parent->left = rightChild;
			rightChild->color = minNode->color;
		}
	}

	return minNode->data;
}

// Function to do inorder and level order traversals 
void RBTree::inorder() { inorderHelper(root);}
void RBTree::levelOrder() { levelOrderHelper(root); }

vector<pair<uint32_t, float>> RBTree::genList() {
	vector<Node *> nodes;
	vector<pair<uint32_t, float>> weight;
	listHelper(root, nodes);
	for (auto a : nodes) {
		weight.push_back(a->data);
		// cout << a->data.first << endl;
	}
	
	return weight;	
}

pair<uint32_t, float > RBTree::getMin() {
	Node* current = root;
	while (current->left != nullptr)
		current = current->left;

	return current->data;
}

#endif