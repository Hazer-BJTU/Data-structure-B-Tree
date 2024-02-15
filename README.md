# Data-structure-B-Tree
B-Tree implementation as homework assignment for data structure course.
## Introduction
B-Tree is a typical dynamic search tree like Binary Search Tree, AVL Tree, Red Black Tree and B+Tree, etc, which is capable of simultaneously inserting, removing and querying elements. This is a complete B-Tree program suitable for homework assignment of data structure. Despite its lenghy implementation, potential bugs and low efficiency, it's to some extent easy to understand for undergraduate students who major in computer science.
## API
## ``` template<class T> class bTree ```
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
  bTree<T>& insert(const T& element);
```
Insert an ```element``` into the bTree.
```
  bTree<T>& printTree();
```
Print the structure of bTree in the command line.
```
  bTree<T>& printInOrder();
```
Print all the elements in ascending order in the command line.
```
  bTree_iterator<T> begin();
```
Return a bTree iterator pointing to the first element. If the tree is empty, it will return ```end()```.
```
  bTree_iterator<T> end();
```
Return a bTree iterator pointing to the successor of the last element.
```
  bTree_iterator<T> find(const T& element);
```
Return a bTree iterator pointing to the given ```element``` or return ```end()``` if the given ```element``` doesn't exist.
```
  bTree<T>& remove(const T& element);
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
```
  bTree<T>& clear();
```
Clear all elements in the tree.
## ```template<class T> class bTree_iterator```
Declaration: bTree_iterator.h\
Definition: bTree_iterator.hpp
```
  bTree_iterator<T>& operator ++ ();
```
Point to the element that comes after the current element. The iterator that comes after ```end()``` is ```end()```.
```
  bTree_iterator<T> operator ++ (int);
```
It is similar to the operation above.
```
  bTree_iterator<T>& operator -- ();
```
Point to the element that comes before the current element. The iterator that comes before ```begin()``` is ```end()```.
```
  bTree_iterator<T> operator -- (int);
```
It is similar to the operation above.
```
  T* get();
```
You can use it to manipulate the element. For example, the following code shows you how to print all elements in the bTree in ascending order.
```
  bTree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  for (bTree_iterator<int> it = tree.begin() ; it != tree.end() ; it++) {
    std::cout << *(it.get()) << ' ';
  }
```
