template<class T>
bTree_node<T>::bTree_node(int size, T element) {
	this->size = size;
	num = 1;
	dataArr = new T[size + BLOCK];
	for (int i = 0; i < size + BLOCK; i++)
		dataArr[i] = T();
	dataArr[0] = element;
	pointerArr = new bTree_node<T>*[size + BLOCK + 1];
	for (int i = 0; i < size + BLOCK + 1; i++)
		pointerArr[i] = NULL;
	father = NULL;
}

template<class T>
bTree_node<T>::bTree_node(const bTree_node<T>& node) {
	size = node.size;
	num = node.num;
	dataArr = new T[size + BLOCK];
	for (int i = 0; i < size + BLOCK; i++)
		dataArr[i] = node.dataArr[i];
	pointerArr = new bTree_node<T>*[size + BLOCK + 1];
	for (int i = 0; i < size + BLOCK + 1; i++)
		pointerArr[i] = NULL;
	father = NULL;
}

template<class T>
bTree_node<T>::bTree_node() {
	size = num = 0;
	dataArr = new T[size + BLOCK];
	for (int i = 0; i < size + BLOCK; i++)
		dataArr[i] = T();
	pointerArr = new bTree_node<T>*[size + BLOCK + 1];
	for (int i = 0; i < size + BLOCK + 1; i++)
		pointerArr[i] = NULL;
	father = NULL;
}

template<class T>
bTree_node<T>::~bTree_node() {
	delete[] dataArr;
	for (int i = 0; i < size + BLOCK + 1; i++) {
		if (!pointerArr[i]) continue;
		delete pointerArr[i];
		pointerArr[i] = NULL;
	}
	delete[] pointerArr;
}

template<class T>
void bTree_node<T>::reConnect(bTree_node<T>* father, bTree_node<T>* child, int position) {
	if (child) child->father = father;
	if (father) father->pointerArr[position] = child;
	return;
}

template<class T>
bool bTree_node<T>::isTerminal() {
	//The terminal nodes have no child.
	return pointerArr[0] == NULL;
}

template<class T>
bool bTree_node<T>::isRoot() {
	//The father of the root actually represents end() and doesn't contain valid data.
	//The father of end() is NULL.
	return father->father == NULL;
}

template<class T>
int bTree_node<T>::getPos() {
	if (!father) return -1;
	for (int i = 0; i < father->num + 1; i++)
		if (father->pointerArr[i] == this) return i;
}

template<class T>
bTree_node<T>* bTree_node<T>::locate(const T& element) {
	//Locate the tree node where the given element should be inserted or already exists.
	//If the given element doesn't exist, then the located tree node must be a terminal node.
	if (isTerminal()) return this;
	if (element < dataArr[0]) return pointerArr[0]->locate(element);
	for (int i = 0; i < num; i++) {
		if (dataArr[i] == element) return this;
		if (i > 0 && dataArr[i - 1] < element && element < dataArr[i]) {
			return pointerArr[i]->locate(element);
		}
	}
	return pointerArr[num]->locate(element);
}

template<class T>
int bTree_node<T>::locateInNode(const T& element) {
	for (int i = 0; i < num; i++)
		if (dataArr[i] == element) return i;
	return -1;
}

template<class T>
void bTree_node<T>::split(int position) {
	/* Illustration of spliting the root node.
	*                                     A
	*         [ D ] A [ E ]             /   \
	*             /   \       -->   [ D ]   [ E ]
	*         [ B ]   [ C ]              | |
	*                                [ B ] [ C ]
	*/
	if (isRoot()) {
		bTree_node<T>* new_root = new bTree_node<T>(size, dataArr[position]);
		bTree_node<T>* right_part = new bTree_node<T>(size, T());
		//Move data [ position + 1, num - 1 ] in this node to [ 0, num - position - 2 ] in  the right_part.
		for (int i = position + 1; i < num; i++)
			right_part->dataArr[i - position - 1] = dataArr[i];
		//Reconnect pointer [ position + 1, num ] in this node to [ 0, num - position -1 ] in the right_part.
		for (int i = position + 1; i < num + 1; i++) {
			reConnect(right_part, pointerArr[i], i - position - 1);
			pointerArr[i] = NULL;
		}
		//Resize the nodes, num(after) + right_part.num + 1 = num(original), num(after) = position.
		right_part->num = num - position - 1;
		num = position;
		//Reconnect the two nodes to the new root node.
		reConnect(father, new_root, 0);
		reConnect(new_root, this, 0);
		reConnect(new_root, right_part, 1);
		new_root->num = 1;
		return;
	}
	/* Illustration of spliting a internal node.
	*          [ F ] [ G ]          [ F ] A [ G ]
	*               |                   /   \
	*         [ D ] A [ E ]   -->   [ D ]   [ E ]
	*             /   \                  | |
	*         [ B ]   [ C ]          [ B ] [ C ]
	*/
	//Split a internal node.
	bTree_node<T>* right_part = new bTree_node<T>(size, T());
	for (int i = position + 1; i < num; i++)
		right_part->dataArr[i - position - 1] = dataArr[i];
	for (int i = position + 1; i < num + 1; i++) {
		reConnect(right_part, pointerArr[i], i - position - 1);
		pointerArr[i] = NULL;
	}
	right_part->num = num - position - 1;
	num = position;
	int pos = getPos();
	//Shift data [ pos, father.num - 1 ] to [ pos + 1, father.num ] in the father node.
	//Meanwhile, shift pointer [ pos + 1, father.num ] to [ pos + 2, father.num + 1 ] in the father node.
	for (int i = father->num; i > pos; i--) {
		father->dataArr[i] = father->dataArr[i - 1];
		father->pointerArr[i + 1] = father->pointerArr[i];
	}
	//Reconnect the two nodes to the new root node.
	father->dataArr[pos] = dataArr[position];
	reConnect(father, right_part, pos + 1);
	father->num++;
	return;
}

