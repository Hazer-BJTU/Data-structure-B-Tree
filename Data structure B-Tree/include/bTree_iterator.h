#pragma once

#include "bTree_node.h"

template<class T>
class bTree_iterator {
	template<class U>friend class bTree;
private:
	//Member variables
	int position;
	bTree_node<T>* node;
	static bTree_iterator<T> successor(bTree_node<T>* node, const T& element);
	static bTree_iterator<T> precursor(bTree_node<T>* node, const T& element);
public:
	//Constructor/Destructor
	bTree_iterator();
	bTree_iterator(int position, bTree_node<T>* node);
	~bTree_iterator();
	//Member function
	bool operator == (const bTree_iterator& it);
	bool operator != (const bTree_iterator& it);
	bTree_iterator<T>& operator ++ ();
	bTree_iterator<T> operator ++ (int);
	bTree_iterator<T>& operator -- ();
	bTree_iterator<T> operator -- (int);
	T* get();
};

#include "..\src\bTree_iterator.hpp"
