/*
* hashTable.h
*
*  Created on: 14 ביונ 2018
*      Author: אלאא
*/

#ifndef HASHTABLE_H_
#define HASHTABLE_H_




#include <iostream>
using namespace std;

template <class T>
class hashTable
{
public:
	struct node
	{
		T data;
		int key;
		node* next;
	};
	int size;
	int elements_num;
	node** arr;

	hashTable() {
		size = 0;
		elements_num = 0;
		arr = NULL;

	}


	void resize() {
		int newSize = 2 * size;
		if (size == 0)
			newSize = 1;
		node** newTable = new node*[newSize];

		for (int i = 0; i < newSize; i++) {
			newTable[i] = NULL;
		}

		//set tke old nodes in the new array
		for (int i = 0; i < size; i++) {
			node* tmp = arr[i];
			while (tmp) {
				node* next = tmp->next;
				node* tmp2 = tmp;
				int index = tmp2->key % newSize;
				tmp2->next = newTable[index];
				newTable[index] = tmp2;

				tmp = next;
			}
		}

		if (size != 0)
			delete[] arr;

		arr = newTable;
		size = newSize;
	}

	void insert(node* element, int size, node** arr) {
		int index = element->key % size;
		node* tmp = arr[index];
		arr[index] = element;
		element->next = tmp;


	}
	void insert(T data, int key) {

		node* new_node = new node;
		new_node->key = key;
		new_node->next = NULL;
		new_node->data = data;

		if (elements_num == size)
			resize();
		elements_num++;

		insert(new_node, size, arr);


	}
	void remove(int key) {
		if (size == 0)
			return;
		int index = key % size;
		node* tmp = arr[index];
		node* toDelete = NULL;
		if (tmp == NULL)
			return;
		//if the key is the head of the list
		if (tmp->key == key) {
			arr[index] = tmp->next;
			toDelete = tmp;
			tmp = NULL;
			delete toDelete;
			return;
		}
		while (tmp->next) {
			if (tmp->next->key == key) {
				toDelete = tmp->next;
				tmp->next = toDelete->next;
				delete toDelete;
				return;

			}
			tmp = tmp->next;
		}
	}
	node* search(int key, node* tmp) {
		while (tmp) {
			if (tmp->key == key) {
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}

	T& search(int key) {

		int index = key % size;
		node* tmp = arr[index];
		node* t = search(key, tmp);

		return t->data;
	}

	bool isMember(int key) {
		if (size == 0)
			return false;
		int index = key % size;
		node* tmp = arr[index];
		while (tmp != NULL) {
			if (tmp->key == key) {
				return true;
			}
			tmp = tmp->next;
		}
		return false;

	}

	void putKeysInArr(int* keys, int* n) {
		int num = 0;
		for (int i = 0; i < size; i++) {
			node* tmp = arr[i];
			while (tmp) {
				*keys = tmp->key;
				tmp = tmp->next;
				++keys;
				num++;
			}
		}
		*n = num;
	}


	void printTable() {
		for (int i = 0; i < size; i++) {
			node* tmp = arr[i];
			while (tmp) {
				if (tmp == NULL) break;
				std::cout << "index " << i << ",, key: " << tmp->key << endl;
				tmp = tmp->next;
			}
		}
	}

	~hashTable() {
		//delete[] del;
		//delete[] arr;
	}

};




#endif /* HASHTABLE_H_ */
