// Lab3_RadixSort.cpp

// Using our Doubly Linked List to create an array of doubly-linked list and should be size 10 in length.
// The 10 positions in the array of the linked list are used for each base 10 radix. 0-9.
// Use Numbers.txt
// Is it possible to make it work for strings?

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

	Node<T> () { prev = NULL; next = NULL; item = 0; }; // Default Constructor
	Node<T> (T d) { prev = NULL; next = NULL; item = d; }; 

};

// Generic Doubly Linked List Class
template <typename T>
class DList : public ListInterface<T>
{
public:
	Node<T> *head;
	int itemCount;

	DList () { head = NULL; itemCount=0; }; // Default Constructor

	// Checks to see if the list is empty or not
	bool isEmpty()
	{
		// Check to see if the list is empty. Can be done in (2) ways
		// (1) if head node is NULL, or (2) the itemCount is 0
		if (head == NULL && itemCount==0) {
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

		if (head==NULL && itemCount==0){
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

		Node<T> *CurNode = head; // Our Current Node, which traverses the list
		Node<T> *PNode = head; // keeps track of the previous node before RemoveMe.
		Node<T> *SNode = head->prev; // keeps track of succeeding node after RemoveMe


		while (CurNode->item != anEntry && CurNode!=NULL && SNode!=NULL) { // while loop to find the desired node.
			PNode = CurNode;
			CurNode = CurNode->prev;
			SNode = CurNode->prev;
		};
	
		// Makes sure that our desired node is found. 
		if (PNode != NULL && CurNode!=PNode && SNode!=NULL) {

			Node<T> *RemoveMe = CurNode;
			PNode->prev = SNode;
			SNode->next = PNode;
			delete RemoveMe;
			itemCount = itemCount-1;
			return true;
		}
		
		// If the removed node is the head node, we need to move the head.
		if (CurNode == head) {

			Node<T> *RemoveMe = CurNode;
			SNode->next = nullptr;
			head = SNode;
			delete RemoveMe;
			itemCount = itemCount-1;
			return true;
		}

		if (SNode == NULL) { // this is the end of the list and needs to be removed.
		
			Node<T> *RemoveMe = CurNode;
			PNode->prev = NULL;
			delete RemoveMe;
			itemCount = itemCount-1;
			return true;
		}
		
		return true;
	};

	// Find a specifed entry of the list
	bool search(T anEntry) 
	{
		Node<T> *FindMe = head;

		while (FindMe->item != anEntry && FindMe != NULL) {
			FindMe = FindMe->prev;
		};

		if (FindMe!=NULL) {
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
	
		while(PrintMe != NULL) {
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
		while (DeleteMe!= NULL) {

			DeleteMe = head->prev;
			delete head;
			head = DeleteMe;
		}
		
		// set the itemCount back to 0
		itemCount = 0;
	};

// Same Implementation as textbook
	int Integer_RadixMaxLength() 
	{
		int maxDigits = 0;
		Node<T> *Head = head;

		for (int i = 0; i < this->itemCount; i++) {
			int digitCount = Integer_RadixGetLength(Head->item);
			Head = Head->prev;
			if (digitCount > maxDigits) {
				maxDigits = digitCount;
			}
		}

		return maxDigits;
		
	}

// Same implementation as textbook
	int Integer_RadixGetLength(T value) {

		if (value==0) {
			return 1;
		}

		int digits = 0;

		while (value!=0) {
			digits = digits+1;
			value = value/10;
		}

		return digits;
	}

	// Radix sort algorithm
	// based on Zybook Implementation
	// template typename<T>

	void Integer_RadixSort() 
	{
		// make a new list for the rebuilding
		DList<int> TempList;
		DList<int> Dlistarray[10];

		int maxDigits = this->Integer_RadixMaxLength();
		int pow10 = 1; // start with 1's place

		Node<T> *StartNode = this->head;

		for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {

			//TempList.clear();
			while (StartNode!=nullptr) {

				int bucketIndex = abs(StartNode->item/pow10) % 10;
				//cout << StartNode->item << "digitIndex: " << digitIndex << endl;
					Dlistarray[bucketIndex].add(StartNode->item);
					StartNode = StartNode->prev;
			}

			TempList.clear();
			for (int i = 0; i <10; i++) {

				if (!Dlistarray[i].isEmpty()) {
					Node<T> *ArrayHead = Dlistarray[i].head;

					while (ArrayHead!=nullptr) {
						
						TempList.add(ArrayHead->item);
						//cout << ArrayHead->item;
						ArrayHead = ArrayHead->prev;

					}
					
					Dlistarray[i].clear();
				}

			}
			
			StartNode = TempList.head;
			pow10 = 10*pow10;

		}

		TempList.output();
	}

};


int main() {

	DList<int> MyIntlist;
	
	ifstream NumberFile("Numbers.txt"); // Input name of file for numbers
	int num;

	if (NumberFile.is_open()){
		
		while (NumberFile>>num) {
			
			MyIntlist.add(num);
		}

		NumberFile.close();
	}
	
	MyIntlist.Integer_RadixSort();

	return 0;
}