#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <queue>


class ElementNotFoundException : public std::runtime_error 
{
public:
	explicit ElementNotFoundException(const std::string & err) : std::runtime_error(err) {}
};




template<typename Key, typename Value>
class CrumpleTree
{
	struct Node {
	Key key;
	Value value;
	Node* left;
	Node* right;
	Node* parent;
	int level;

	Node(Key k, Value v, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, int lv = 0) : 
    	key(k), value(v), left(l), right(r), parent(p), level(lv) {}
	};

private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	Node* root;
	size_t tree_size;

public:
	CrumpleTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	CrumpleTree(const CrumpleTree & st);
	//	CrumpleTree & operator=(const CrumpleTree & st);
	

	// The destructor is required.
	~CrumpleTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// returns the level on which the node with this key resides.
	// If !contains(k), this will throw an ElementNotFoundException
	unsigned getLevel(const Key & k) const;

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const CrumpleTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the balancing operation(s) if needed
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);


	// Deletes the given key from the tree
	// and performs the balancing operation(s) if needed.
	// If the key does not exist in the tree, 
	// do not modify the tree.
	void remove(const Key &k);


	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


	//Added Functions:
	Node* find_node(const Key & k) const;

	void printTree() const;
	void printTreeHelper(Node* node) const;

	void inOrder_Helper(Node* cur, std::vector<Key> in_order_keys) const;
	void preOrder_Helper(Node* cur, std::vector<Key>& pre_order_keys) const;
	void postOrder_Helper(Node* cur, std::vector<Key>& post_order_keys) const;

	void case5Left(Node*& f_node, Node*& b_node);
	void case3Left(Node*& f_node, Node*& b_node);

	void Node_Shape(Node* node, unsigned& l_dist, unsigned& r_dist);


	//TEMP:
	void leftRotate(Node* current);
	void rightRotate(Node* current);
	void caseFiveRight(Node* current);
	void caseFiveLeft(Node* current);

	// Declaration of private member functions for rebalancing
    void processRebalanceCases(Node*& focusNode, Node* grandParent);
    void checkAndHandleCase5(Node*& focusNode);
    void checkAndHandleCase3(Node*& focusNode);
    void adjustLevelsAfterCase(Node*& focusNode);
    void updateFocusNode(Node*& focusNode);

	//
	void deleteTree(Node* node);
	void destroyNode(Node* nodeToDelete);
	Node* findInorderSuccessor(Node* node);
	void rebalanceAfterDeletion(Node* focusNode);
	int getBalanceFactor(Node* node);
	void swapNodes(Node* node1, Node* node2); 
};


template<typename Key, typename Value>
CrumpleTree<Key,Value>::CrumpleTree()
{
	root = nullptr;
	tree_size = 0;
}

