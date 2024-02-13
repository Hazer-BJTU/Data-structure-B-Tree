# Data-structure-B-Tree
B-Tree implementation as homework assignment for data structure course.
## Introduction
B-Tree is a typical dynamic search tree like Binary Search Tree, AVL Tree, Red Black Tree and B+Tree etc, which is capable of simultaneously inserting, removing and querying elements. This is a complete B-Tree program suitable for homework assignment of data structure. Despite its lenghy implementation, potential bugs and low efficiency, its to some extent easy to understand for undergraduate students who major in computer science.
## API
## ``` template<class T> bTree ```
Declaration: bTree.h\
Definition: bTree.hpp
```
  bTree(int size);
```
Initialize a bTree instance whose nodes contain at most ```size``` elements and at least ```size/2``` elements.
```
  bTree();
```
It is the same as ```bTree(5)```.
```
  bool insert(const T& element);
```
Insert an ```element``` into the bTree, the return value indicates whether the insertion is successful.
```
  void printTree();
```
Print the structure of bTree in the command line.
```
  void printInOrder();
```
Print all the elements in ascending order in the command line.
```
  bTree_iterator<T> begin();
```
Return a bTree iterator pointing to the first element. If the tree is empty, it will return end().
```
  bTree_iterator<T> end();
```
Return a bTree iterator pointing to the successor of the last element.
```
  bTree_iterator<T> find(const T& element);
```
Return a bTree iterator pointing to the given ```element``` or return ```end()``` if the given ```element``` doesn't exist.
```
  bool remove(const T& element);
```
Remove an ```element``` from the bTree.
```
  bTree_iterator<T> successor(const T& element);
```
Find the first element that is strictly greater than the given ```element``` or return ```end()``` if such element doesn't exist.
```
  bTree_iterator<T> precursor(const T& element);
```
Find the last element that is strictly smaller than the given ```element``` or return ```end()``` if such element doesn't exist.