template<class T>
void bTree_node<T>::printTree() {
	std::cout << "[";
	for (int i = 0; i < num; i++) {
		std::cout << dataArr[i];
		if (i != num - 1) std::cout << ",";
	}
	std::cout << "]: ";
	if (isTerminal()) std::cout << "Null";
	for (int i = 0; i < num + 1; i++) {
		if (!pointerArr[i]) continue;
		std::cout << "[";
		for (int j = 0; j < pointerArr[i]->num; j++) {
			std::cout << pointerArr[i]->dataArr[j];
			if (j != pointerArr[i]->num - 1) std::cout << ",";
		}
		std::cout << "]";
		if (i != num) std::cout << ", ";
	}
	std::cout << std::endl;
	for (int i = 0; i < num + 1; i++)
		if (pointerArr[i]) pointerArr[i]->printTree();
	return;
}

template<class T>
void bTree_node<T>::printInOrder() {
	for (int i = 0; i < num; i++) {
		if (pointerArr[i]) pointerArr[i]->printInOrder();
		std::cout << dataArr[i] << " ";
	}
	if (pointerArr[num]) pointerArr[num]->printInOrder();
	return;
}

template <class T>
void bTree_node<T>::merge(int position) {
	/* Illustration of merging the node.
	*      [ F ] A [ G ]            [ F ] [ G ]
	*          /   \                     |
	*      [ D ]   [ E ]    -->    [ D ] A [ E ]
	*           | |                    /   \
	*       [ B ] [ C ]             [ B ] [ C ]
	*/
	bTree_node<T>* right = pointerArr[position + 1];
	bTree_node<T>* left = pointerArr[position];
	left->dataArr[left->num] = dataArr[position];
	//Move data [ 0, right.num - 1 ] in the right node to [ left.num + 1, right.num + left.num ] in the left node.
	for (int i = 0; i < right->num; i++)
		left->dataArr[left->num + i + 1] = right->dataArr[i];
	//Reconnect pointer [ 0, right.num ] in the right node to [ left.num + 1, right.num + left.num + 1 ] in the left node.
	for (int i = 0; i < right->num + 1; i++) {
		reConnect(left, right->pointerArr[i], left->num + i + 1);
		right->pointerArr[i] = NULL;
	}
	//Delete the right node while resize the left node.
	left->num = left->num + right->num + 1;
	delete right;
	//Shift data from [ position + 1, num - 1 ] to [ position, num - 2 ] in this node.
	//Meanwhile, shift pointer [ position + 2, num ] to [ position + 1, num - 1 ] in this node.
	for (int i = position; i < num - 1; i++) {
		dataArr[i] = dataArr[i + 1];
		pointerArr[i + 1] = pointerArr[i + 2];
	}
	pointerArr[num] = NULL;
	num--;
	//The empty root node should be deleted.
	if (isRoot() && num == 0) {
		reConnect(father, left, 0);
		for (int i = 0; i < size + BLOCK + 1; i++)
			pointerArr[i] = NULL;
		delete this;
	}
	return;
}

template<class T>
void bTree_node<T>::leftRotate(int position) {
	/* Illustration of the left rotation.
	*       [ H ] A [ I ]               [ H ] C [ I ]
	*           /   \                       /   \
	*    [ F ] B     C [ G ]   -->   [ F ] B A   [ G ]
	*           |   |                       | |
	*       [ D ]   [ E ]               [ D ] [ E ]
	*/
	bTree_node<T>* right = pointerArr[position + 1];
	bTree_node<T>* left = pointerArr[position];
	left->dataArr[left->num] = dataArr[position];
	reConnect(left, right->pointerArr[0], left->num + 1);
	right->pointerArr[0] = NULL;
	dataArr[position] = right->dataArr[0];
	left->num++;
	//Shift data from [ 1, right.num - 1 ] to [ 0, right.num - 2 ] in the right node.
	//Meanwhile, shift pointer [ 1, right.num ] to [ 0, right.num - 1 ] in the right node.
	for (int i = 0; i < right->num - 1; i++) {
		right->dataArr[i] = right->dataArr[i + 1];
		right->pointerArr[i] = right->pointerArr[i + 1];
	}
	right->pointerArr[right->num - 1] = right->pointerArr[right->num];
	right->pointerArr[right->num] = NULL;
	right->num--;
	return;
}

template<class T>
void bTree_node<T>::rightRotate(int position) {
	/* Illustration of the right rotation.
	*       [ H ] A [ I ]             [ H ] B [ I ]
	*           /   \                     /   \
	*    [ F ] B     C [ G ]   -->   [ F ]     A C [ G ]
	*           |   |                         | |
	*       [ D ]   [ E ]                 [ D ] [ E ]
	*/
	bTree_node<T>* right = pointerArr[position + 1];
	bTree_node<T>* left = pointerArr[position];
	//Shift data from [ 0, right.num - 1 ] to [ 1, right.num ] in the right node.
	//Meanwhile, shift pointer [ 0, right.num ] to [ 1, right.num + 1 ] in the right node.
	right->pointerArr[right->num + 1] = right->pointerArr[right->num];
	for (int i = right->num; i > 0; i--) {
		right->dataArr[i] = right->dataArr[i - 1];
		right->pointerArr[i] = right->pointerArr[i - 1];
	}
	right->dataArr[0] = dataArr[position];
	reConnect(right, left->pointerArr[left->num], 0);
	left->pointerArr[left->num] = NULL;
	right->num++;
	dataArr[position] = left->dataArr[left->num - 1];
	left->num--;
	return;
}

