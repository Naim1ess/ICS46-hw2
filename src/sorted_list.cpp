#include "sorted_list.h"
#include <iostream>
#include "Timer.h"
#include <fstream>

using namespace std;

int SortedArrayList::find_index(const string &word) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (buf[mid] == word) {
            return mid;
        }
        else if (buf[mid] < word) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low; // Not found
}

void SortedArrayList::copy_down(int hole) {
    for (int i = size; i>hole; --i) {
        buf[i]=buf[i-1];
    }
}
void SortedArrayList::copy_up(int hole) {
    for (int i = hole; i<size-1; i++) {
        buf[i]=buf[i+1];
    }
    buf[size-1] = "";
}


SortedArrayList::SortedArrayList(int cap) : SortedList("SortedArrayList") {
    this->capacity = cap;
    this->size = 0;
    this->buf = new string[capacity];
}
void SortedArrayList::insert(const string & word) {
    if (size==0) {
        buf[0] = word;
        size++;
        return;
    }
    int wordindex = find_index(word);
    copy_down(wordindex);
    buf[wordindex] = word;
    size++;
}
bool SortedArrayList::find(const string & word) {
    int index = find_index(word);
    if (index>=size || buf[index] != word) {
        return false;
    } else {
        return true;
    }
}
void SortedArrayList::remove(const string & word) {
    int index=find_index(word);
    if (buf[index] != word){
        return;
    }
    if (size==1) {
        size=0;
        return;
    }
    copy_up(index);
    size--;
}
bool SortedArrayList::is_empty() {
    return size==0;
}
bool SortedArrayList::is_full() {
    return size==capacity;
}
void SortedArrayList::print(ostream & out) {
    for (int i=0; i<size; ++i) {
        out << buf[i] << " ";
    }
}
SortedArrayList::~SortedArrayList() {
    delete[] buf;
}

//ListNode
void ListNode::print(ostream & out, ListNode * L) {
    out << L->data;
}
ListNode * ListNode::find(const string & word, ListNode * L) {
    for (ListNode *p=L;p;p=p->next) {
        if (p->data == word) {
            return p;
        }
        else if (p->data >word) {
            return nullptr;
        }
    }
    return nullptr;
}
void ListNode::delete_list(ListNode * L) {
    while (L != nullptr) {
        ListNode *node = L;
        L = L->next;
        delete node;
    }
}
void ListNode::remove(const string & word, ListNode * & L) {
    if (L == nullptr) {
        return;
    }
    ListNode * prev = nullptr;
    for (ListNode *p=L; p!=nullptr; p=p->next) {
        if (p->data == word) {
            if (prev == nullptr) {
                L = p->next;
            } else {
                prev->next = p->next;
            }
            delete p;
            return;
        }
        prev = p;
    }
}

//SortedLinkedList

SortedLinkedList::SortedLinkedList() : SortedList(string("SortedLinkedList")) {
    head = nullptr;
}
void SortedLinkedList::insert(const string& word) {
    ListNode* new_node = new ListNode(word, NULL);

    if (head == nullptr) {
        head = new_node;
        return;
    }

    if (word < head->data) {
        new_node->next = head;
        head = new_node;
        return;
    }

    ListNode* prev = head;
    ListNode* curr = head->next;
    while (curr != nullptr && curr->data < word) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = new_node;
    new_node->next = curr;
}
bool SortedLinkedList::find(const string & word) {
    return ListNode::find(word, head) != nullptr;
}
void SortedLinkedList::remove(const string & word) {
    ListNode::remove(word, head);
}
bool SortedLinkedList::is_empty() {
    return head==NULL;
}
bool SortedLinkedList::is_full() {
    return false;
}
void SortedLinkedList::print(ostream & out) {
    for(auto e: *this) {
        out << e << ' ';
    }
}
SortedLinkedList::~SortedLinkedList() {
    ListNode::delete_list(head);
    head = nullptr;
}

void error(string word, string msg) {
    cout << word << msg << endl;
}

void insert_all_words(int k, string file_name, SortedList & L) {
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
void find_all_words(int k, string file_name, SortedList & L) {
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
void remove_all_words(int k, string file_name, SortedList & L) {
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
void measure_SortedList_methods(string file_name, SortedList & L) {
    cout << L.name << endl;
    for (int K=1; K<=10; ++K) {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if ( !L.is_empty()) {
            error(L.name, "is not empty");
        }
    }
}
void measure_lists(string input_file) {
    int maxlen = 45392;
    SortedArrayList SAL = SortedArrayList(maxlen);
    measure_SortedList_methods(input_file, SAL);
    SortedLinkedList SLL;
    measure_SortedList_methods(input_file, SLL);
}

ostream & operator << (ostream & out, SortedList & L) {
    L.print(out);
    return out;
}