template<typename Key, typename Value>
CrumpleTree<Key,Value>::~CrumpleTree()
{
	  deleteTree(this->root);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::deleteTree(Node* node) {
    if (node != nullptr) {
        // Recursively delete left and right subtrees
        deleteTree(node->left);
        deleteTree(node->right);

        // Delete the current node
        delete node;
    }
}

template<typename Key, typename Value>
size_t CrumpleTree<Key, Value>::size() const noexcept
{
	//Update size after insertion & deletion
	return tree_size;
}

template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::isEmpty() const noexcept
{
	return tree_size == 0;
}


template<typename Key, typename Value>
bool CrumpleTree<Key, Value>::contains(const Key &k) const noexcept
{
	try {
        Node* node = find_node(k);
        return (node != nullptr);
    } catch (const ElementNotFoundException& e) {
        // Key not found
        return false;
    }
}

template<typename Key, typename Value>
unsigned CrumpleTree<Key, Value>::getLevel(const Key & k) const
{
	//levels updated within insert & remove.
	Node* node = find_node(k);
	return node->level;
}


template<typename Key, typename Value>
Value & CrumpleTree<Key, Value>::find(const Key & k)
{
	Node* cur = this->root;
	while (cur != nullptr) {
		if (k == cur->key) {
			return cur->value; // Found
		}
		else if (k < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	throw ElementNotFoundException("Key Not Found!");
}

template<typename Key, typename Value>
const Value & CrumpleTree<Key, Value>::find(const Key & k) const
{
	Node* cur = this->root;
	while (cur != nullptr) {
		if (k == cur->key) {
			return cur->value; // Found
		}
		else if (k < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	throw ElementNotFoundException("Key Not Found!");
}

template<typename Key, typename Value>
typename CrumpleTree<Key, Value>::Node* CrumpleTree<Key, Value>::find_node(const Key & k) const
{
    Node* cur = this->root;
    while (cur != nullptr) {
        if (k == cur->key) {
            return cur; // Found, return the pointer
        }
        else if (k < cur->key) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    throw ElementNotFoundException("Key Not Found!");
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::insert(const Key & k, const Value & v)
{
    Node* currentNode = root;
    Node* parentNode = nullptr;
    bool isLeftChild = false;

    // Traverse from root to find the correct insertion point
    while (currentNode != nullptr) {
        parentNode = currentNode;
        if (k < currentNode->key) {
            currentNode = currentNode->left;
            isLeftChild = true;
        } else {
            currentNode = currentNode->right;
            isLeftChild = false;
        }
    }

    // Initialize new node at level 1
    Node* newNode = new Node(k, v, nullptr, nullptr, parentNode, 1);

    // Handle the case where the tree was previously empty
    if (parentNode == nullptr) {
        root = newNode;
        ++tree_size;
        return;
    }

    // Link the new node to its parent
    if (isLeftChild) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }
    ++tree_size;

    // Start rebalancing from the new node upwards
    Node* focusNode = newNode;
    while (focusNode->parent != nullptr) {
        Node* grandParent = focusNode->parent->parent;

        if (focusNode->level == focusNode->parent->level) {
            // Handle various cases of tree rebalancing
            processRebalanceCases(focusNode, grandParent);
        } else {
            focusNode = focusNode->parent;
        }
    }
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::processRebalanceCases(Node*& focusNode, Node* grandParent) {
    // Consolidate common operations and simplify conditionals
    Node* parent = focusNode->parent;

    if (grandParent && parent->level == grandParent->level - 2) {
        // Case 1 (2, 1) or (2, 2)
        parent->level++;
        return;
    }

    if (parent->level == 1 || 
        (parent->right && parent->level - parent->right->level == 1) ||
        (parent->left && parent->level - parent->left->level == 1)) {
        // Case 2 (1, 1)
        parent->level++;
        focusNode = parent;
        return;
    }

	// Check if Case 3 applies
    checkAndHandleCase3(focusNode);
    // Check if Case 5 applies
    checkAndHandleCase5(focusNode);

    focusNode = parent;  // Move up the tree for the next iteration
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::checkAndHandleCase5(Node*& focusNode) {

    if (!focusNode || !focusNode->parent) {
        // Either focusNode or its parent is null, cannot proceed
        return;
    }

    // Case 5 left rising
    if (focusNode->left && focusNode->parent->right && 
        focusNode->level - focusNode->left->level == 2 && 
        focusNode->parent->level - focusNode->parent->right->level == 2) {
        caseFiveRight(focusNode);
        focusNode->level--;
        focusNode->parent->level++;
        if (focusNode->parent->right) {  // Additional check for safety
            focusNode->parent->right->level--;
        }
    }

    // Case 5 right rising
    else if (focusNode->right && focusNode->parent->left && 
             focusNode->level - focusNode->right->level == 2 && 
             focusNode->parent->level - focusNode->parent->left->level == 2) {
        caseFiveLeft(focusNode);
        focusNode->level--;
        focusNode->parent->level++;
        if (focusNode->parent->left) {  // Additional check for safety
            focusNode->parent->left->level--;
        }
    }

    // Move up the tree for the next iteration
    updateFocusNode(focusNode);
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::checkAndHandleCase3(Node*& focusNode) {

    Node* parent = focusNode->parent;

    // Case 3 (2, 1) right rising
    if ((parent->left && parent->level - parent->left->level == 2) || 
        (parent->level == 2 && !parent->left)) {
        if ((focusNode->left && focusNode->level - focusNode->left->level == 2) || 
            (!focusNode->left && focusNode->level == 2)) {
            parent->level--;
            leftRotate(focusNode);
        } else if (focusNode->left && focusNode->level - focusNode->right->level == 1) {
            caseFiveLeft(focusNode);
            adjustLevelsAfterCase(focusNode);
        }
    }

    // Case 3 (1, 2) left rising
    else if ((parent->right && parent->level - parent->right->level == 2) || 
             (parent->level == 2 && !parent->right)) {
        if ((focusNode->right && focusNode->level - focusNode->right->level == 2) || 
            (!focusNode->right && focusNode->level == 2)) {
            parent->level--;
            rightRotate(focusNode);
        } else if (focusNode->right && focusNode->level - focusNode->left->level == 1) {
            caseFiveRight(focusNode);
            adjustLevelsAfterCase(focusNode);
        }
    }

    // Update focusNode to its parent for next iteration
    updateFocusNode(focusNode);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::adjustLevelsAfterCase(Node*& focusNode) {
    focusNode->level--;
    focusNode->parent->level++;
    if (focusNode == focusNode->parent->left) {
        focusNode->parent->right->level--;
    } else {
        focusNode->parent->left->level--;
    }
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::updateFocusNode(Node*& focusNode) {
    if (focusNode->parent) {
        focusNode = focusNode->parent;
    } else {
        focusNode = nullptr;  // Reached the root, end iteration
    }
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::leftRotate(Node* current) {
    Node* parent = current->parent;
    Node* grandparent = parent->parent;

    // Update parent's right child
    parent->right = current->left;
    if (current->left) {
        current->left->parent = parent;
    }

    // Make the current node the new child of its grandparent
    current->left = parent;
    parent->parent = current;

    // Adjust the child pointers of the grandparent
    if (grandparent) {
        if (parent == grandparent->left) {
            grandparent->left = current;
        } else {
            grandparent->right = current;
        }
    } else {
        // Make current the new root if there is no grandparent
        root = current;
    }

    // Update current's parent to grandparent
    current->parent = grandparent;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::rightRotate(Node* current) {
    Node* parent = current->parent;
    Node* grandparent = parent->parent;

    // Update parent's left child to current's right child
    parent->left = current->right;
    if (current->right) {
        current->right->parent = parent;
    }

    // Make the current node the new child of its grandparent
    current->right = parent;
    parent->parent = current;

    // Adjust the child pointers of the grandparent
    if (grandparent) {
        if (parent == grandparent->left) {
            grandparent->left = current;
        } else {
            grandparent->right = current;
        }
    } else {
        // Make current the new root if there is no grandparent
        root = current;
    }

    // Update current's parent to grandparent
    current->parent = grandparent;
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::caseFiveRight(Node* current){
    Node* parent = current->parent;
    Node* grandparent = parent->parent;
    Node* rightChild = current->right;
    Node* rightChildLeft = rightChild ? rightChild->left : nullptr;  // Check for null
    Node* rightChildRight = rightChild ? rightChild->right : nullptr;  // Check for null

    //Assign current to left child of its right child
    rightChild->left = current;
    current->parent = rightChild;

    //Assign current's right child to the left child of its right child
    current->right = rightChildLeft;
    if (rightChildLeft){
        rightChildLeft->parent = current;
    }

    //Assign current's parent as the right child of its right child
    rightChild->right = parent;
    parent->parent = rightChild;

    parent->left = rightChildRight;
    if (rightChildRight){
        rightChildRight->parent = parent;
    }

    //Reassign grandparent pointers
    if (grandparent) {
        if (current == grandparent->left) {
            grandparent->left = rightChild;
        } else {
            grandparent->right = rightChild;
        }
    } else {
        // If there's no grandparent, rightChild becomes the new root
        root = rightChild;
    }

    rightChild->parent = grandparent;
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::caseFiveLeft(Node* current){
    Node* parent = current->parent;
    Node* grandparent = parent->parent;
    Node* leftChild = current->left;
    Node* leftChildRight = leftChild ? leftChild->right : nullptr;  // Check for null
    Node* leftChildLeft = leftChild ? leftChild->left : nullptr;    // Check for null

    // Ensure leftChild is not null before proceeding
    if (!leftChild) {
        return;  // Or handle the error appropriately
    }

    //Assign current to right child of its left child
    leftChild->right = current;
    current->parent = leftChild;

    //Assign current's left child to the right child of its left child
    current->left = leftChildRight;
    if (leftChildRight) {
        leftChildRight->parent = current;
    }

    //Assign current's parent as the left child of current's left child
    leftChild->left = parent;
    parent->parent = leftChild;

    parent->right = leftChildLeft;
    if (leftChildLeft) {
        leftChildLeft->parent = parent;
    }

    //Reassign grandparent pointers
    if (grandparent) {
        if (parent == grandparent->left) {
            grandparent->left = leftChild;
        } else {
            grandparent->right = leftChild;
        }
    } else {
        // If there's no grandparent, leftChild becomes the new root
        root = leftChild;
    }

    leftChild->parent = grandparent;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::remove(const Key &k) {
    Node* nodeToDelete = find_node(k);  // Use your existing find_node method

    if (!nodeToDelete) {
        // Node not found, exit the function
        return;
    }

    // If the node is not a leaf, find its inorder predecessor or successor
	bool isLeaf = false;
	if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) isLeaf = true;

    if (isLeaf) {
        Node* replacement = findInorderSuccessor(nodeToDelete);
        // Swap the contents of nodeToDelete and replacement
        swapNodes(nodeToDelete, replacement);
        // Now, nodeToDelete becomes the leaf or a node with a single child
        nodeToDelete = replacement;
    }

    // Node destruction phase
    destroyNode(nodeToDelete);

    // Rebalancing phase
    rebalanceAfterDeletion(nodeToDelete);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::swapNodes(Node* node1, Node* node2) {
    if (node1 == nullptr || node2 == nullptr) return;

    // Swap keys
    Key tempKey = node1->key;
    node1->key = node2->key;
    node2->key = tempKey;

    // Swap values
    Value tempValue = node1->value;
    node1->value = node2->value;
    node2->value = tempValue;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::rebalanceAfterDeletion(Node* focusNode) {
    // Check the current configuration of the focusNode and apply the appropriate case

    while (focusNode != nullptr) {
        // Update the distances from focusNode to its children
        unsigned f_l_dist, f_r_dist;
        Node_Shape(focusNode, f_l_dist, f_r_dist);

        // Case 1A & 1B
        if ((f_l_dist == 1 && f_r_dist == 1) || (f_l_dist == 1 && f_r_dist == 2)) {
            // Apply case 1A or 1B logic
            break; // Done with rebalancing
        }

        // Case 2
        if (f_l_dist == 3 && f_r_dist == 2) {
            // Apply case 2 logic
            focusNode->level--; // f falls to become (2, 1)
            focusNode = focusNode->parent; // Move up the tree
            continue;
        }

        // Check for the state of focusNode's parent (j) to decide on cases 3, 4, 5, 6
        Node* j = focusNode->parent;
        if (j) {
            unsigned j_l_dist, j_r_dist;
            Node_Shape(j, j_l_dist, j_r_dist);

            // Case 3
            if (j_l_dist == 1 && j_r_dist == 1) {
                // Apply single rotation
            }

            // Case 4A & 4B
            if (j_l_dist == 2 && j_r_dist == 1) {
                // Apply case 4 logic
            }

            // Case 5
            if (j_l_dist == 1 && j_r_dist == 2) {
                // Apply double rotation
            }

            // Case 6
            if (j_l_dist == 2 && j_r_dist == 2) {
                // Apply case 6 logic
            }
        }

        focusNode = focusNode->parent; // Move up the tree for the next iteration
    }
}

// Helper function to get the balance factor of a node
template<typename Key, typename Value>
int CrumpleTree<Key, Value>::getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}


template<typename Key, typename Value>
typename CrumpleTree<Key, Value>::Node* CrumpleTree<Key, Value>::findInorderSuccessor(Node* node) {
    if (!node) return nullptr;

    Node* successor = nullptr;
    if (node->right) {
        // The successor is the smallest node in the right subtree
        successor = node->right;
        while (successor->left) {
            successor = successor->left;
        }
    } else {
        // Walk up the tree
        Node* curr = node;
        while (curr->parent && curr == curr->parent->right) {
            curr = curr->parent;
        }
        successor = curr->parent;
    }
    return successor;
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::destroyNode(Node* nodeToDelete) {
    if (!nodeToDelete) return;

    Node* child = nodeToDelete->left ? nodeToDelete->left : nodeToDelete->right;

    if (nodeToDelete->parent) {
        // Link the child to the parent of the node to delete
        if (nodeToDelete == nodeToDelete->parent->left) {
            nodeToDelete->parent->left = child;
        } else {
            nodeToDelete->parent->right = child;
        }
    } else {
        // Deleting the root node
        root = child;
    }

    if (child) {
        child->parent = nodeToDelete->parent;
    }

    delete nodeToDelete;
    --tree_size; // Update the size of the tree
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::Node_Shape(Node* node, unsigned& l_dist, unsigned& r_dist) {
	if (node->left == nullptr) {
		l_dist = node->level;
	} else {
		l_dist = node->level - node->left->level;
	}

	if (node->right == nullptr) {
		r_dist = node->level;
	} else {
		r_dist = node->level - node->right->level;
	}
}



template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::inOrder() const
{	
	std::vector<Key> in_order_keys;
	inOrder_Helper(root, in_order_keys);
	return in_order_keys; 
}


template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::preOrder() const
{
	std::vector<Key> pre_order_keys;
    preOrder_Helper(root, pre_order_keys);
    return pre_order_keys;
}


template<typename Key, typename Value>
std::vector<Key> CrumpleTree<Key, Value>::postOrder() const
{
	std::vector<Key> post_order_keys;
    postOrder_Helper(root, post_order_keys);
    return post_order_keys; 
}


template<typename Key, typename Value>
void CrumpleTree<Key, Value>::inOrder_Helper(Node* cur, std::vector<Key> in_order_keys) const
{
	if (cur == nullptr) // Base
		return;         

	inOrder_Helper(cur->left, in_order_keys);   // "L"  
	in_order_keys.push_back(cur->key);    // "Cur"
	inOrder_Helper(cur->right, in_order_keys);  // "R"
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::preOrder_Helper(Node* cur, std::vector<Key>& pre_order_keys) const {
    if (cur == nullptr) {
        return;
    }

    pre_order_keys.push_back(cur->key);    // "Cur"
    preOrder_Helper(cur->left, pre_order_keys);   // "L"
    preOrder_Helper(cur->right, pre_order_keys);  // "R"
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::postOrder_Helper(Node* cur, std::vector<Key>& post_order_keys) const {
    if (cur == nullptr) {
        return;
    }

    postOrder_Helper(cur->left, post_order_keys);   // "L"
    postOrder_Helper(cur->right, post_order_keys);  // "R"
    post_order_keys.push_back(cur->key);    // "Cur"
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::printTree() const {
	printTreeHelper(this->root);
}

template<typename Key, typename Value>
void CrumpleTree<Key, Value>::printTreeHelper(Node* node) const {
        if (node == nullptr) return;

        std::queue<Node*> queue;
        queue.push(node);

        while (!queue.empty()) {
            int levelSize = queue.size();

            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = queue.front();
                queue.pop();

                std::cout << "(" << currentNode->key << ", lv:" << currentNode->level << ") ";

                if (currentNode->left != nullptr)
                    queue.push(currentNode->left);
                if (currentNode->right != nullptr)
                    queue.push(currentNode->right);
            }

            std::cout << std::endl; // New line after each level
        }
    }

#endif 