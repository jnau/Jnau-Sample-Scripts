# Data Structures and Algorithms

Implementation of certain Data Structures and algorithms using Linked Lists and Dynamic Arrays/Matrices.

# LinkedList.cpp & DoublyLinkedList.cpp
Implements a regular Linked List, and Doubly Linked List which in turn is used to create stack and queue containers. We implemented search and sort algorithms using these data structures. These can be found in __BinarySearchSort.cpp & RadixSort.cpp__ where we implemented binary search, insertion sort, and radix sort algorithms.

# HashTables.cpp
Using an inline dynamic array implementation of doubly linked lists, we created a hash table to sort Customers by their first/last name and arbitrary identification number, thus generating hash keys using 3 simple methods: the MidSquare, MidSquare Base 2, and basic Modulo methods. 

# BinaryTrees.cpp
Created Binary Tree data structure using a tree node definition. In order to iteratively traverse the tree, we implemented a stack using doubly linked lists. This implementation __does not__ generate a height balanced tree. Therefore, the __TreeBalancing__.cpp script rotates a degenerate tree into a height balanced tree using AVL rotations.

# Graphs.cpp
Implementing a Dynamic matrix by using a dynamic array of arrays, we created a graph of distances between 7 different airlines. Implementing a lowest cost algorithm, similar to Dijkstra's algorithm, we would find the lowest cost in terms of the number of total distance in miles. 

## Relevant files include: 
Numbers.txt, Words.txt, and FlightDistances.txt
