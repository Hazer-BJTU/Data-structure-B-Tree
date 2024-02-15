template<class T>
bTree_iterator<T>::bTree_iterator() {
	position = 0;
	node = NULL;
}

template<class T>
bTree_iterator<T>::bTree_iterator(int position, bTree_node<T>* node) {
	this->position = position;
	this->node = node;
}

template<class T>
bTree_iterator<T>::~bTree_iterator() {}

template<class T>
bool bTree_iterator<T>::operator == (const bTree_iterator& it) {
	return position == it.position && node == it.node;
}

template<class T>
bool bTree_iterator<T>::operator != (const bTree_iterator& it) {
	return !operator == (it);
}

template<class T>
bTree_iterator<T>& bTree_iterator<T>::operator ++ () {
	if (node->father == NULL) return *this;
	if (!node->isTerminal()) {
		//The successors of internal nodes lie in their subtrees.
		node = node->pointerArr[position + 1];
		while (node->pointerArr[0]) node = node->pointerArr[0];
		position = 0;
		return *this;
	}
	if (position + 1 < node->num) {
		position++;
		return *this;
	}
	position++;
	while (position >= node->num && node->father != NULL) {
		//Backtracking the successor in the father of the node.
		position = node->getPos();
		node = node->father;
	}
	//Set the iterator to end() if the precursor doesn't exist.
	if (node->father == NULL)
		position = 0;
	return *this;
}

template<class T>
bTree_iterator<T> bTree_iterator<T>::operator ++ (int) {
	bTree_iterator<T> temp = *this;
	operator ++ ();
	return temp;
}

template<class T>
bTree_iterator<T>& bTree_iterator<T>::operator -- () {
	if (node->father == NULL && node->pointerArr[position] == NULL) return *this;
	if (!node->isTerminal()) {
		//The precursors of internal nodes lie in their subtrees.
		node = node->pointerArr[position];
		while (node->pointerArr[node->num]) node = node->pointerArr[node->num];
		position = node->num - 1;
		return *this;
	}
	if (position - 1 >= 0) {
		position--;
		return *this;
	}
	position--;
	while (position < 0 && node->father != NULL) {
		//Backtracking the precursor in the father of the node.
		position = node->getPos() - 1;
		node = node->father;
	}
	//Set the iterator to end() if the precursor doesn't exist.
	if (node->father == NULL)
		position = 0;
	return *this;
}

template<class T>
bTree_iterator<T> bTree_iterator<T>::operator -- (int) {
	bTree_iterator<T> temp = *this;
	operator -- ();
	return temp;
}

template<class T>
T* bTree_iterator<T>::get() {
	return &(node->dataArr[position]);
}

template<class T>
bTree_iterator<T> bTree_iterator<T>::successor(bTree_node<T>* node, const T& element) {
	int p = 0;
	while (p != node->num && !(element < node->dataArr[p])) p++;
	if (node->isTerminal()) {
		if (p == node->num)
			return bTree_iterator<T>(0, NULL);
		return bTree_iterator<T>(p, node);
	}
	if (p == node->num)
		return successor(node->pointerArr[p], element);
	bTree_iterator<T>it = successor(node->pointerArr[p], element);
	if (it == bTree_iterator<T>(0, NULL))
		return bTree_iterator<T>(p, node);
	return it;

}

template<class T>
bTree_iterator<T> bTree_iterator<T>::precursor(bTree_node<T>* node, const T& element) {
	int p = node->num - 1;
	while (p != -1 && !(node->dataArr[p] < element)) p--;
	if (node->isTerminal()) {
		if (p == -1)
			return bTree_iterator<T>(0, NULL);
		return bTree_iterator<T>(p, node);
	}
	if (p == -1)
		return precursor(node->pointerArr[p + 1], element);
	bTree_iterator<T>it = precursor(node->pointerArr[p + 1], element);
	if (it == bTree_iterator<T>(0, NULL))
		return bTree_iterator<T>(p, node);
	return it;
}

