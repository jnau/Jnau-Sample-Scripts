// Lab7_Graphs.cpp

// It found that the lowest cost would be starting at any point and be 4391 miles. 

#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <math.h>

using namespace std;

//ofstream myfile("Lab7_results.txt");

// From DynamicArray.cpp
enum { INVALID=-1,DEFAULT_CAPACITY = 10 };	// Small size to test

template <typename T>
class ArrayInterface
{
public:
	/** Gets the current number of entries in this array.
	@return The integer number of entries currently in the bag. */
	virtual int getCurrentSize() = 0;

	/** Sees whether this array is empty.
	@return True if the bag is empty, or false if not. */
	virtual bool isEmpty() = 0;

	/** Adds a new entry to this array.
	@post  If successful, newEntry is stored in the array and
	the count of items in the bag has increased by 1.
	@param newEntry  The object to be added as a new entry.
	@return  True if addition was successful, or false if not. */
	virtual void add(T newEntry) = 0;

};

template <typename T>
class DynamicArray : public ArrayInterface<T>
{
private:
	T* items;							// Array of items
	int itemCount;                      // Current count of array items 
	int maxItems;                       // Max capacity of the array
public:
	DynamicArray(int capacity = DEFAULT_CAPACITY) : itemCount(0), maxItems(capacity)
	{
		items = new T[capacity];
	}  
	/*
	~DynamicArray()
	{
		if (items)
			delete[] items;
	}*/

	void resize(int n){

		if (items) {
			delete []items;
		}

		while (n>maxItems){
			maxItems = maxItems*2;
		}

		items = new T[maxItems];
	}

	int getCurrentSize()
	{
		return itemCount;
	}  

	int Update_Size(){
		int n = itemCount;
		n++;
		itemCount = n;

		return itemCount;
	}

	int getMaxSize()
	{
		return maxItems;
	}

	bool isEmpty() 
	{
		return itemCount == 0;
	}  

	T& get(int index)
	{
		return items[index];
	}

	T& operator [](int index)
	{
		return get(index);
	}

	void add(T newEntry)
	{
		bool hasRoomToAdd = (itemCount < maxItems);
		if (hasRoomToAdd)
		{
			items[itemCount] = newEntry;
			itemCount++;
		}  

		else {

			// make a new array
			const int DoubleSize = maxItems*2;
			T *NewArray = new T[DoubleSize];


			for (int i = 0; i <itemCount; i++) {
				NewArray[i] = items[i];
			};

			maxItems = DoubleSize;
			delete []items;
			items = NewArray;
			items[itemCount] = newEntry;
			itemCount++;
		}
	}  

	friend ostream& operator << (ostream& stream, DynamicArray& darray)
	{
		stream << "The array contains " << static_cast<int>(darray.getCurrentSize()) << " items:" << endl;
		for (int i = 0; i < darray.getCurrentSize(); i++)
		{
			stream << darray[i] << " ";
		}  
		stream << endl << endl;
		return stream;
	} 

};

// Generic Dynamic Matrix class
template <typename T>
class DynamicMatrix
{

public: 
	DynamicArray<DynamicArray<T> > MyMatrix;
	int Num_Rows;
	int Num_Cols;
	int itemCount;

	DynamicMatrix ( int x_size, int y_size){
		Num_Rows = y_size;
		Num_Cols = x_size;
		
		for (int i = 0; i < y_size; i++){
			DynamicArray<T> A;

			for ( int j = 0; j < x_size; j++){
				A[j] = 0;
				itemCount++;
				MyMatrix[i] = A;
			}
		}
	} 

	~DynamicMatrix() 
	{
		if (!MyMatrix.isEmpty()){
			for (int i = 0; i < Num_Cols; i++){
				delete[] &MyMatrix[i];
			}

			delete[] &MyMatrix;
		}

	}

	DynamicArray<T> operator[] (int index){ return MyMatrix[index]; };

	bool isEmpty()
	{
		return itemCount==0;
	}

	int getCurrentSize()
	{
		return itemCount;
	}

	void Show() 
	{
		for (int i = 0; i < Num_Rows; i++){
			for (int j = 0; j < Num_Cols; j++){
				cout << MyMatrix[i][j] << " ";
				//myfile << MyMatrix[i][j] << " ";
			}
			cout << endl;
			//myfile << endl;
		}
	}
};

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
			return true;
		}
		else {
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

		while (FindMe->item != anEntry && FindMe != nullptr) {
			FindMe = FindMe->prev;
		};

		if (FindMe!=nullptr) {
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

		while (PrintMe->prev != nullptr) {
			PrintMe = PrintMe->prev;
		}

		while(PrintMe != nullptr) {
			cout << PrintMe->item << '\t';
			//myfile << PrintMe->item << '\t';
			PrintMe = PrintMe->next;
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
		itemCount = 0;
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
		}

		else if (this->itemCount==1){
			T value = TopItem->item;
			this->clear();
		}

		else if (this->itemCount==0){
			return;
		}
	};

	void Peek() 
	{
	 	Node<T> *FindMe = this->head;
	 	
		if (this->search(FindMe->item)==true) {
		}
	};

	 bool isEmpty() 
	 {
		Node<T> *Head = this->head;
		int NumItems = this->itemCount;

		if (Head==NULL && NumItems==0) {
			return true;
		}
		else {
			return false;
		}
	};
	 
	int GetLength() 
	{
		return this->itemCount;
	};
};

