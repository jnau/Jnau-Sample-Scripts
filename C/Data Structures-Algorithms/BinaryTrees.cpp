// BinaryTree.cpp

// We are told to convert the TreeArray C++ source code into a binary tree using the specifed TreeNode definition.
// Also, we are asked to implement iterative versions of the Preorder, Postorder, and Inorder traversals for this binary tree.

// Use of Doubly Linked List to create Stacks in order to traverse binary tree

// Name: Jessica Au
// CWID: 20161910

#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <cmath>

using namespace std;

// Implementation of stack 

template <typename T>
class StackNode
{
public:
	T item;
	StackNode<T> *prev;

	StackNode() { prev = nullptr; item = 0; };
	StackNode(T t) { prev = nullptr; item = t; };
};

template<typename T>
class Stack
{
public:
	int itemCount;
	StackNode<T> *top;

	Stack() { top = nullptr; itemCount = 0; };
	Stack(T t) { Push(t); };

	void Push(T anEntry)
	{
		StackNode<T> *Ndata = new StackNode<T>(anEntry);

		if (top == nullptr && itemCount == 0) {
			// This case is for an empty list
			top = Ndata; //initialize the head to Ndata.
			itemCount++; // Increase the itemCount by 1
		}

		else {

			Ndata->prev = top;
			top = Ndata;
			itemCount++;
		}

	}

	bool Pop()
	{
		if (itemCount>0) {

			T value = top->item;

			if (itemCount == 1) {

				// clear the stack
				T value = top->item;
				cout << value->data << endl;
				top = nullptr;
				itemCount = 0;
				return true;
			}

			else {

				cout << value->data << endl;
				StackNode<T> *RemoveMe = top;
				top = top->prev;
				delete RemoveMe;
				itemCount--;
				return true;
			}
		}

		else {
			return false;
		}

	};

	bool isEmpty()
	{
		if (top == nullptr) {
			return true;
		}

		else {
			return false;
		}

	};

	void Output()
	{
		StackNode<T> *Top = top;
		while (Top != nullptr) {

			cout << Top->item << endl;
			Top = Top->next;
		}

	};

	StackNode<T>* Peek()
	{
		if (top) {
			return top;
		}
		else {
			return 0;
		}
	};

};

template <typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;

	TreeNode() { left = nullptr; right = nullptr; data = 0; };
	TreeNode(T t) { left = nullptr; right = nullptr; data = t; };
};


template <typename T>
class BinaryTree
{
public:

	Stack<TreeNode<T>* > stack;
	int TreeSize;
	TreeNode<T> *root;

	BinaryTree() { root = nullptr; TreeSize = 0; };
	BinaryTree(T d) { Insert(d); };


	void Insert(T d)
	{
		TreeNode<T> *NewTdata = new TreeNode<T>(d);
		TreeNode<T> *StartNode = root;

		if (StartNode == nullptr) {

			root = NewTdata;
			cout << "The root: " << '\t' << root->data << '\n' << endl;
			TreeSize++;

		}

		else {

			//cout << "Starting from the root of the tree, " << endl;
			while (StartNode != nullptr) {

				if (StartNode->left != nullptr && d < StartNode->data) {

					StartNode = StartNode->left;
					//cout << "Move Left" << endl;
				}

				else if (StartNode->right != nullptr && d > StartNode->data) {

					StartNode = StartNode->right;
					//cout << "Move Right" << endl;
				}

				else {
					break;
				}
			}

			if (d < StartNode->data) {

				//cout << "Move Left" << endl;
				StartNode->left = NewTdata;
				TreeSize++;
				//cout << "Insertion of " << d << " to the left of " << StartNode->data << '\n' << endl;
			}

			else if ( d> StartNode->data){

				//cout << "Move Right" << endl;
				StartNode->right = NewTdata;
				TreeSize++;
				//cout << "Insertion of " << d << " to the right of " << StartNode->data << '\n' << endl;
			}
		}
	}

	// This Search Implementation returns how many edges away it is from the parent node.
	int Search(T anEntry)
	{
		TreeNode<T> *Search = root;
		int EdgesFromParent = 0;

		while (Search != nullptr && Search->data != anEntry) {

			if (anEntry < Search->data) {
				Search = Search->left;
				EdgesFromParent++;
			}

			else {
				Search = Search->right;
				EdgesFromParent++;

			}
		}

		if (Search != nullptr) {
			return EdgesFromParent;
		}

		else {
			EdgesFromParent = 0;
			return EdgesFromParent;
		}
	}

