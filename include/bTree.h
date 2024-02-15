#pragma once

#include "bTree_iterator.h"

#define DFT_SIZE 5

template<class T>
class bTree {
private:
	//Member variables
	int size;
	bTree_node<T>* end_node;
	//Member functions
	bTree_node<T>* locate(const T& element);
public:
	//Constructor/Destructor
	bTree(int size);
	bTree();
	~bTree();
	//Member functions
	bTree<T>& insert(const T& element);
	bTree<T>& printTree();
	bTree<T>& printInOrder();
	bTree_iterator<T> begin();
	bTree_iterator<T> end();
	bTree_iterator<T> find(const T& element);
	bTree<T>& remove(const T& element);
	bTree_iterator<T> successor(const T& element);
	bTree_iterator<T> precursor(const T& element);
	bTree<T>& clear();
};

#include "..\src\bTree.hpp"