// Function that implements the lowest cost algorithm as shown in lecture.
template<typename T>
DList<T> LowestCostAlgorithm(int start, DynamicMatrix<T>& Matrix) { // returns a doubly linked list object

	// initialization
	DynamicMatrix<int> MyRoutes(7,6);
	DList<int> MyList;

	int total_dist = 0;
	MyList.add(start);
	int Minimum = 5000;
	int index = 0;

	for (int j = 0; j < MyRoutes.Num_Rows; j++){
		for (int i = 0; i < MyRoutes.Num_Cols; i++){

			MyRoutes[j][i] = Matrix[start][i];

			if (j > 0) {
				
				// checks to compare if the last destination was visited
				// If this destination cannot visit any other ones, but was able to previously
				// then include this destination.
				if (MyRoutes[j][i] == 0 && MyRoutes[j-1][i] != 0) {
					MyRoutes[j][i] = MyRoutes[j-1][i];
				}

			}

			// The following conditional statements see if the destination was chosen before
			// and will disclude it in the new chosen destination.
			bool inList = false;
			Node<T> *FindMe = MyList.head;
			while (FindMe != nullptr && FindMe->item != i){
				FindMe = FindMe->prev;
			}

			if (FindMe != nullptr ){ inList = true;}

			else {
				inList = false;
			}

			// Once these conditions are met, we choose the minimum to be the lowest distance
			// that has not been visited yet.
			if (MyRoutes[j][i] != 0 && MyRoutes[j][i] < Minimum && (inList==false)){
				Minimum = MyRoutes[j][i];
				index = i;
			}
		}
	
		total_dist = total_dist + Minimum;
		Minimum = 5000;
		MyList.add(index);
		start = index;

		if (MyList.itemCount == 7) {
			MyList.add(total_dist);
			return MyList;
		}
	}

	return MyList;
}

// Translate our indexes into airline strings for readers
template <typename T>
DList<string> Translate(DList<T>& List){

	DList<string> NewList;
	Node<T> *Tail= List.head;

	while (Tail->prev != nullptr){
		Tail = Tail->prev;
	}

	Node<T> *TranslateMe = Tail;

	while (TranslateMe != nullptr) {

		T TranslateItem = TranslateMe->item;
	
		switch(TranslateItem)
		{
			case 0: NewList.add("SFO"); TranslateMe = TranslateMe->next; break;
			case 1: NewList.add("LAX"); TranslateMe = TranslateMe->next; break;
			case 2: NewList.add("DFW"); TranslateMe = TranslateMe->next; break;
			case 3: NewList.add("ORD"); TranslateMe = TranslateMe->next; break;
			case 4: NewList.add("JFK"); TranslateMe = TranslateMe->next; break;
			case 5: NewList.add("BOS"); TranslateMe = TranslateMe->next; break;
			case 6: NewList.add("MIA"); TranslateMe = TranslateMe->next; break;
		}
	}

	return NewList;
}

int main()
{
	DynamicMatrix<int> M(7,7);
	Queue<int> MyQueue; 
	DList<int> MyList;
	
	// reads in distances from text file into our dynamic matrix
	ifstream file("FlightDistance.txt");
	if (!file.is_open()) {
		cout << "Error!" << endl;
	}  

	while (file.good()){
		int num = 0;

		for (int i = 0; i < M.Num_Rows; i++){
			for (int j = 0; j < M.Num_Cols; j++){

				int s;
				file >> s;
				M[i][j] = s; 
			}
		}
	}

	file.close();
	//myfile << '\n' << endl;
	//myfile << "------ My Adjacency Matrix ------ " << endl;
	cout << '\n' << endl;
	cout << "------ My Adjacency Matrix ------ " << endl;

	M.Show();
	//myfile << '\n' << endl;
	cout << '\n' << endl;
	// Begin our queue of starting position indexes.
	for (int i = 0; i < 7; i++){
		MyQueue.Push(i);
	}
	
	DList<string> BestList;
	int BestDist;
	// while all the starting positions are not visited
	while (!MyQueue.isEmpty()) {
		
		int start = MyQueue.head->item;
		MyQueue.Pop();
		MyList = LowestCostAlgorithm(start, M);
		int LowestDistance = 5000;
		string s;

		switch(start){
			case 0: s = "SFO"; break;
			case 1: s = "LAX"; break;
			case 2: s = "DFW"; break;
			case 3: s = "ORD"; break;
			case 4: s = "JFK"; break;
			case 5:	s = "BOS"; break;
			case 6: s = "MIA"; break; 
		}

		Node<int> *Distance = MyList.head;
		MyList.remove(MyList.head->item);
		DList<string> NewList;
		
		NewList = Translate(MyList);
		cout << "The Lowest cost route starting from " << s  << " is: " << endl;
		//myfile << "The Lowest cost route starting from " << s  << " is: " << endl;
		
		NewList.output();
		if (Distance->item < LowestDistance) {
			LowestDistance = Distance->item;
			BestList = NewList;
			BestDist = LowestDistance;
		}

		cout << endl;
		cout << "The total distance is " << Distance->item <<  " miles."<< endl;
		cout << '\n' << endl;
		//myfile << endl;
		//myfile << "The total distance is " << Distance->item <<  " miles."<< endl;
		//myfile << '\n' << endl;
	}

	cout << "The BEST route with the shortest distance of " << BestDist << " is" << endl;
	//myfile << "The BEST route with the shortest distance of " << BestDist << " is" << endl;
	BestList.output();

	return 0;
}