	void parent(TreeNode<T>* ChildNode) {

		int Edges = Search(ChildNode->data);

		for (int i = 0; i < Edges; i++) {
			cout << "|---";
		}

	}

	// Iterative version for the In Order traversal.
	// Should start from leftmost node of the tree and traverse through the list until the rightmost node of the tree.

	void inOrderIterative()
	{
		TreeNode<T> *StartNode = root;
		TreeNode<T> *TempNode;
		bool done = false;

		while (done == false) {
			while (StartNode != nullptr) {

				stack.Push(StartNode);
				StartNode = StartNode->left;

				while (StartNode == nullptr && (!stack.isEmpty())) {

					TempNode = stack.top->item->right;
					parent(stack.top->item);
					stack.Pop();
					StartNode = TempNode;
				}
			}

			done = true;
		}
	}

	// Iterative version of the Post Order Traversal.
	// Traverse through the left subtree, then right subtree for each node;

	void postOrderIterative()
	{
		TreeNode<T> *StartNode = root;
		TreeNode<T> *TempNode;
		bool done = false;

		while (done == false) {
			while (StartNode != nullptr || !stack.isEmpty()) {

				stack.Push(StartNode);
				StartNode = StartNode->left;

				while (StartNode == nullptr && !stack.isEmpty()) {

					TempNode = stack.top->item->right;

					if (TempNode == nullptr) {
						TempNode = stack.top->item;
						parent(TempNode);
						stack.Pop();

						while (!stack.isEmpty() && TempNode == stack.top->item->right) {
							TempNode = stack.top->item;
							parent(TempNode);
							stack.Pop();
						}
					}

					else {
						StartNode = TempNode;
					}
				}		
			}

			done = true;
		}
	}

	// Implementation of Iterative version of Pre Order Traversal
	// Print each node, then its left subtree and then its right subtree

	void preOrderIterative()
	{
		TreeNode<T> *StartNode = root;
		TreeNode<T> *TempLNode;
		TreeNode<T> *TempRNode;
		bool done = false;

		while (done == false) {
			while (StartNode != nullptr) {

				stack.Push(StartNode);
				TempLNode = stack.top->item->left;
				TempRNode = stack.top->item->right;

				while (stack.top!= nullptr) {
					
					parent(stack.top->item);
					stack.Pop();

					if (TempRNode != nullptr) {
						stack.Push(TempRNode);
					}

					if (TempLNode != nullptr) {
						stack.Push(TempLNode);
					}

					if (stack.top == nullptr) { StartNode = nullptr; break;  }
					StartNode = stack.top->item;
					TempLNode = stack.top->item->left;
					TempRNode = stack.top->item->right;
				}
			}

			done = true;
		}
	}
};

int main()
{
	BinaryTree<int> MyBinTree;

	ifstream NumberFile("Numbers.txt");
	int num;

	if (NumberFile.is_open()) {

		while (NumberFile >> num) {
			MyBinTree.Insert(num);
		}

		NumberFile.close();

	}

	int K = 59; // A number that is in the textfile
	int L = 13; // A number that is NOT in the textfile

	cout << "Searching for this number: " << K << endl;
	if (MyBinTree.Search(K) > 0) { cout << "Algorithm found the number, " << K << " in the tree."<< endl; }
	else { cout << K << " was not found in this tree." << endl; };

	cout << '\n' << endl;

	cout << "Searching for this number: " << L << endl;
	if (MyBinTree.Search(L) > 0) { cout << "Algorithm found the number, " << L << endl; }
	else { cout << L << " was not found in this tree." << endl; };

	cout << '\n' << endl;
	cout << "----- In Order Iterative Tree ----- " << endl;
	MyBinTree.inOrderIterative();
	cout << '\n' << endl;
	cout << '\n' << endl;
	cout << "----- Post Order Iterative Tree ----- " << endl;
	MyBinTree.postOrderIterative();
	cout << '\n' << endl;
	cout << '\n' << endl;
	cout << "----- Pre Order Iterative Tree ----- " << endl;
	MyBinTree.preOrderIterative();
	cout << '\n' << endl;
	cout << '\n' << endl;
	cout << "----- Complete ----- " << endl;

	//system("pause");

	return 0;
};

