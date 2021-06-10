#include <iostream>
#include "uftree.h"
using namespace std;

template <class T>
class unionfind {
public:
	int* size;
	int* parents;
	int n;
	//each index represents a set :
	uftree<T>** tree;
	unionfind() {}
	unionfind(int n,T* arr) {
		size = new int[n];
		parents = new int[n];
		this->n = n;
		tree = new uftree<T>*[n];

		for (int i = 0; i < n; i++) {
			size[i] = 1;
			parents[i] = -1;
		}
		for (int i = 0; i < n; i++) {
			tree[i] = new uftree<T>(i+1,arr[i]);
		//	tree[i] = &uftree<T>;
		}
}
	int find(int element) {
		int parent = parents[element-1];
		int tmp = -1;
		while (parent != -1) {
			 tmp = parent;
			parent = parents[parent - 1];
		
		}
		
		parent = parents[element - 1];
		while (parent != -1) {
			//x is the child parent is the parent 
			int x = parent;
			parent = parents[parent - 1];
			if (parent == -1)
				break;
			parents[x- 1] = tmp;
			

		}
		parents[element - 1] = tmp;
		if (tmp == -1)
			return element;
		return tmp;
}

	int beforeUnion(int e1, int e2) {
		int g1 = find(e1);
		int g2 = find(e2);
		int p;
		if (size[g1 - 1] > size[g2 - 1]) {
			
			p = g1;
		}
		else {
			
			p = g2;
		}
		return p;

	}

	//returns the new parent
	int unionM(int e1, int e2) {
		int g1 = find(e1);
		int g2 = find(e2);
		int c, p;
		if (size[g1 - 1] > size[g2 - 1]) {
			c = g2;
			p = g1;
		}
		else {
			c = g1;
			p = g2;
		}

		parents[c - 1] = p;
		size[p - 1] = size[p - 1] + size[c - 1];
		(tree[c - 1])->merge(tree[p - 1]);
		return p;

	}

	void print() {
		for (int i = 0; i < n; i++) {
			cout << i << "parent " << parents[i] << endl;
			cout << "size " << size[i] << endl;
		}


	}
	T& findGroup(int element) {
		int group = find(element);
		return tree[group-1]->getRootData();
		
	}

};