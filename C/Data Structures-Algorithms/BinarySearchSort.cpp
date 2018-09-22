// Lab2_BinarySearchSort.cpp
// Implemented an insertion sort and binary search algorithm on a doubly linked list.

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
#include <string>

using namespace std;

// Generic ListInterface Class
template <typename T>
class ListInterface
{
public:

	// pure virtual functions
	virtual bool isEmpty() = 0;
	virtual bool add(T newEntry) = 0;
	virtual bool remove(T anEntry) = 0;
	virtual void clear() = 0;
	virtual bool search(T anEntry) = 0;
	virtual void output() =0;

};

// Generic Node Class
template <typename T>
class Node
{
public:
	T item;
	Node<T> *prev; // prev node
	Node<T> *next; // next node

	Node<T> () { prev = nullptr; next = nullptr; item = 0; }; // Default Constructor
	Node<T> (T d) { prev = nullptr; next = nullptr; item = d; }; 

};

// Generic Doubly Linked List Class
template <typename T>
class DList : public ListInterface<T>
{
public:
	Node<T> *head;
	int itemCount;

	DList () { head = nullptr; itemCount=0; }; // Default Constructor

	// Checks to see if the list is empty or not
	bool isEmpty()
	{
		// Check to see if the list is empty. Can be done in (2) ways
		// (1) if head node is NULL, or (2) the itemCount is 0

		if (head == nullptr && itemCount==0) {
		//if (itemCount==0){
			//cout << "This is currently empty" << endl;
			return true;
		}
		else {

			//cout << "This is no longer empty" << endl;
			return false;
		}
		
	};

		// Add an item to the list
	bool add(T newEntry) 
	{
		// Create a new node for this newEntry called Ndata
		Node<T> *Ndata = new Node<T> (newEntry);

		if (head==nullptr && itemCount==0){
			
			// This case is for an empty list
			head = Ndata; //initialize the head to Ndata.
			itemCount = itemCount+1; // Increase the itemCount by 1
			return true;
		}

		else {

			// For an existing list, we need to point the prev of Ndata to the current head
			// Then move the head of this list to Ndata and increase the itemCount.

			Ndata->prev = head; 
			head->next = Ndata;

			head = Ndata;
			itemCount = itemCount+1;
			return true;
		}

	};

		// Removes a specified entry in the list
	bool remove(T anEntry) 
	{
		// We will search the list by starting at the head and moving through the
		// previous nodes of the list until it we find our desired node to remove.

		Node<T> *RemoveMe = head; // Our starting Node, which traverses the list
		Node<T> *PNode = head; // keeps track of the previous node before RemoveMe.
		Node<T> *SNode = head->prev; // keeps track of succeeding node after RemoveMe


		while (RemoveMe->item != anEntry && RemoveMe!=nullptr && SNode!=nullptr) { // while loop to find the desired node.
			PNode = RemoveMe;
			RemoveMe = RemoveMe->prev;
			SNode = RemoveMe->prev;
		};
	
		// Makes sure that our desired node is found. 
		// Makes sure that our desired node is found. 
		if (PNode != nullptr && RemoveMe!=PNode && SNode!=nullptr) {

		//
			PNode->prev = SNode;
			SNode->next = PNode;

			itemCount = itemCount-1;

			return true;
		}
		
		// If the removed node is the head node, we need to move the head.
		if (PNode!= nullptr && RemoveMe == PNode) {

			Node<T> *NewHead = SNode;

			NewHead->next = nullptr; 
			head = NewHead;

			
			itemCount = itemCount-1;

			return true;
		}

		if (SNode == nullptr) { // this is the end of the list and needs to be removed.
		
			PNode->prev = nullptr;

			itemCount = itemCount-1;
			return true;
		}
		
		return true;
	};

	// Find a specifed entry of the list
	bool search(T anEntry) 
	{
		Node<T> *FindMe = head;

		while (FindMe->item != anEntry && FindMe != nullptr) {
			FindMe = FindMe->prev;
		};

		if (FindMe!=nullptr) {
			//cout << "The word " << FindMe->item << " is in this list" << endl;
			return true;
			
		}

		else {
			return false;
		}	
	};

	// Prints the contents of the list.
	void output()
	{
		Node<T> *PrintMe = head;
	
		while(PrintMe != nullptr) {
			cout << PrintMe->item << '\t';
			PrintMe = PrintMe->prev;
		}
		
	};

