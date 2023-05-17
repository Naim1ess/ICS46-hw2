#ifndef BST_H
#define BST_H
#include <stack>

#include <iostream>
using namespace std;

// constexpr int NWORDS = 45;
constexpr int NWORDS = 45392;

struct Node
{
    string key;
    int value;
    Node * left, * right;
    int height;
    Node(const string & new_key, Node * new_left=nullptr, Node * new_right=nullptr)
        : key(new_key),
          value(0), // for map, BST needs both key and value, but ignore for our measurement
          left(new_left), right(new_right),
          height(1)
    { }

};

struct BST
{
    Node * root;
    const string name;
    int count;

    BST(const string & new_name)
        : root(nullptr), name(new_name), count(0) { }

    virtual void insert( const string & word) = 0;
    virtual bool find( const string & word ) const = 0;
    virtual void remove( const string & word ) = 0;

    virtual bool is_empty() const = 0;
    virtual int size() const { return count; }
    virtual int get_height() const = 0;

    static void pre_order_print(ostream & out, Node * t);
    static void in_order_print(ostream & out, Node * t);
    static void post_order_print(ostream & out, Node * t);

    void print(ostream & out) const
    {
        pre_order_print(out, root);
        in_order_print(out, root);
        post_order_print(out, root);
    }

    virtual ~BST(); // must delete any Nodes in the tree pointed to by root
    void clear(Node* node);
    BST(const BST & L) = delete;
    BST& operator =(const BST & L) = delete;

    class iterator {
    stack<Node*> stk;
    void push_left(Node* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = string;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = std::ptrdiff_t;

    explicit iterator(Node * const ptr = nullptr) {
        push_left(ptr);
    }

    iterator & operator ++ () {
        Node* node = stk.top();
        stk.pop();
        push_left(node->right);
        return *this;
    }

    iterator operator ++ (int) {
        iterator tmp(*this);
        operator++();
        return tmp;
    }

    reference operator * () const {
        return stk.top()->key;
    }

    pointer operator -> () const {
        return &stk.top()->key;
    }

    bool operator == (const iterator & other) const {
        return stk == other.stk;
    }

    bool operator != (const iterator & other) const {
        return stk != other.stk;
    }
    };

    BST::iterator begin() {
        return iterator(root);
    }

    BST::iterator end() {
        return iterator();
    }
};


ostream & operator << (ostream & out, BST & L) {
    L.print(out);
    return out;
}

void error(string word, string msg);
void insert_all_words(int k, string file_name, BST & L);
void find_all_words(int k, string file_name, BST & L);
void remove_all_words(int k, string file_name, BST & L);
void measure_BST(string file_name, BST & L);
void measure_BSTs(string input_file);

#endif
