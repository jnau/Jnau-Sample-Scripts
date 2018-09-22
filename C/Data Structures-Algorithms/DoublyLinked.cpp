// Lab1_DoublyLinked.cpp

// Implementation of a doubly linked list by adding a next node.
// Implemented a Stack and Queue interface with the following functions:
// 	Pop, Push, Peek, isEmpty, and GetLength.

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

		Node<T> *RemoveMe = head; // Our starting Node, which traverses the list
		Node<T> *PNode = head; // keeps track of the previous node before RemoveMe.
		Node<T> *SNode = head->prev; // keeps track of succeeding node after RemoveMe


		while (RemoveMe->item != anEntry && RemoveMe!=NULL && SNode!=NULL) { // while loop to find the desired node.
			PNode = RemoveMe;
			RemoveMe = RemoveMe->prev;
			SNode = RemoveMe->prev;
		};
	
		// Makes sure that our desired node is found. 
		// Makes sure that our desired node is found. 
		if (PNode != NULL && RemoveMe!=PNode && SNode!=NULL) {

		//
			PNode->prev = SNode;
			SNode->next = PNode;
			//delete RemoveMe;
			itemCount = itemCount-1;

			return true;
		}
		
		// If the removed node is the head node, we need to move the head.
		if (PNode!= NULL && RemoveMe == PNode) {

			Node<T> *NewHead = SNode;
			NewHead->next = NULL; 
			head = NewHead;
			//delete RemoveMe;
			
			itemCount = itemCount-1;

			return true;
		}

		if (SNode == NULL) { // this is the end of the list and needs to be removed.
		
			PNode->prev = NULL;
			//delete RemoveMe;
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

};

// Generic Stack Class
template <typename T>
class Stack : public DList<T>
{
public:
	Stack () {}; // default constructor

	void Push(T d)
	{
		this->add(d);
	}

	bool Pop()
	{
		Node<T> *TopItem = this->head;

		if (this->itemCount>1) {
			
			T value = TopItem->item;
			this->remove(value);
			cout << "The popped item is " << value << endl;
			return true;
		}
		else if (this->itemCount==1) {

			T value = TopItem->item;
			cout << "The popped item is " << value << endl;
			this->clear();
			return true;
		}
		else {
			cout << "Sorry, this stack is empty" << endl;
			return false;
		}
	};
	
	void Peek() 
	{
	 	Node<T> *FindMe = this->head;
		if (this->search(FindMe->item)==true) {
			cout << "The top item is " << FindMe->item << endl;
		}
	};


	bool isEmpty() 
	{
		Node<T> *Head = this->head;
		int NumItems = this->itemCount;

		if (Head==NULL && NumItems==0) {
			cout << "This stack is empty" << endl;
			return true;
		}
		else {
			cout << "This stack is not empty" << endl;
			return false;
		}

	};

	int GetLength() {
		return this->itemCount;
	};
};


// Generic Queue Class
template <typename T>
class Queue : public DList<T>
{
public: 
	Queue() {};

	void Push(T data)
	{
		Node<T> *Tail = this->head;
		Node<T> *Ndata = new Node<T> (data);

		int NumItems = this->itemCount;

		if (NumItems==0) {
			this->add(data);
			this->itemCount = NumItems+1;
		}

		else {

			while(Tail->prev!=NULL) {

				Tail = Tail->prev;
			}
			
			Ndata->next = Tail;
			Tail->prev = Ndata;
			this->itemCount = NumItems+1;
		}

	};

	void Pop() 
	{
		Node<T> *TopItem = this->head;
		
		if (this->itemCount>1) {
			
			T value = TopItem->item;
			this->remove(value);
			cout << "The popped item in this queue is " << value << endl;
		}

		else if (this->itemCount==1){

			T value = TopItem->item;
			cout << "The last item in this queue is " << value << endl;
			this->clear();
		}

		else if (this->itemCount==0){
			cout << "Sorry, this queue is empty" << endl;
		}
	};

	void Peek() 
	{
	 	Node<T> *FindMe = this->head;
	 	
		if (this->search(FindMe->item)==true) {
			cout << "The top item is " << FindMe->item << endl;
		}
	};

	 bool isEmpty() 
	 {
		Node<T> *Head = this->head;
		int NumItems = this->itemCount;

		if (Head==NULL && NumItems==0) {
			cout << "This queue is empty" << endl;
			return true;
		}
		else {
			cout << "This queue is not empty" << endl;
			return false;
		}
	};
	 
	int GetLength() 
	{
		return this->itemCount;
	};
};


int main()
{

	DList<string> Mylist;
	ListInterface<string> * Alist = &Mylist;
	Stack<string> MyStack;
	Queue<string> MyQueue;
	
	ifstream file("Words.txt");
	string word;
	
	cout << "Now begins my Doubly Linked list demonstration!"<< endl;
	if(Alist->isEmpty()==true) {cout << "We currently have an empty list" << endl; };
	
	cout << "Adding contents of Words.txt to List" << endl;
	
	if (file.is_open()){
		while (getline(file,word)){
			
			// The following lines remove whitespaces
			istringstream WordStream (word);
			WordStream >> noskipws;
			WordStream >> word >> ws;

			// add these words into my list
			Alist->add(word);
			MyStack.Push(word);
			MyQueue.Push(word);
		}

		file.close();

	}

	// Dlist demonstration
	if(Alist->isEmpty()==false) {
		cout << "This list is no longer empty." << endl; 
	};

	cout << '\n' << endl;
	cout << "Here's the list: " << endl;
	Mylist.output();
	cout << '\n' << endl;
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << "Let's find the word, calling" << endl;
	string M = "calling";
	if (Alist->search(M)==true) {
		cout << "The word " << M << " is found in this list."<< endl;
	};

	cout << "Let's remove this word." << endl;
	Alist->remove("calling");
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << "Let's remove the head which is " << Mylist.head->item << endl;
	M = "supper";
	if (Alist->search(M)==true) {
		cout << "The word " << M << " is found in this list."<< endl;
	};

	Alist->remove("supper");
	cout << "The new head is " << Mylist.head->item << endl;
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	M = "the";
	cout << "Try removing the last item " << M << endl;
	Alist->remove(M);
	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << "Let's clear the list. " << endl;
	Alist->clear();
	if (Alist->isEmpty()==true) { 
		cout << "This list is now cleared." << endl;
	};

	cout << "There are now " << Mylist.itemCount << " items in this list"<< endl;
	cout << '\n' << endl;
	cout << '\n' << endl;

	// Stack Demonstration
	cout << "Now begins the Stack demonstration" << endl;
	MyStack.isEmpty();
	cout << "The length of this stack is " << MyStack.GetLength() << endl;
	MyStack.Peek();
	MyStack.Pop();
	MyStack.Pop();
	MyStack.Pop();
	MyStack.Pop();
	//cout << "The contents of the current stack are: " << endl;
	//MyStack.output();
	//cout << '\n' << endl;
	cout << "The length of this stack is " << MyStack.GetLength() << endl;
	cout << '\n' << endl;
	cout << '\n' << endl;

	// Queue demonstration
	cout << "Now begins the Queue demonstration" << endl;
	MyQueue.isEmpty();
	cout << "The length of this queue is " << MyQueue.GetLength() << endl;
	MyQueue.Peek();
	MyQueue.Pop();
	MyQueue.Pop();
	MyQueue.Pop();
	MyQueue.Pop();
	//cout << "The contents of the current queue are: " << endl;
	//MyQueue.output();
	//cout << '\n' << endl;
	cout << "The length of this queue is " << MyQueue.GetLength() << endl;


	return 0;
}