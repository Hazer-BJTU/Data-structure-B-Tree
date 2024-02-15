template<class T>
bTree<T>::bTree(int size) {
	this->size = size;
	end_node = new bTree_node<T>(size, T());
}

template<class T>
bTree<T>::bTree() {
	size = DFT_SIZE;
	end_node = new bTree_node<T>(size, T());
}

template<class T>
bTree<T>::~bTree() {
	if (end_node)
		delete end_node;
	end_node = NULL;
}

template<class T>
bTree_node<T>* bTree<T>::locate(const T& element) {
	//Find more details in bTree_node.h/locate
	if (!end_node->pointerArr[0]) return NULL;
	return end_node->pointerArr[0]->locate(element);
}

template<class T>
bTree<T>& bTree<T>::insert(const T& element) {
	bTree_node<T>* node = locate(element);
	if (node == NULL) {
		end_node->pointerArr[0] = new bTree_node<T>(size, element);
		end_node->pointerArr[0]->father = end_node;
		return *this;
	}
	if (node->locateInNode(element) != -1) {
		//The given element already exists in the tree.
		return *this;
	}
	//Find the first element in node which is greater than the given element.
	int p = 0;
	while (node->dataArr[p] < element && p < node->num) p++;
	//Shift data [ p, num - 1 ] to [ p + 1, num ] in the node.
	for (int i = node->num; i > p; i--)
		node->dataArr[i] = node->dataArr[i - 1];
	node->dataArr[p] = element;
	node->num++;
	//Make adjustments to the tree in order to maintain its properties.
	while (node != end_node) {
		if (node->num > node->size) node->split((node->num) >> 1);
		else break;
		node = node->father;
	}
	return *this;
}

template<class T>
bTree<T>& bTree<T>::printTree() {
	if (!end_node->pointerArr[0]) {
		std::cout << "The tree is empty..." << std::endl;
		return *this;
	}
	end_node->pointerArr[0]->printTree();
	return *this;
}

template<class T>
bTree<T>& bTree<T>::printInOrder() {
	if (!end_node->pointerArr[0]) {
		std::cout << "The tree is empty..." << std::endl;
		return *this;
	}
	end_node->pointerArr[0]->printInOrder();
	std::cout << std::endl;
	return *this;
}

template<class T>
bTree_iterator<T> bTree<T>::begin() {
	bTree_node<T>* ptr = end_node;
	while (ptr->pointerArr[0]) ptr = ptr->pointerArr[0];
	return bTree_iterator<T>(0, ptr);
}

template<class T>
bTree_iterator<T> bTree<T>::end() {
	return bTree_iterator<T>(0, end_node);
}

template<class T>
bTree_iterator<T> bTree<T>::find(const T& element) {
	bTree_node<T>* ptr = locate(element);
	if (ptr == NULL) return end();
	if (ptr->locateInNode(element) == -1) return end();
	for (int i = 0; i < ptr->num; i++) {
		if (ptr->dataArr[i] == element)
			return bTree_iterator<T>(i, ptr);
	}
}

template<class T>
bTree<T>& bTree<T>::remove(const T& element) {
	bTree_node<T>* node = locate(element);
	if (node == NULL) {
		//The tree is empty.
		return *this;
	}
	int pos = node->locateInNode(element);
	if (pos == -1) {
		//The element doesn't exist.
		return *this;
	}
	if (!node->isTerminal()) {
		//Instead of removing a given element in an internal node, we actually remove its successor.
		bTree_iterator<T> it(pos, node);
		it++;
		node->dataArr[pos] = *(it.get());
		node = it.node;
		pos = it.position;
	}
	//Shift data from [ pos + 1, num - 1 ] to [ pos, num - 2 ] in the node.
	for (int i = pos; i < node->num - 1; i++)
		node->dataArr[i] = node->dataArr[i + 1];
	node->num--;
	//Make adjustment to the tree in order to maintain its properties.
	while (node->num < size >> 1 && !node->isRoot()) {
		int p = node->getPos();
		bTree_node<T>* father = node->father;
		if (p + 1 <= father->num && father->pointerArr[p + 1]->num > size >> 1) {
			//We perform the left rotation.
			father->leftRotate(p);
			break;
		}
		else if (p - 1 >= 0 && father->pointerArr[p - 1]->num > size >> 1) {
			//We perform the right rotation.
			father->rightRotate(p - 1);
			break;
		}
		//We perform the merge operation.
		if (p + 1 <= father->num) {
			father->merge(p);
		}
		else {
			node = father->pointerArr[p - 1];
			father->merge(p - 1);
		}
		//If the root is empty and thus deleted, we break the loop.
		if (node->isRoot()) break;
		node = node->father;
	}
	if (node->isRoot() && node->num == 0) {
		//The tree is empty.
		delete end_node->pointerArr[0];
		end_node->pointerArr[0] = NULL;
	}
	return *this;
}

template<class T>
bTree_iterator<T> bTree<T>::successor(const T& element) {
	//Return the first element that is strictly greater than the given element, or imply that such element doesn't exist.
	//Find more details in bTree_iterator.h/successor
	if (!end_node->pointerArr[0]) return end();
	bTree_iterator<T>it = bTree_iterator<T>::successor(end_node->pointerArr[0], element);
	if (it == bTree_iterator<T>(0, NULL)) return end();
	return it;
}

template<class T>
bTree_iterator<T> bTree<T>::precursor(const T& element) {
	//Return the last element that is strictly smaller than the given element, or imply that such element doesn't exist.
	//Find more details in bTree_iterator.h/precursor
	if (!end_node->pointerArr[0]) return end();
	bTree_iterator<T>it = bTree_iterator<T>::precursor(end_node->pointerArr[0], element);
	if (it == bTree_iterator<T>(0, NULL)) return end();
	return it;
}

template<class T>
bTree<T>& bTree<T>::clear() {
	if (end_node->pointerArr[0] == NULL) return *this;
	delete end_node->pointerArr[0];
	end_node->pointerArr[0] = NULL;
	return *this;
}
