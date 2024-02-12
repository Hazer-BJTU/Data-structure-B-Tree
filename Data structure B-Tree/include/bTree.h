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
	bool insert(const T& element);
	void printTree();
	void printInOrder();
	bTree_iterator<T> begin();
	bTree_iterator<T> end();
	bTree_iterator<T> find(const T& element);
	bool remove(const T& element);
	bTree_iterator<T> successor(const T& element);
	bTree_iterator<T> precursor(const T& element);
};

#include "..\src\bTree.hpp"
