#include "avltree.h"

int AVLTree::get_height(Node * node) {
    if(node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::get_balance(Node * node) {
    if(node == nullptr)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::set_height(Node * node) {
    if(node != nullptr) {
        node->height = 1 + max(get_height(node->left), get_height(node->right));
    }
}

Node * AVLTree::right_rotate(Node * y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    set_height(y);
    set_height(x);
    return x;
}

Node * AVLTree::left_rotate(Node * x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    set_height(x);
    set_height(y);
    return y;
}

Node * AVLTree::rebalance(Node * t) {
    set_height(t);
    int balance = get_balance(t);

    if (balance > 1 && get_balance(t->left) >= 0)
        return right_rotate(t);
 
    if (balance > 1 && get_balance(t->left) < 0) {
        t->left = left_rotate(t->left);
        return right_rotate(t);
    }
 
    if (balance < -1 && get_balance(t->right) <= 0)
        return left_rotate(t);
 
    if (balance < -1 && get_balance(t->right) > 0) {
        t->right = right_rotate(t->right);
        return left_rotate(t);
    }

    return t;
}

Node * AVLTree::insert_node(Node * t, string key) {
    if (t == nullptr) {
        return new Node(key);
    } else if (key < t->key) {
        t->left = insert_node(t->left, key);
    } else if (key > t->key) {
        t->right = insert_node(t->right, key);
    } else {  // equal keys are not allowed in BST
        return t;
    }
 
    return rebalance(t);
}

Node * AVLTree::find_node(Node * t, string key) {
    if (t == nullptr || t->key == key)
        return t;

    if (t->key < key)
        return find_node(t->right, key);
 
    return find_node(t->left, key);
}

Node * AVLTree::delete_node(Node * t, string key) {
    // BST deletion
    if (t == nullptr)
        return t;
 
    if (key < t->key)
        t->left = delete_node(t->left, key);
    else if(key > t->key)
        t->right = delete_node(t->right, key);
    else {
        if( (t->left == nullptr) || (t->right == nullptr) ) {
            Node *temp = t->left ? t->left : t->right;
 
            // No child case
            if(temp == nullptr) {
                temp = t;
                t = nullptr;
            } else { // One child case
                *t = *temp;
            }
            delete temp;
        } else {
            // node with two children: get the inorder
            // successor (smallest in the right subtree)
            Node* temp = t->right;
            while (temp->left != nullptr)
                temp = temp->left;

            // copy the inorder successor's data to this node
            t->key = temp->key;

            // delete the inorder successor
            t->right = delete_node(t->right, temp->key);
        }
    }
 
    // if the tree had only one node then return
    if (t == nullptr)
        return t;

    return rebalance(t);
}


AVLTree::AVLTree() : BST("AVLTree") {}

void AVLTree::insert(const string & key) {
root = insert_node(root, key);
count++;
}

bool AVLTree::find(const string & key) const {
return find_node(root, key) != nullptr;
}

void AVLTree::remove(const string & key) {
root = delete_node(root, key);
if (root != nullptr)
count--;
}

bool AVLTree::is_empty() const {
return root == nullptr;
}

int AVLTree::get_height() const {
return get_height(root);
}
