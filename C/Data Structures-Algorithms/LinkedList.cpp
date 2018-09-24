// Lab0_LinkedList.cpp
// This script implements a singly linked list to store the data
// from a local Words.txt file. Both Node and List are generic classes.
// Main function not included.

// Jessica Au. CWID: 20161910 

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
class Listinterface
{
public:

	// pure virtual functions
	virtual bool isEmpty() = 0;
	virtual bool add(T newEntry) = 0;
	virtual bool remove(T anEntry) = 0;
	virtual void clear() = 0;
	virtual bool search(T anEntry) = 0;

};

// Generic Node Class
template <typename T>
class Node
{
public:
	T item;
	Node<T> *prev;

	Node<T> () { prev = nullptr; item = 0; }; // Default Constructor
	Node<T> (T d) { prev = nullptr; item = d; }; 

};

// Generic Linked List Class
template <typename T>
class List : public Listinterface<T>
{
public:
	Node<T> *head;
	int itemCount;

	List () { head = nullptr; itemCount=0; }; // Default Constructor

	// Checks to see if the list is empty or not
	bool isEmpty()
	{
		// Check to see if the list is empty. Can be done in (2) ways
		// (1) if head node is NULL, or (2) the itemCount is 0

		if (itemCount==0 && head == nullptr){
			//cout << "This list is currently empty" << endl;
			return true;
		}
		else {

			//cout << "This list is no longer empty" << endl;
			return false;
		}
		
	};

	// Add an item to the list
	bool add(T newEntry) {

		// Create a new node for this newEntry called Ndata
		Node<T> *Ndata = new Node<T> (newEntry);

		if (head==nullptr){
			
			// This case is for an empty list
			head = Ndata; //initialize the head to Ndata.
			itemCount = itemCount+1; // Increase the itemCount by 1
			return true;
		}

		else {

			// For an existing list, we need to point the prev of Ndata to the current head
			// Then move the head of this list to Ndata and increase the itemCount.
			Ndata->prev = head; 
			head = Ndata;
			itemCount = itemCount+1;
			return true;
		}

		delete Ndata;

	};

	// Removes a specified entry in the list
	bool remove(T anEntry) {

		// We will search the list by starting at the head and moving through the
		// previous nodes of the list until it we find our desired node to remove.
		Node<T> *SNode = head; // Our starting Node, which traverses the list
		Node<T> *PNode = head; // keeps track of the previous node before SNode.


		while (SNode->item != anEntry && SNode!=NULL) { // while loop to find the desired node.
			PNode = SNode;
			SNode = SNode->prev;
		};
	
		// Makes sure that our desired node is found. 
		if (PNode != NULL && SNode!=PNode) {

			Node<T> *RemoveMe = SNode; //
			PNode->prev = SNode->prev;
			delete RemoveMe;

			itemCount = itemCount-1;
			return true;
		}
		
		// If the removed node is the head node, we need to move the head.
		if (PNode!= NULL && SNode == PNode) {

			//Node<T> *NewHead = PNode->prev;
			//NewHead->prev = PNode->prev->prev; 
			//head = NewHead;

			Node<T> *RemoveMe = SNode;
			SNode = SNode->prev;
			SNode->prev = SNode->prev->prev;
			head = SNode;

			delete RemoveMe;
			
			itemCount = itemCount-1;
			return true;
		}

		if (SNode->prev == NULL) {
		
			return false;
		}
		
		return true;
	};

/*
	// Prints the contents of the list.
	void output()
	{
		Node<T> *PrintMe = head;
	
		while(PrintMe != NULL) {
			cout << PrintMe->item << '\t';
			PrintMe = PrintMe->prev;
		}
		
	};

*/	

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

	// Find a specifed entry of the list
	bool search(T anEntry) {

		Node<T> *FindMe = head;

		while (FindMe->item != anEntry && FindMe != NULL) {
			FindMe = FindMe->prev;
		};

		if (FindMe!=NULL) {
			cout << "The word " << FindMe->item << " is in this list" << endl;
			return true;
		}

		else {
			return false;
		}	
	};
	
};

int main() {

	List<string> Mylist;
	
	//ListInterface<int> * Alist = &Mylist;
	
	ifstream file("Words.txt");
	string word;
	
	cout << "Now begins my Linked list demonstration!"<< endl;
	Mylist.isEmpty();
	
	cout << "Adding contents of Words.txt to List" << endl;
	
	if (file.is_open()){
		while (getline(file,word)){
			
			// The following lines remove whitespaces
			istringstream WordStream (word);
			WordStream >> noskipws;
			WordStream >> word >> ws;

			// add these words into my list
			Mylist.add(word);
		}
		
		file.close();
	}

	Mylist.isEmpty();
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	//cout << "Here's the list: " << endl;
	//Mylist.output();
	//cout << '\n' << endl;
	cout << "Let's find the word, calling" << endl;
	Mylist.search("calling");
	cout << "Let's remove this word." << endl;
	Mylist.remove("calling");
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << "I guess it did work?" << endl;
	cout << "Let's remove the head which is " << Mylist.head->item << endl;
	Mylist.remove("supper");
	cout << "The new head is " << Mylist.head->item << endl;
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << "Let's clear the list" << endl;
	Mylist.clear();
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	Mylist.isEmpty();
	

	return 0;
}