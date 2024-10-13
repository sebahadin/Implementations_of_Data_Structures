# Data Structures Implementation in C++

## Overview
This repository contains C++ implementations of various fundamental data structures. Each data structure is implemented from scratch and includes key operations like insertion, deletion, searching, and sorting. The aim is to provide a comprehensive resource for learning, testing, and applying data structures in real-world applications.

## Table of Contents
- [Data Structures](#data-structures)
  - [AVL Tree](#avl-tree)
  - [Binary Heap](#binary-heap)
  - [Binary Search Tree](#binary-search-tree)
  - [Custom Vector](#custom-vector)
  - [Doubly Linked List](#doubly-linked-list)
  - [Stack](#stack)
  - [Queue with Traffic Junction Simulation](#queue-with-traffic-junction-simulation)
  - [General Tree](#general-tree)
  - [Singly Linked List](#singly-linked-list)
  - [Hash Table](#hash-table)

## Data Structures

### 1. AVL Tree
An **AVL Tree** is a self-balancing binary search tree. This implementation ensures balance through rotations after insertion or deletion to maintain an O(log n) height.

**Code:** [`AVL_Tree.cpp`](./AVL_Tree.cpp)

---

### 2. Binary Heap
A **Binary Heap** is a complete binary tree with heap properties, where every parent is smaller (or larger) than its children. This implementation supports insertion, deletion, and heap sort.

**Code:** [`BinaryHeap.cpp`](./BinaryHeap.cpp)

---

### 3. Binary Search Tree (BST)
A **Binary Search Tree** (BST) ensures that for each node, its left subtree contains values less than the node, and the right subtree contains values greater than the node. It supports standard operations like insertion and search.

**Code:** [`BinarySearchTree.cpp`](./BinarySearchTree.cpp)

---

### 4. Custom Vector
This is a custom implementation of a **dynamic array** similar to the C++ `vector` class. It includes functionalities such as dynamic resizing, push, pop, and element access.

**Code:** [`C++_vector_implementation.cpp`](./C++_vector_implementation.cpp)

---

### 5. Doubly Linked List
A **Doubly Linked List** allows traversal in both directions, with each node containing pointers to both its next and previous nodes. This implementation includes insertions, deletions, and traversal operations.

**Code:** [`DoublyLinkedList.cpp`](./DoublyLinkedList.cpp)

---

### 6. Stack
A **Stack** follows the Last In, First Out (LIFO) principle. This implementation supports operations like push, pop, and peek.

**Code:** [`Stack.cpp`](./Stack.cpp)

---

### 7. Queue with Traffic Junction Simulation
The **Traffic Junction Simulation** is a practical demonstration of the **Queue** data structure, where cars arriving at a traffic junction are processed in a First-In, First-Out (FIFO) order. This simulation models real-world traffic flow, where the first car to arrive at a junction is the first to be allowed to pass, ensuring a fair and orderly system. The queue operates by enqueuing cars as they arrive and dequeuing them as they pass through the junction. The simulation efficiently handles the order of vehicles and can be extended to include more complex traffic behaviors such as multi-lane traffic, traffic lights, and priority-based systems.

In this implementation, cars are added to the queue with a random or predefined arrival time, and the system processes them according to the order in which they arrived. The queue ensures that each car waits its turn and exits the system once processed. This simulation provides an effective way to understand how queues can be applied in real-world scenarios, such as traffic management, while demonstrating the efficiency of basic queue operations like enqueue, dequeue, and peek. The code can also be expanded to include additional features such as calculating wait times, handling varying traffic loads, or incorporating real-time data for more advanced traffic flow simulations.

**Code:** [`Traffic_junction_simulation_queue_implementation.cpp`](./Traffic_junction_simulation_queue_implementation.cpp)

---

### 8. General Tree
A **General Tree** allows each node to have an arbitrary number of children, making it useful for representing hierarchical data. This implementation supports traversal and other tree operations.

**Code:** [`General_Tree.cpp`](./General_Tree.cpp)

---

### 9. Singly Linked List
A **Singly Linked List** is a linear data structure where each node points to the next one in the sequence. This implementation includes insertions, deletions, and traversal.

**Code:** [`SinglyLinkedList.cpp`](./SinglyLinkedList.cpp)

---

### 10. Hash Table
A **Hash Table** is a key-value data structure that uses a hash function to map keys to buckets for efficient lookup and insertion.

**Code:** [`HashTable.cpp`](./HashTable.cpp)
