// Lab6_TreeBalancing.cpp

// Given a degenerate tree, we are asked to perform 'in place' rotations to construct a complete tree.

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

template <typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;
	int height;

	TreeNode() { left = nullptr; right = nullptr; data = 0; };
	TreeNode(T t) { left = nullptr; right = nullptr; data = t; };
};


template <typename T>
class BinaryTree
{
public:

	int TreeSize;
	TreeNode<T> *root;

	BinaryTree() { root = nullptr; TreeSize = 0; };
	BinaryTree(T d) { Insert(d); };

	int getHeight(TreeNode<T>* Node) 
	{
		int h = 0;
		if (Node != nullptr) {
			int l_height = getHeight(Node->left);
			int r_height = getHeight(Node->right);
			int max_height = max(l_height, r_height);
			h = max_height+1;
		}

		return h;
	}

	int BalanceFactor(TreeNode<T>* Node) 
	{

		int l_height = getHeight(Node->left);
		int r_height = getHeight(Node->right);
		int BFactor = l_height - r_height;

		return BFactor;
	}

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

			else if ( d > StartNode->data){

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

	void inOrderRecursive (TreeNode<T>* Tree) 
	{
		if (Tree == nullptr){return;}
		inOrderRecursive(Tree->left);
		parent(Tree);
		cout << Tree->data << endl;
		inOrderRecursive(Tree->right);

	}

	void PreOrderRecursive (TreeNode<T>* Tree) 
	{
		if (Tree == nullptr){return;}
		parent(Tree);
		cout << Tree->data << endl;
		PreOrderRecursive(Tree->left);
		PreOrderRecursive(Tree->right);

	}

	void PostOrderRecursive (TreeNode<T>* Tree) 
	{
		if (Tree == nullptr){return;}
		PostOrderRecursive(Tree->left);
		PostOrderRecursive(Tree->right);
		parent(Tree);
		cout << Tree->data << endl;

	}

	TreeNode<T>* findMiddleNode()
	{
		//int m = TreeSize/2;
		int m = 0;
		TreeNode<T>* Rover = root;
		if (Rover->right == nullptr){

			while (Rover != nullptr) {
				Rover = Rover->left;
				m++;
			}
		}

		else {

			while (Rover != nullptr) {
				Rover = Rover->right;
				m++;
			}
		}

		m = m/2;
		
		TreeNode<T> *Middle = root;
		if (Middle->left == nullptr) {
			for (int i = 0; i < m; i++) {
				//Middle->left = Middle->right;
				Middle = Middle->right;
			}
		}

		else {
			for (int i = 0; i < m; i++) {
				Middle = Middle->left;
			}
		}

		return Middle;

	};

	void CreateSplayTree(TreeNode<T>* Middle)
	{
		//TreeNode<T> *Root = root;
		int m = (TreeSize)/2;

		if (Middle->left == nullptr) {

			for (int i = 0; i < m; i++) {
				RR_Rotation(root, root);
			}
		}

		else {

			for (int i = 0; i < m; i++) {
				LL_Rotation(root, root);
			}
		}

	}

	TreeNode<T>* RR_Rotation(TreeNode<T>* Parent, TreeNode<T>* Root)
	{
		TreeNode<T>* RotateMe = Parent->right;
		Parent->right = RotateMe->left;
		RotateMe->left = Parent;

		if (Parent == root) {
			//root = RotateMe;
			root = RotateMe;
		}

		else if (Parent == Root->right) {
			Root->right = RotateMe;
		}

		else if (Parent == Root->left){
			Root->left = RotateMe;
		}

		else if (Parent == Root) {
			Root = RotateMe;
		}

		return RotateMe;

	}

	TreeNode<T>* LL_Rotation(TreeNode<T>* Parent, TreeNode<T>* Root)
	{

		TreeNode<T>* RotateMe = Parent->left;
		Parent->left = RotateMe->right;
		RotateMe->right = Parent;

		if (Parent == root) {
			root = RotateMe;
		}
		else if (Parent == Root->right) {
			Root->right = RotateMe;
		}

		else if (Parent == Root->left){
			Root->left = RotateMe;
		}

		else if (Parent == Root) {
			Root = RotateMe;
		}

		return RotateMe;
	}

	TreeNode<T>* LR_Rotation(TreeNode<T>* Parent, TreeNode<T>* Root)
	{
		TreeNode<T> *RotateMe = Parent->left;
		Parent->left = RR_Rotation(RotateMe, Root);
		return LL_Rotation(Parent, Root);
	}

	TreeNode<T>* RL_Rotation(TreeNode<T>* Parent, TreeNode<T>* Root) 
	{
		TreeNode<T> *RotateMe = Parent->right;
		Parent->right = LL_Rotation(RotateMe, Root);
		return RR_Rotation(Parent, Root);
	}

	TreeNode<T>* Balance(TreeNode<T>* Node, TreeNode<T>* Root)
	{
		int BF = BalanceFactor(Node);

		if (BF > 1) {

			if (BalanceFactor(Node->left) > 0){
				Node = LL_Rotation(Node, Root);
			}
			else {
				Node = LR_Rotation(Node, Root);
			}
		}

		else if (BF < -1) {

			if (BalanceFactor(Node->right) > 0){
				Node = RL_Rotation(Node, Root);
			}

			else {
				Node = RR_Rotation(Node, Root);
			}
		}

		return Node;

	}

	void AVLTree( TreeNode<T>* TreeRoot)
	{
		TreeNode<T> *Rover = TreeRoot->left;
		TreeNode<T> *TempNode = Rover->left;
		int Flag = 0;

		while ( Rover != nullptr ){

			if (abs(BalanceFactor(Rover)) > 1){
				Balance(Rover, TreeRoot);
			}

			Rover = TempNode;
			TempNode = TreeRoot->left->left;

			if (abs(BalanceFactor(Rover)) < 2) {

				int BH = abs(BalanceFactor(Rover->left));
				if (BH > 1) {Flag++; }
				break;
				
			}
			
		}

		Rover = TreeRoot->right;
		TempNode = Rover->right;

		while ( Rover != nullptr ) {
			if (abs(BalanceFactor(Rover)) > 1){
				Balance(Rover, TreeRoot);
			}

			Rover = TempNode;
			TempNode = TreeRoot->right->right;

			if (abs(BalanceFactor(Rover)) < 2 ) {

				int BH = abs(BalanceFactor(Rover->right));
				if (BH > 1) {Flag++;}
				break;
				
			}
		}


		if (Flag > 0) {

	 		AVLTree(TreeRoot->left);
			AVLTree(TreeRoot->right);
		}
		

	}
};

int main()
{
	BinaryTree<int> MyBinTree;

	ifstream NumberFile("Test_Num.txt");
	int num;
	int Treecount = 0;

	if (NumberFile.is_open()) {

		while (NumberFile >> num) {
			MyBinTree.Insert(num);
		}

		NumberFile.close();

	}
	cout << Treecount << endl;
	cout << '\n' << endl;
	cout << "----- Degenerate Tree ----- " << endl;

	
	MyBinTree.inOrderRecursive(MyBinTree.root);

	cout << "Items in tree " << MyBinTree.TreeSize << endl;
	//cout << MyBinTree.findMiddleNode()->data << endl;
	cout << '\n' << endl;
	MyBinTree.CreateSplayTree(MyBinTree.findMiddleNode());

	cout << "----- Splay Tree ----- " << endl;
	MyBinTree.inOrderRecursive(MyBinTree.root);
	cout << '\n' << endl;
	cout << '\n' << endl;

	MyBinTree.AVLTree(MyBinTree.root);

	cout << "----- Rotated Tree ----- " << endl;
	MyBinTree.inOrderRecursive(MyBinTree.root);

	cout << '\n' << endl;
	cout << '\n' << endl;

	system("pause");

	return 0;
};

