#include "bstree.h"

Node * BSTree::insert_node(Node * t, string key) {
    if (t == nullptr) {
        t = new Node(key);
    } else if (key < t->key) {
        t->left = insert_node(t->left, key);
    } else if (key > t->key) {
        t->right = insert_node(t->right, key);
    }
    t->height = compute_height(t);
    return t;
}

Node * BSTree::find_node(Node * t, string key) {
    if (t == nullptr) {
        return nullptr;
    } else if (key < t->key) {
        return find_node(t->left, key);
    } else if (key > t->key) {
        return find_node(t->right, key);
    } else {
        return t;
    }
}

Node * BSTree::left_most(Node * t) {
    if (t == nullptr) {
        return nullptr;
    } else if (t->left == nullptr) {
        return t;
    } else {
        return left_most(t->left);
    }
}

Node * BSTree::delete_node(Node * t, string key) {
    if (t == nullptr) {
        return nullptr;
    } else if (key < t->key) {
        t->left = delete_node(t->left, key);
    } else if (key > t->key) {
        t->right = delete_node(t->right, key);
    } else {  // key == t->key
        if (t->left == nullptr && t->right == nullptr) {
            delete t;
            t = nullptr;
        } else if (t->left == nullptr) {
            Node *temp = t;
            t = t->right;
            delete temp;
        } else if (t->right == nullptr) {
            Node *temp = t;
            t = t->left;
            delete temp;
        } else {
            Node *temp = left_most(t->right);
            t->key = temp->key;
            t->right = delete_node(t->right, temp->key);
        }
    }
    if (t != nullptr) {
        t->height = compute_height(t);
    }
    return t;
}

int BSTree::compute_height(Node * t) {
    if (t == nullptr) {
        return 0;
    } else {
        int left_height = (t->left != nullptr) ? t->left->height : 0;
        int right_height = (t->right != nullptr) ? t->right->height : 0;
        return 1 + max(left_height, right_height);
    }
}

BSTree::BSTree() : BST("BSTree") {}

void BSTree::insert(const string & key) {
    root = insert_node(root, key);
    count++;
}

bool BSTree::find(const string & key) const {
    return find_node(root, key) != nullptr;
}

void BSTree::remove(const string & key) {
    root = delete_node(root, key);
    count--;
}

bool BSTree::is_empty() const {
    return root == nullptr;
}

int BSTree::get_height() const {
    return compute_height(root);
}
