/*
* avlTree.h
*
*  Created on: 7 במאי 2018
*      Author: אלאא
*/

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<iostream>

using namespace std;
template<class T>


class rankTree
{
public:
	struct node
	{
		T data;
		int key;
		int key2;
		int sum;
		int rank;
		node* left;
		node* right;
		unsigned long int height;
	};

	node* root;

	void makeEmpty(node* t)
	{
		if (t == NULL)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}


	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}
	int height(node* t)
	{

		if (t == NULL) return 0;
		else return t->height;
		return 1;
	}

	int getBalance(node* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	void inorder(node* t, int* arr, int* i)
	{
		if (t == NULL)
			return;
		inorder(t->right, arr, i);

		arr[*i] = t->key2;
		*i += 1;

		inorder(t->left, arr, i);
	}

	rankTree()
	{
		root = NULL;
	}

	void insert(T x, int key)
	{
		root = insert(x, key, root);
	}
	void insertAux(T x, int key, int key2)
	{
		root = insertAux(x, key, key2, root);
	}

	void remove(int key)
	{
		root = remove(root, key);
	}

	void removeAux(int key, int key2)
	{
		root = removeAux(root, key, key2);
	}

	int max(int x, int y)
	{
		return x > y ? x : y;
	}

	rankTree& operator=(const rankTree& tree) {

		this->root = tree.root;

		return *this;
	}

	node* search(int key, node* t) {
		// Element not found
		if (t == NULL)
			return NULL;

		// Searching for element
		else if (key < t->key)
			return search(key, t->left);
		else if (key > t->key)
			return search(key, t->right);
		return t;
	}

	T& search(int key) {
		node* t = search(key, this->root);
		return t->data;
	}
	int searchLibrary(int key) {
		node* t = search(key, this->root);
		if (t == NULL)
			return 0;
		return 1;
	}

	T& searchAux(int key, int key2) {
		node* t = searchAux(key, key2, this->root);
		return t->data;
	}

	node* searchAux(int key, int key2, node* t) {
		if (t == NULL)
			return NULL;

		// Searching for element
		else if (key == t->key) {
			if (key2 < t->key2) {
				return searchAux(key, key2, t->left);
			}
			else if (key2 > t->key2) {
				return searchAux(key, key2, t->right);
			}
		}
		else if (key < t->key)
			return searchAux(key, key2, t->left);
		else if (key > t->key)
			return searchAux(key, key2, t->right);
		return t;
	}


	void inorder(int* arr, int* i)
	{
		inorder(this->root, arr, i);
	}

	void inorderAux(node* t)
	{

		if (t == NULL)
			return;
		inorderAux(t->left);
		cout << t->key << " ";
		inorderAux(t->right);
	}


	void display()
	{
		inorderAux(root);
		cout << endl;
	}




	void inorderUnite(node* t, T* arr, int* i)
	{
		if (t == NULL)
			return;
		inorderUnite(t->left, arr, i);
		arr[*i] = t->data;
		*i += 1;
		inorderUnite(t->right, arr, i);
	}
	void inorderUnite(T* arr, int* i)
	{
		inorderUnite(this->root, arr, i);

	}


	/* A function that constructs Balanced Binary Search Tree from a sorted array */
	void sortedArrayToBST(T* arr, int start, int end, int* keys, int* keys2)
	{
		/* Base Case */
		if (start > end)
			return;

		/* Get the middle element and make it root */
		int mid = (start + end) / 2;
		insertAux(arr[mid], keys[mid], keys2[mid]);

		/* Recursively construct the left subtree and make it
		left child of root */
		sortedArrayToBST(arr, start, mid - 1, keys, keys2);

		/* Recursively construct the right subtree and make it
		right child of root */
		sortedArrayToBST(arr, mid + 1, end, keys, keys2);

		return;
	}


	node* singleRightRotate(node* &t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		updateRanks(t);
		setAllSums(t);
		return u;
	}

	node* singleLeftRotate(node* &t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		updateRanks(t);
		setAllSums(t);
		return u;
	}

	node* doubleLeftRotate(node* &t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node* &t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}








	///////////// nwe remove
	node* remove(node* p, int key)
	{
		if (!p) return 0;
		if (key < p->key)
			p->left = remove(p->left, key);
		else if (key > p->key)
			p->right = remove(p->right, key);
		else //  k == p->key
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);

	}
	node* balance(node* p) // p node balance
	{
		fixheight(p);

		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // no balance needed
	}


	node* removemin(node* p) // deleting the node with the minimal key from p tree
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* findmin(node* p) // searching the node with the minimal key in p tree
	{
		return p->left ? findmin(p->left) : p;
	}
	node* rotateleft(node* q) // the left rotation round q
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}
	node* rotateright(node* p) // the right rotation round p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}
	void fixheight(node* p)
	{
		unsigned long int hl = 0;
		if (p->left != NULL) hl = height(p->left);
		unsigned long int  hr = 0;
		if (p->right != NULL)hr = height(p->right);
		p->height = (hl>hr ? hl : hr) + 1;
	}
	int bfactor(node* p)
	{
		return height(p->right) - height(p->left);
	}
	node* removeAux(node* p, int key, int key2)
	{
		if (!p) return 0;
		if (key < p->key)
			p->left = removeAux(p->left, key, key2);
		else if (key > p->key)
			p->right = removeAux(p->right, key, key2);
		else if (key == p->key && key2 < p->key2)
			p->left = removeAux(p->left, key, key2);
		else if (key == p->key && key2 > p->key2)
			p->right = removeAux(p->right, key, key2);

		else //  k == p->key
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);

	}


	~rankTree() {
		//destroy(root);
	}
	void destroy(node* root) {
		if (root == NULL) return;
		destroy(root->left);
		destroy(root->right);
		delete root;

	}
	void destroy() {
		destroy(this->root);
	}






	node* insert(T x, int k, node* t) // k key insertion in the tree with p root
	{
		if (!t)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = NULL;
			t->key = k;
			t->height = max(height(t->left), height(t->right)) + 1;

			return t;
		}
		if (k<t->key)
			t->left = insert(x, k, t->left);
		else
			t->right = insert(x, k, t->right);
		return balance(t);
	}
	node* insertAux(T x, int k, int k2, node* t) // k key insertion in the tree with p root
	{
		if (!t)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = NULL;
			t->key = k;
			t->key2 = k2;
			t->height = max(height(t->left), height(t->right)) + 1;
			t->rank = 1;
			t->sum = k;

			return t;
		}

		if (k < t->key) {
			t->left = insertAux(x, k, k2, t->left);
			
		}
		else if (k > t->key) {
			t->right = insertAux(x, k, k2, t->right);
			
		}
		else {
			if (k2 > t->key2) {
				t->right = insertAux(x, k, k2, t->right);
			
			}
			else {
				t->left = insertAux(x, k, k2, t->left);
				
			}
		}





		node* b= balance(t);
		updateRanks(t);
		setAllSums(root);
		return b;
	}


	node* insertAuxScoreBoard(T x, int k, int k2, node* t) // k key insertion in the tree with p root
	{
		if (!t)
		{
			t = new node;
			t->data = x;
			t->height = 0;
			t->left = t->right = NULL;
			t->key = k;
			t->key2 = k2;
			t->height = max(height(t->left), height(t->right)) + 1;

			return t;
		}

		if (k<t->key)
			t->left = insertAuxScoreBoard(x, k, k2, t->left);
		else if (k>t->key)
			t->right = insertAuxScoreBoard(x, k, k2, t->right);
		else if (k == t->key) {
			if (k2 > t->key2)
				t->right = insertAuxScoreBoard(x, k, k2, t->right);


			else

				t->left = insertAuxScoreBoard(x, k, k2, t->left);


		}





		return balance(t);
	}

	void insertAuxScoreBoard(T x, int k, int k2) {
		root = insertAuxScoreBoard(x, k, k2, root);
	}
	void inorderScore(node* t, int* arr, int* i)
	{
		if (t == NULL)
			return;
		inorderScore(t->right, arr, i);

		arr[*i] = t->key;
		*i += 1;
		inorderScore(t->left, arr, i);
	}
	void inorderScore(int* arr, int* i)
	{
		inorderScore(this->root, arr, i);
	}


	void inorderCount(node* t, int* i)
	{
		if (t == NULL)
			return;
		inorderCount(t->left, i);

		*i += 1;
		inorderCount(t->right, i);
	}
	void inorderCount(int* i)
	{
		inorderCount(this->root, i);
	}

	void updateRanks(node* n) {
		node* current = n;
		while (current != NULL) {

			int leftRank = 0, rightRank = 0;
			//	int leftSum = 0, rightSum = 0;
			if (current->left) {
				leftRank = current->left->rank;
				//	leftSum = current->left->sum;
			}
			if (current->right) {

				rightRank = current->right->rank;
				//	rightSum = current->right->sum;

			}

			current->rank = leftRank + rightRank + 1;
			//current->sum = leftSum + rightSum + current->sum;

			current = current->parent;

		}
	}


	void setAllRanks(node* subroot) {
		if (!subroot)

			return; // empty tree , only if root==null

		int leftRank = 0;

		int rightRank = 0;

		if (subroot->left) {

			setAllRanks(subroot->left);

			leftRank = subroot->left->rank;

		}

		if (subroot->right) {

			setAllRanks(subroot->right);

			rightRank = subroot->right->rank;

		}

		subroot->rank = leftRank + rightRank + 1;
	}
	void setAllSums(node* subroot) {
		if (!subroot)

			return; // empty tree , only if root==null

		int leftSum = 0;

		int rightSum = 0;

		if (subroot->left) {

			setAllSums(subroot->left);

			leftSum = subroot->left->sum;

		}

		if (subroot->right) {

			setAllSums(subroot->right);

			rightSum = subroot->right->sum;

		}

		subroot->sum = leftSum + rightSum + subroot->key;
	}
	void print() {
		print2(root, 1);
	}
	void print2(node* nodeToPrint, int level) {
		int i;

		if (nodeToPrint) {

			print2(nodeToPrint->right, level + 1);

			cout << "\n";

			if (nodeToPrint == root) {

				cout << "Root ->";

			}



			for (i = 0; i < level && nodeToPrint != root; i++) {

				cout << "       ";

			}

			cout << nodeToPrint->key;

			//cout << nodeToPrint->data;
			cout << ",,,,,,";
			cout << nodeToPrint->rank;
			cout << "--sum--";
			cout << nodeToPrint->sum;
			//cout << nodeToPrint->getBalance();



			print2(nodeToPrint->left, level + 1);

		}
	}


};




#endif /* AVLTREE_H_ */
