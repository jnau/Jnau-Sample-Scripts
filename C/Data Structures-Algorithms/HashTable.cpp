// Lab4_HashTable.cpp
// Implements a Hash table with a dynamic array of doubly linked lists

// Name: Jessica Au
// CWID: 20161910

#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <stdlib.h>
#include <memory>
#include <math.h>

using namespace std;


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
	~DynamicArray()
	{
		if (items)
			delete[] items;
	}

	void resize(int n){

		if (items) {
			delete []items;
		}
		
		while (n>maxItems)
		{
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
	
		while(PrintMe != NULL) {
			cout << "Index: " << PrintMe->item.CalculateHash_MSquareBase2(PrintMe->item.GetKey()) << ' ' << "Name: " << '\t' << PrintMe->item.GetFirstName() << ' ' << PrintMe->item.GetLastName() << ' ' << '\t' << "ID: " << PrintMe->item.GetID()  << '\n';
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
};

// New Customer class 
// holds information about the customers
// Generates the unique hash keys here

class Customer 
{
private:

	string lastname;
	string firstname;
	string id;
	int hash_Method1;
	int hash_Method2;
	int hash_Method3;
	int key;

public:

	Customer() {lastname = ""; firstname = ""; id = ""; hash_Method1 = -1; hash_Method2 = -1; hash_Method3 = -1; key = -1;};
	Customer( string firstname, string lastname, string id) {

		setFirstName(firstname);
		setLastName(lastname);
		setID(id);
		setKey(id);
	}

	void setFirstName(string s) { firstname = s; };
	void setLastName(string s) { lastname = s; };
	void setID(string s){ id = s; };
	void setHash(int key){ hash_Method1 = CalculateHash_Modulo(key); hash_Method2 = CalculateHash_MidSquare(key); hash_Method3 = CalculateHash_MSquareBase2(key); };

	string GetFirstName() {return firstname;};
	string GetLastName() {return lastname;};
	string GetID() {return id;}

	int GetKey(){ return key; };
	int GetHash1(){ return hash_Method1; };
	int GetHash2(){ return hash_Method2; };
	int GetHash3(){ return hash_Method3; };

	void setKey(string s)
	{
		string delimiter = "-";
		string token;
		size_t pos = 0;

		int n = 0;
		int Part1 = 0;
		int Part2 = 0;

		while ((pos = s.find(delimiter))!= string::npos){

			token = s.substr(0,pos);
			Part1 = stoi(token);
			s.erase(0,pos+delimiter.length());
		}
		
		Part2 = stoi(s);
		
		//n = abs((Part1*Part2)+11 - (Part1+Part2)*11);
		//n = abs(Part1+Part2+11*Part1-12);
		int S1 = Sum(Part1);
		int S2 = Sum(Part2);

		n = abs(Part1+Part2+11*Part1-12);
		key = n;

	}

	// calculate hash for Modulo method
	int CalculateHash_Modulo(int key)
	{

		int n = 0;
		n = key % 640;
		
		return n;

	}; 

	int Integer_RadixGetLength(int value) {

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

	int Sum(int value){

		DynamicArray<int> nums;

		int sum = 0;
		int len = Integer_RadixGetLength(value);
		for (int i = 0; i < len; i++){
			nums[i] = value % 10;
			sum = sum + nums[i];
			value = value/10;

		}

		return sum;

	};
	int GetDigits(int value, int length, int NumDigits){

		DynamicArray<int> nums;


		for (int i = 0; i < length; i++){
			nums[i] = value % 10;
			value = value/10;

		}

		int Mid = length/2;
		int Start = Mid+1;
		int End = Start-NumDigits;

		int MiddleDigits = 0;

		int pow10 = pow(10,(NumDigits-1));
		
		for (int j = Start; j > End; j--){
			
			MiddleDigits = MiddleDigits + nums[j]*pow10;
			pow10 = pow10/10;

		}

		return MiddleDigits;

	};

	// Calculate hash for Mid Square method
	int CalculateHash_MidSquare(int key){

		int n = 0;
		int R = 3;

		n = abs(key * key);
		int len = Integer_RadixGetLength(n);
		int digits = GetDigits(n, len, R);

		n = digits % 640;

		return n;

	};

	// Calculate hash for Mid Square Base 2 method
	int CalculateHash_MSquareBase2(int key){

		int n = 0;
		int R = 14;

		n = abs(key * key);
		int exBits = n >> R;
		exBits = exBits & (0xFFFFFFFF >> (32-R));

		n = exBits % 640;

		return n;

	};


	friend bool operator== (const Customer &c1, const Customer &c2){
		return (c1.firstname == c2.firstname && c1.lastname == c2.lastname && c1.id == c2.id);
	};

	friend bool operator!= (const Customer &c1, const Customer &c2){
		return !(c1== c2);
	};

};

// Generic Hash Table Class
template <typename T>
class HashTable : DList<T>
{

private:
	DynamicArray<DList<T> > table;
	int collisions;

public:
	HashTable(int n){ collisions = 0; table.resize(n*1.1);}; // 1.25x size of #data

	~HashTable() 
	{
		cout << "Number of Collisions using Mid Square Base 2 Method = " << collisions << ' ' << (collisions*100/513) << "%" << endl;
	};

	int MaxSize()
	{ 
		return table.getMaxSize();
	};

	int CurrentSize() 
	{
		return table.getCurrentSize();
	};

	//void HashInsert(int key)
	void HashInsert(T& t)
	{
		int key = t.GetKey();
		t.setHash(key);

		//int index = t.GetHash1(); // 95 collisions
		//int occupied = 0;

		//int index = t.GetHash2(); // 95 Collisions: 156/513, 640 space
		//int occupied = 0;

		int index = t.GetHash3(); // 85 Collisions; 16%, for 1280 space, 154/513, 28% 640 space
		int occupied = 0;

		if (!table[index].isEmpty()){

			occupied = table[index].itemCount;
		}

		table[index].add(t);
		table.Update_Size();

		if (occupied>0) {
			collisions++;
		}

	};

	void SetHash(DynamicArray<T>& data, int ArraySize)
	{
		for (int i = 0; i < ArraySize; i++){
			HashInsert(data[i]);

		}

	};

	void PrintHash(int TableSize){
		for (int i = 0; i < TableSize;i++){
			table[i].output();
		}

	}

	T Find(string s)
	{
		//cout << "HASH TABLE" << endl;

		Customer FindMe;
		FindMe.setKey(s);
		int K = FindMe.GetKey();
		cout << "The Hash Key is: " << K << endl;
		
		int index = FindMe.CalculateHash_MSquareBase2(K);
		//int index = FindMe.CalculateHash_Modulo(K);
		//int index = FindMe.CalculateHash_MidSquare(K);
		//cout << " Hash = " << index << endl;

		Node<T> *Search = table[index].head;
		while ((Search->item.GetKey()) != K && Search!=nullptr) {
			Search = Search->prev;
		};
			
		return Search->item;
		
	};

};


int main()
{
	DynamicArray<Customer> darray;
	ifstream file("Customer.csv");
	string ln;
	string fn;
	string identification;

	if (!file.is_open()) {
		cout << "Error!" << endl;
	}

	while (file.good()){

		getline(file, ln, ',');
		getline(file, fn, ',');
		getline(file, identification, '\n');

		Customer Customer(fn,ln,identification);
		darray.add(Customer);
	}

	file.close();

	int NumItems = darray.getCurrentSize();
	cout << "The current number of items in this array is: " << NumItems << endl;
	cout << "Max Size of the Dynamic Array: " << darray.getMaxSize() << endl;
	//if (!darray.isEmpty()) {cout << "This isn't empty" << endl;};
	//cout << "ID: " <<darray[1].GetID() << "Name: " << darray[1].GetLastName() <<  darray[1].GetFirstName()<< endl;
	
	HashTable<Customer> Mytable(NumItems);
	cout << "The max size of my Hash Table is: " << Mytable.MaxSize() << endl;
	Mytable.SetHash(darray, NumItems);
	int tablesize = Mytable.CurrentSize();
	cout << "Currently, My hash table has " << Mytable.CurrentSize() << " items" << endl;
	cout << '\n' << endl;
	cout << "Find the person with this ID: 25674316-6058714" << endl;
	Customer person = Mytable.Find("25674316-6058714");
	//Customer person = Mytable.Find("56105665-7450612");
	cout << "Found: " << person.GetFirstName() << ' ' << person.GetLastName() << '\t' << person.GetID() << endl;
	cout << '\n' << endl;
	Mytable.PrintHash(tablesize);

	return 0;
}