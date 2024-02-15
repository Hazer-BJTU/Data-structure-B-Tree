#define CRTDBG_MAP_ALLOC

#include ".\include\bTree.h"
#include <crtdbg.h>
#include <fstream>
#include <time.h>

#define MAXN 100000
#define DFT_STR_LENGTH 256

int myRand() {
	return rand() * 1000 + rand();
}

int h[MAXN + 5];
int NUMBER, SIZE;
using namespace std;
int main() {
	
	ifstream fileIn("config.ini");
	if (!fileIn) {
		cout << "File not found...\n";
		exit(0);
	}
	
	char temp[DFT_STR_LENGTH];
	fileIn.getline(temp, DFT_STR_LENGTH);
	fileIn >> NUMBER;
	fileIn.get();
	fileIn.getline(temp, DFT_STR_LENGTH);
	fileIn >> SIZE;
	fileIn.get();
	fileIn.close();
	
	srand((unsigned)time(NULL));
	{
		bTree<int>tree(SIZE);
		for (int i = 0; i < NUMBER; i++) {
			int option = myRand() % 10 + 1;
			if (option <= 4) {
				int x = myRand() % MAXN + 1;
				cout << "Insert " << x << '\n';
				tree.insert(x);
				h[x] = 1;
			}
			else if (option <= 6) {
				int x = myRand() % MAXN + 1;
				while (h[x] == 0 && x != MAXN)x++;
				cout << "Remove " << x << '\n';
				tree.remove(x);
				h[x] = 0;
			}
			else if (option == 7) {
				int x = myRand() % MAXN + 1;
				bTree_iterator<int>it = tree.find(x);
				if ((it == tree.end() && h[x] == 0) || (it != tree.end() && h[x] == 1)) {
					cout << "Find test passed.\n";
				}
				else {
					cout << "Find test failed!\n";
					exit(0);
				}
			}
			else if (option == 8) {
				int x = myRand() % MAXN + 1;
				bTree_iterator<int>it = tree.precursor(x);
				int p = -1;
				for (int i = x - 1; i >= 1; i--) {
					if (h[i] == 1) {
						p = i;
						break;
					}
				}
				if (p == -1 && it == tree.end()) {
					cout << "Precursor test passed.\n";
				}
				else if (*(it.get()) == p) {
					cout << "Precursor test passed.\n";
				}
				else {
					cout << "Precursor test failed!\n";
					exit(0);
				}
			}
			else if (option == 9) {
				int x = myRand() % MAXN + 1;
				bTree_iterator<int>it = tree.successor(x);
				int p = -1;
				for (int i = x + 1; i <= MAXN; i++) {
					if (h[i] == 1) {
						p = i;
						break;
					}
				}
				if (p == -1 && it == tree.end()) {
					cout << "Successor test passed.\n";
				}
				else if (*(it.get()) == p) {
					cout << "Successor test passed.\n";
				}
				else {
					cout << "Successor test failed!\n";
					exit(0);
				}
			}
			else if (option == 10) {
				bool flag = true;
				for (bTree_iterator<int>it = tree.begin(); it != tree.end(); it++) {
					if (h[*(it.get())] == 0) {
						flag = false;
						break;
					}
				}
				if (flag) cout << "Traverse test passed.\n";
				else {
					cout << "Traverse test failed!\n";
					exit(0);
				}
			}
		}
		tree.printTree();
		tree.clear();
		tree.printTree();
	}
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
