#include "bst.h"
#include "avltree.h"
#include "bstree.h"
#include <iostream>
#include "timer.h"
#include <fstream>

void BST::pre_order_print(ostream & out, Node * t)
{
    if (t == nullptr)
        return;
    out << t->key << ' ';
    pre_order_print(out, t->left);
    pre_order_print(out, t->right);
}

void BST::in_order_print(ostream & out, Node * t)
{
    if (t == nullptr)
        return;
    in_order_print(out, t->left);
    out << t->key << ' ';
    in_order_print(out, t->right);
}

void BST::post_order_print(ostream & out, Node * t)
{
    if (t == nullptr)
        return;
    post_order_print(out, t->left);
    post_order_print(out, t->right);
    out << t->key << ' ';
}

void error(string word, string msg) {
    cout << word << msg << endl;
}
void insert_all_words(int k, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit) {
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void find_all_words(int k, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/ 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit) {
        L.find(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int k, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/ 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit) {
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void measure_BST(string file_name, BST & L) {
    cout << L.name << endl;
    for (int K=1; K<=10; ++K) {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if ( !L.is_empty()) {
            error(L.name, "is not empty");
        }
    }
}
void measure_BSTs(string input_file) {
    AVLTree AVL = AVLTree();
    measure_BST(input_file, AVL);
    BSTree BST = BSTree();
    measure_BST(input_file, BST);
}
