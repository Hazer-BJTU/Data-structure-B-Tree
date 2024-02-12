#pragma once

#include <iostream>
#include <stdlib.h>

#define BLOCK 1

template<class T>
class bTree_node {
	template<class U>friend class bTree;
	template<class U>friend class bTree_iterator;
private:
	//Member variables
	int size, num;
	T* dataArr;
	bTree_node<T>** pointerArr;
	bTree_node<T>* father;
	//Constructor/Destructor
	bTree_node(int size, T element);
	bTree_node(const bTree_node<T>& node);
	bTree_node();
	~bTree_node();
	//Member functions
	static void reConnect(bTree_node<T>* father, bTree_node<T>* child, int position);
	bool isTerminal();
	bool isRoot();
	int getPos();
	bTree_node<T>* locate(const T& element);
	int locateInNode(const T& element);
	void split(int position);
	void printTree();
	void printInOrder();
	void merge(int position);
	void leftRotate(int position);
	void rightRotate(int position);
};

#include "..\src\bTree_node.hpp"
