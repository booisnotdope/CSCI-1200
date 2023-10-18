/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iterator>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T> 
class BPlusTree	{
	public:
	//Constructor
	BPlusTree(unsigned int anum_keys);
	//Copy Constructors
	BPlusTree(BPlusTree<T> &old);
	BPlusTree<T>& operator= (BPlusTree<T> &old);

	//Destructors
	~BPlusTree();

	//Accessors
	void insert(const T &value);
	BPlusTreeNode<T>* find(const T &value);

	//Printing
	void print_sideways(std::ofstream& outfile);
	void print_BFS(std::ofstream& outfile);

	private:
	//Variables
	unsigned int num_keys;
	BPlusTreeNode<T>* root;

	//Functions
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* &old_root);	
	void destroy_tree(BPlusTreeNode<T>* &root);
	void inserter(BPlusTreeNode<T>* &node, const T &value);
	// void spliter(BPlusTreeNode<T>* &old_node);
	BPlusTreeNode<T>* finder(BPlusTreeNode<T>* &node, const T &value);

};

/////////////////////////////////////////////////////
//Constructor
template <class T>
BPlusTree<T>::BPlusTree(unsigned int a_num_keys){
	num_keys = a_num_keys;
	root = NULL;	
}
///////////////////
//Copy Constructors
template <class T>
BPlusTree<T>::BPlusTree(BPlusTree<T> &old){
	num_keys = old.num_keys;
	if (old.root == NULL) root = NULL;
	else {
		root = this -> copy_tree(old.root);
	}
}
//copy operator
template <class T>
BPlusTree<T>& BPlusTree<T>::operator= (BPlusTree<T> &old){
	num_keys = old.num_keys;;
	destroy_tree(root);
	if (old.root == NULL) root = NULL;
	else {
		root = this -> copy_tree(old.root);
	}
	return *this;
}
/////////////
//copy helper
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* &old_root){
	//Base Case
	if (old_root -> is_leaf()){
		BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>;
		for (T i: old_root -> keys){
			new_root -> keys.push_back(i);
		}
		return new_root;
	}
	
	//Recursive Case
	BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>;

	for (BPlusTreeNode<T>* i: old_root -> children){
		new_root -> children.push_back(copy_tree(i));
	}
	return new_root;
}

//////////////////////////////////////////////////////////
//Destructors
template <class T>
BPlusTree<T>::~BPlusTree(){
	this -> destroy_tree(root);
}

//Helper Destructor
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* &root){
	if (!root) return;
    for (BPlusTreeNode<T>* i: root -> children){
		destroy_tree(i);
	}
    delete root;
}

/////////////////////////////////////////////////////////
//insert funciton
template <class T>
void BPlusTree<T>::insert(const T &value){
	if (root == NULL) {
		root = new BPlusTreeNode<T>;
		root -> keys.push_back(value);
	} else {
		BPlusTreeNode<T>* leaf_node = find(value);
		inserter(leaf_node, value);
	}
}

//helper function
template <class T>
void BPlusTree<T>::inserter(BPlusTreeNode<T>* &node, const T &value){
	bool inserted = false;
	for (unsigned int i = 0; i < node -> keys.size(); i++){
		if (value < node -> keys[i]) {
			node -> keys.insert(node -> keys.begin()+i, value);
			inserted = true;
			break;
		}
	}
	if (!inserted){
		node -> keys.push_back(value);
	}

	// if (node -> keys.size() > num_keys){
	// 	spliter(node);
	// }
}

//spliter function
// template <class T>
// void BPlusTree<T>::spliter(BPlusTreeNode<T>* &old_node){
// 	BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>;
// 	if (old_node -> is_leaf()){
		
// 	}
// }

///////////////////////////////////////////////
//find function
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T &value){
	return finder(root, value);
}

//helper find
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::finder(BPlusTreeNode<T>* &node, const T &value){
	//Base Case 1
	if (node == NULL) return NULL;

	//Base Case 2
	if (node -> is_leaf()) return node;

	//Recursive Case
	for (unsigned int i = 0; i < node -> keys.size(); i++){
		if (node -> keys[i] == value) return node;
		else return finder(node -> children[i], value);		
	}
	
	return finder(node -> children[node -> children.size() - 1], value);
}

template <class T>
void BPlusTree<T>::print_sideways(std::ofstream& outfile){
	outfile << "Tree is empty." << std::endl;
}

template <class T>
void BPlusTree<T>::print_BFS(std::ofstream& outfile){
	outfile << "Tree is empty." << std::endl;
}
#endif
