#include <algorithm>

/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y = t->right;
    t->right = y->left;
    y->left = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y = t->left;
    t->left = y->right;
    y->right = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(getHeightBalance(subtree) < -1){
        if(getHeightBalance(subtree -> left) > 0){
            rotateLeftRight(subtree);
        }else{
            rotateRight(subtree);
        }
    }
    else if(getHeightBalance(subtree) > 1){
        if(getHeightBalance(subtree -> right) < 0){
            rotateRightLeft(subtree);
        }else{
            rotateLeft(subtree);
        }
    }
    
    recursive_set_height(subtree);
}

template <class K, class V>
int AVLTree<K, V>::getHeightBalance(Node* root) {
  // your code here
  if (root == NULL) {
    return 0;
  } else {
    return heightOrNeg1(root->right) - heightOrNeg1(root->left);
  }
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* node) {
  if (node == NULL) {
    return -1;
  } else {
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
  }
}

template <class K, class V>
void AVLTree<K, V>::recursive_set_height(Node* node) {
  if (node == NULL) {
    return;
  } else {
    node -> height = getHeight(node);
    recursive_set_height(node -> left);
    recursive_set_height(node -> right);
    return;
    
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL){
        subtree = new Node(key, value);
    }else if(key < subtree-> key){
        insert(subtree->left, key, value);
    }else if(key > subtree-> key){
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
    return;
    
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        Node*& left = subtree->left;
        remove(left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        Node*& right = subtree->right;
        remove(right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *curr_node = subtree->left;
            while (curr_node->right != NULL) {
                curr_node = curr_node->right;
            }
            K k_temp = curr_node -> key;
            V v_temp = curr_node -> value;
            curr_node -> key = subtree -> key;
            curr_node -> value = subtree -> value;
            subtree -> key = k_temp;
            subtree -> value = v_temp;
            remove(subtree -> left, key);
            //swap(subtree, curr_node);
        } else {
            /* one-child remove */
            // your code here
            Node* temp;
            if (subtree->left == NULL) {
                temp = subtree->right;
            } else {
                temp = subtree->left;
            }
            delete subtree;
            subtree = temp;
        }
        // your code here
        
        rebalance(subtree);
    }
}
