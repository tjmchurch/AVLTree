#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>   
#include<algorithm>
#define NODEPTR Node*
struct Node {
	int key;
	std::string value;
	NODEPTR parent;
	NODEPTR left = nullptr;
	NODEPTR right = nullptr;
	Node(int key, std::string val, NODEPTR parent) {
		this->key = key;
		this->value = val;
		this->parent = parent;
	}
};
class AVLTree {
private:
	NODEPTR root;
	unsigned int size;
	bool recursiveInsert(NODEPTR current, int key, std::string value);
	bool recursiveFind(NODEPTR current, int key, std::string& value);
	void balance(NODEPTR current);
	void singleRightRotation(NODEPTR pivot);
	void singeLeftRotation(NODEPTR pivot);
	int getDiff(NODEPTR current);
	unsigned int getHeight(NODEPTR current);
	friend std::ostream& print(std::ostream& os, const NODEPTR current, unsigned int index);

public:
	//void print(std::ostream& os, NODEPTR current, unsigned int index);
	bool insert(int key, std::string value);
	unsigned int getHeight();
	unsigned int getSize();
	std::vector<std::string> recursiveFindRange(NODEPTR root, std::vector<std::string>, int lowkey, int highkey);
	bool find(int key, std::string& value);
	std::vector<std::string> findRange(int lowkey, int highkey);
	friend std::ostream& print(std::ostream& os,const NODEPTR current, unsigned int index) {
		//print right subtree
		if (current->right != nullptr) {
			print(os, current->right, index + 1);
		}
		//indent correct number of tabs
		for (size_t i = 0; i < index; i++) {
			os << "\t";
		}
		//print current node
		os << current->key << " , " << current->value << std::endl;
		//print left subtree
		if (current->left != nullptr) {
			print(os, current->left, index + 1);
		}
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const AVLTree& me) {	
		if (me.root == nullptr){
			return os << "Empty Tree" << std::endl;
		}
		return print(os, me.root, 0);
	}
	//empty constructor
	AVLTree() {
		root = nullptr;
		size = 0;
	}
	//overload = constructor
	AVLTree& operator = (AVLTree& rhs) {
		clear(root);
		root = nullptr;
		size = rhs.getSize();
		root = copy(rhs.root, root);
		return *this;
	}
	//copy constructor
	AVLTree(AVLTree& rhs) {
		root = nullptr;
		size = rhs.getSize();
		root = copy(rhs.root, root);
	}
	//use for copy constructor to copy the tree
	NODEPTR copy(NODEPTR oldNode, NODEPTR parent) {
		if (oldNode == nullptr) {
			return nullptr;
		}
		NODEPTR copyNode = new Node(oldNode->key, oldNode->value, parent);
		copyNode->left = copy(oldNode->left, copyNode);
		copyNode->right = copy(oldNode->right, copyNode);
		return copyNode;
	}
	//delete tree
	~AVLTree() {
		clear(root);
	}
	//used for deleting tree
	void clear(NODEPTR current) {
		if (current == nullptr) {
			return;
		}
		//delete left subtree
		clear(current->left);
		//delete right subtree
		clear(current->right);
		size--;
		//delete tree
		delete current;
	}
};
//used to add a node
inline bool AVLTree::insert(int key, std::string value) {
	size++;
	//check for empty tree
	if (root == nullptr) {
		root = new Node(key, value, nullptr);
		return true;
	}
	return recursiveInsert(root, key, value);
}
inline bool AVLTree::recursiveInsert(NODEPTR current, int key, std::string value) {
	//check for same key
	if (current->key == key) {
		return false;
	}
	//check for greater than current
	if (current->key < key) {
		//checks for ready to insert
		if (current->right == nullptr) {
			current->right = new Node(key, value, current);
			//balance the tree
			balance(current);
			return true;
		}
		//keep tranversing until bottom of tree
		return recursiveInsert(current->right, key, value);
	}
	//go left of current 
	//check for ready to insert
	if (current->left == nullptr) {
		current->left = new Node(key, value, current);
		//balance the tree
		balance(current);
		return true;
	}
	//keep traversing
	return recursiveInsert(current->left, key, value);
}
inline void AVLTree::balance(NODEPTR current) {
	//check if current = root->parent
	if (current == nullptr) {
		return;
	}
	////calculate the difference between left and right
	int tmp = getDiff(current);
	if (tmp == -2) {
		//unbalnced right		
		if (getDiff(current->right) < 0) {
			//unbalanced right right
			singeLeftRotation(current);
		}
		else {
			//unbalanced right left
			singleRightRotation(current->right);
			singeLeftRotation(current);
		}
	}
	//unbalance left
	if (tmp == 2) {
		if (getDiff(current->left) > 0) {
			//unbalnced left left
			singleRightRotation(current);
		}
		else {
			//unbalanced left right
			singeLeftRotation(current->left);
			singleRightRotation(current);
		}
	}
	//balance up the tree
	balance(current->parent);
}
inline void AVLTree::singleRightRotation(NODEPTR pivot) {
	//pivot->left = pivot->left->right
	//pivot->parent->left/right = pivot left
	//pivot->left->right = pivot
	NODEPTR tmp = pivot->left;
	pivot->left = tmp->right;
	tmp->right = pivot;
	if (pivot->parent != nullptr) {
		if (pivot->parent->left == pivot) {
			pivot->parent->left = tmp;
		}
		else {
			pivot->parent->right = tmp;
		}
	}
	else {
		//rotate root
		//root pivot
		root = tmp;
		tmp->parent = nullptr;
	}
	//reassign parent pointer
	if (pivot->right != nullptr) {
		pivot->right->parent = pivot;
	}
	tmp->parent = pivot->parent;
	pivot->parent = tmp;
}
inline void AVLTree::singeLeftRotation(NODEPTR pivot) {
	NODEPTR tmp = pivot->right;
	pivot->right = tmp->left;
	tmp->left = pivot;
	if (pivot->parent != nullptr) {
		if (pivot->parent->left == pivot) {
			pivot->parent->left = tmp;
		}
		else {
			pivot->parent->right = tmp;
		}
	}
	else {
		//rotate root
		//root pivot
		root = tmp;
		tmp->parent = nullptr;
	}
	//reassign parent pointers
	if (pivot->right != nullptr) {
		pivot->right->parent = pivot;
	}
	tmp->parent = pivot->parent;
	pivot->parent = tmp;
}
inline unsigned int AVLTree::getHeight() {
	return getHeight(root);
}
inline unsigned int AVLTree::getHeight(NODEPTR current) {
	int tmp = 0;
	if (current != nullptr) {
		//gets the height of left subtree
		unsigned int left = getHeight(current->left);
		//gets the height of right subtree
		unsigned int right = getHeight(current->right);
		tmp = 1 + std::max(left, right);
	}
	return tmp;
}
inline bool AVLTree::find(int key, std::string& value) {
	return recursiveFind(root, key, value);
}
inline bool AVLTree::recursiveFind(NODEPTR current, int key, std::string &value) {
	if (current == nullptr) {
		return false;
	}
	//correct value
	if (current->key == key) {
		value = current->value;
		return true;
	}
	//check left subtree
	if (recursiveFind(current->left, key, value)) {
		return true;
	}
	//checks right subtree
	return recursiveFind(current->right, key, value);
}
inline int AVLTree::getDiff(NODEPTR current) {
	//gets height of left subtree
	int left = getHeight(current->left);
	//gets height of right subtree
	int right = getHeight(current->right);
	//find the difference
	return left - right;
}
inline unsigned int AVLTree::getSize() {
	return size;
}
inline std::vector<std::string> AVLTree::recursiveFindRange(NODEPTR current, std::vector<std::string> tmp, int lowkey, int highkey) {
	//key greater than low value
	if (lowkey <= current->key) {
		if (current->left != nullptr) {
			tmp = recursiveFindRange(current->left, tmp, lowkey, highkey);
		}
		//key inside range
		if (highkey >= current->key) {
			tmp.push_back(current->value);
		}

	}
	//gets the upper range
	if (highkey >= current->key) {
		if (current->right != nullptr) {
			tmp = recursiveFindRange(current->right, tmp, lowkey, highkey);
		}
	}
	return tmp;
}
inline std::vector<std::string> AVLTree::findRange(int lowkey, int highkey) {
	//if highKey < key then dont traverse right
	//if lowKey > key then dont traverse left
	//Left-root-right traversal

	std::vector<std::string> tmp;
	if (root == nullptr){
		return tmp;
	}
	return recursiveFindRange(root, tmp, lowkey, highkey);

}
