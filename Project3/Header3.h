#pragma once
#include <string>
#define NODEPTR Node*


//QUESTION TO ASK**************************************************************
//WIll they test key doesnt equal value
//best way to structure AVLNODE, AVLTree
//Insert function

struct Node {
	int key;
	std::string value;
	NODEPTR parent;
	NODEPTR left = nullptr;
	NODEPTR right = nullptr;
	
};

class AVLTree {
private:
	NODEPTR root;
	bool recursiveInsert(NODEPTR current, int key, int value);
public:	
	bool insert(int key, int value);
	unsigned int getHeight();
	unsigned int getSize();
	friend ostream& operator<<(ostream& os, const AVLTree& me);
	bool find(int key, string& value);
	vector<string> findRange(int lowkey, int highkey);
	AVLTree() {
		root = nullptr;
	}
	//implement copy consructor
	//implement destructor


};
bool AVLTree::insert(int key, std::string value) {
	//implement rotations
	if (root == nullptr){
		root = new node;
		root->key = key;
		root->value = value;
		root->parent = nullptr;
		return true;
	}
	return recursiveInsert(root, key, value);
}
bool AVLTree::recursiveInsert(NODEPTR current, int key, int value) {
	if (current == nullptr){
		root = new AVLNode;
		root->key = key;
		root->value = value;
		root->parent = nullptr;
		return true;
	}
	if (curent->key == key){
		return false;
	}
	if (tmp->key < key) {
		return recursiveInsert(current->right, key, value);
	}
	return recursiveInsert(current->right, key, value);
}

unsigned int AVLTree::getHeight() {

}
unsigned int AVLTree::getSize() {

}
friend ostream& operator<<(ostream& os, const AVLTree& me) {

}
bool AVLTree::find(int key, string& value) {

}
vector<string> AVLTree::findRange(int lowkey, int highkey) {

}
