#include <iostream>
using namespace std;

template <class T>

class uftree {
public:
	class Node {
	public:
		Node* parent;
		int id;
		T data;
		// data is NULL unless we are the root

		Node(int i, T t) {
			parent = NULL;
			this->id = i;
			data = t;
		}
		Node(){}
		Node& operator=(const Node& n) {
			this->data = n.data;
			this->id = n.id;
			this->parent = n.parent;
			return *this;
		}
	};
	Node* root;
	int size;
	 uftree(int i, T t) {
		// Node r(i, t);
		 root = new Node(i,t);
		// *root=r;
		 size = 1;
		
	}
	// use this after union to merge the trees
	 void updateDate(T newt) {}
	 //the current tree is now the child of t 
	 void merge(uftree* t) {

		 this->root->parent = t->root;
		 root = root->parent;
		 t->size += this->size;

	 }

	 uftree() 
	 {
		 root = NULL;
		 size = 0;

	 
	 }
     uftree& operator=(const uftree& t) {
		 this->root = t.root;
		 this->size = t.size;
		 return *this;
	 }
	 uftree(const uftree& t) {
		 this->root = t.root;
		 this->size = t.size;

	 }
	 T& getRootData()
	 {
		 return root->data;

	 }
	 void destroy()
	 {

	 }


};