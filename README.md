# Data Structures in C++

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
- [How to Compile and Run](#how-to-compile-and-run)
- [Contributing](#contributing)
- [License](#license)

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
This implementation of a **Queue** uses a simulation of traffic junction management, where cars are processed in a First-In, First-Out (FIFO) order.

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