	// Deletes the contents of the list
	void clear() 
	{
		Node<T> *DeleteMe = head;

		// Traverses through the list and deleting memory of all nodes
		// Starts at the head of the list

		while (DeleteMe!= nullptr) {

			DeleteMe = head->prev;
			delete head;
			head = DeleteMe;

		}

		// set the itemCount back to 0
		itemCount = 0;
	};

	// Insertion Sort function: InsertionSort()
	// Implements the Insertion sort algorithm.
	// Given the size of the doubly linked list, this algorithm sorts the values in ascending order, 
	// starting from the head. It actually removes the larger node and inserts a new one in the 
	// correct place. Derived from algorithm in textbook.

	// For example,
	//	head -> 1, 2, 3, 4, ..., 5 <- end of list
	void InsertionSort(int size) 
	{
		int i = 0;
		int j = 0;
		
		Node<T> *CompNode = head;
		Node<T> *SwapNode = head->prev;

		for (i = 1; i < size; ++i) {

			j = i;
			
			while (j>0 && SwapNode->item < CompNode->item && SwapNode != nullptr ) {
				Node<T> * Temp = new Node<T> (CompNode->item);
				remove(CompNode->item);

				if (SwapNode->prev != nullptr) {

					SwapNode->prev->next = Temp;
					Temp->prev = SwapNode->prev;
					Temp->next = SwapNode;
					SwapNode->prev = Temp;
				}

				else {

					SwapNode->prev = Temp;
					Temp->next = SwapNode;
				}

				--j;
				CompNode = SwapNode->next;
			}

			if (SwapNode->prev!=nullptr) {
				CompNode = SwapNode;
				SwapNode = SwapNode->prev;
			}

			i = j;
		}

	}

	// Function: Middle()
	// Implemented to find the item of the middle most node for the binary search
	// Can actually be used to find any node, if given the index
	T Middle(int mid) {

		Node<T> *Middle = head;
		for (int i=0; i<mid; i++) {
			Middle = Middle->prev;
		}
		return Middle->item;
	};

	// BinarySearch()
	// Implements the binary search algorithm, takes in list size and key to search for.
	// Follows from algorithm in textbook.
	int BinarySearch(int size, T key) {

		int mid = 0;
		int low = 0;
		int high = size-1;

		while (high>=low) {

			mid = (high+low)/2;
			T mid_item = Middle(mid);

			if (mid_item < key) {
				low = mid+1;
			}

			else if (mid_item > key) {
				high = mid-1;

			}

			else {
				cout << mid_item << " is found!" << endl;
				return 1;
			}

		}

		cout << key << " cannot be found." << endl;
		return -1;
	}

};

int main() 
{
	DList<string> MyStringlist;
	DList<int>  MyIntlist;

	ifstream TextFile("Words.txt"); // Input name of file for text
	ifstream NumberFile("Numbers.txt"); // Input name of file for numbers

	string word;
	int num;

	//cout << "Now begins my Doubly Linked list demonstration!"<< endl;
	if(MyStringlist.isEmpty()==true && MyIntlist.isEmpty()==true) {cout << "We currently have empty lists" << endl; };
	
	cout << "Adding words to MyStringList and Numbers to MyIntlist!" << endl;
	
	if (NumberFile.is_open()){
		
		while (NumberFile>>num) {
			
			MyIntlist.add(num);
		}

		NumberFile.close();
	}

	if (TextFile.is_open()){

		while (getline(TextFile,word)){

			// The following lines remove whitespaces, for strings only
			istringstream WordStream (word);
			WordStream >> noskipws;
			WordStream >> word >> ws;

			// add these words into my list
			MyStringlist.add(word);
		}

		TextFile.close();
	}

	cout << "Here is my unsorted Integer list: " << '\n' << endl;
	MyIntlist.output();
	cout << '\n' << endl;
	int NumItems = MyIntlist.itemCount;
	MyIntlist.InsertionSort(NumItems);
	cout << "Here is my sorted Integer list: " << '\n' << endl;
	MyIntlist.output();
	cout << '\n' << endl;
	MyIntlist.BinarySearch(NumItems, 32312);
	MyIntlist.BinarySearch(NumItems, 15);

	cout << '\n' << endl;
	cout << "Here is my unsorted list of strings: " << '\n' << endl;
	MyStringlist.output();
	cout << '\n' << endl;
	int StringItems = MyStringlist.itemCount;
	MyStringlist.InsertionSort(StringItems);
	cout << "Here is my sorted list of strings: " << '\n' << endl;
	MyStringlist.output();
	cout << '\n' << endl;
	MyStringlist.BinarySearch(StringItems, "calling");
	MyStringlist.BinarySearch(StringItems, "hello");

	return 0;
}

