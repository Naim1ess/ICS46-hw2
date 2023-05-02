#include "holder.h"
#include <iostream>
#include "Timer.h"
#include <fstream>

ArrayStack::ArrayStack(int cap) : Stack("ArrayStack"), capacity(cap), size(0) {
    buf = new string[cap];
}
void ArrayStack::push(const string & word) {
    if (is_full()) {
        return;
    }
    buf[size++]=word;
}
void ArrayStack::pop() {
    size--;
}
string ArrayStack::top() {
    return buf[size -1];
}
bool ArrayStack::is_empty() {
    return size==0;
}
bool ArrayStack::is_full() {
    return size==capacity;
}
void ArrayStack::print(ostream & out) {
    for (int i = size - 1; i >= 0; i--) {
            out << buf[i] << ' ';
        }
}
ArrayStack::~ArrayStack() {
    delete[] buf;
}


void ListNode::print(ostream & out, ListNode * L) {
    for (ListNode *p=L; p!=nullptr; p=p->next) {
        out << p->data << " ";
    }
}
void ListNode::delete_list(ListNode * L) {
    while (L != nullptr) {
        ListNode *node = L;
        L = L->next;
        delete node;
    }
}


LinkedStack::LinkedStack() : Stack("LinkedStack"), head(nullptr) {}
void LinkedStack::push(const string & word) {
    /*ListNode *newNode = new ListNode(word, nullptr);
    if (head==nullptr) {
        head = newNode;
    }
    ListNode *p = head;
    while (p->next != nullptr) {}
    p->next = newNode;*/
    ListNode *newNode = new ListNode(word, head);
    head = newNode;
}
void LinkedStack::pop() {
    /*ListNode *prev = nullptr;
    ListNode *p = head;
    for (; p!=nullptr; prev=p, p=p->next) {}
    if (prev == nullptr) {
        head = nullptr;
    } else {
        prev->next = p->next;
    }*/
    head = head->next;
}
string LinkedStack::top() {
    /*if (head->next == nullptr) {
        return head->data;
    }
    ListNode *p=head;
    for (; p->next!=nullptr; p=p->next) {}
    return p->data;*/
    return head->data;
}
bool LinkedStack::is_empty() {
    return head == nullptr;
}
bool LinkedStack::is_full() {
    return false;
}
void LinkedStack::print(ostream & out) {
    for (ListNode *p=head; p!=nullptr; p=p->next) {
        out << p->data << " ";
    }
}
LinkedStack::~LinkedStack() {
    ListNode *p = head;
    while (p != nullptr) {
        ListNode *node = p;
        p = p->next;
        delete node;
    }
}

ArrayQueue::ArrayQueue(int cap) :Queue("ArrayQueue"), capacity(cap), front(0), rear(-1) {
    buf = new string[capacity];
}
void ArrayQueue::enq(const string & word) {
    if (is_full()) {
        return;
    }
    rear = (rear + 1) % capacity;
    buf[rear] = word;
}
void ArrayQueue::deq() {
    if (is_empty()) {
        return;
    }
    front = (front + 1) % capacity;
}
string ArrayQueue::next() {
    return buf[front];
}
bool ArrayQueue::is_empty() {
    return front > (rear + 1) % capacity;
}
bool ArrayQueue::is_full() {
    return front == (rear + 1) % capacity;
}
void ArrayQueue::print(ostream & out) {
    for (int i = front; i != (rear + 1) % capacity; i = (i + 1) % capacity) {
        out << buf[i] << " ";
    }
}
ArrayQueue::~ArrayQueue() {
    delete[] buf;
}


LinkedQueue::LinkedQueue() : Queue("LinkedQueue"), head(nullptr) {}
void LinkedQueue::enq(const string & word) {
    ListNode *newNode = new ListNode(word, nullptr);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}
void LinkedQueue::deq() {
    head = head->next;
}
string LinkedQueue::next() {
    return head->data;
}
bool LinkedQueue::is_empty() {
    return head == nullptr;
}
bool LinkedQueue::is_full() {
    return false;
}
void LinkedQueue::print(ostream & out) {
    ListNode *L = head;
    while (L != nullptr) {
        out << L->data << " ";
        L = L->next;
}
}
LinkedQueue::~LinkedQueue() {
    ListNode *L = head;
    while (L != nullptr) {
        ListNode *node = L;
        L = L->next;
        delete node;
    }
}

ostream & operator << (ostream & out, Holder & L) {
    L.print(out);
    return out;
}

void error(string word, string msg) {
    cout << word << msg << endl;
}
void insert_all_words(int k, string file_name, Holder & L) {
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
void remove_all_words(int k, string file_name, Holder & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS/ 10;
    t.start();
    for (; limit > 0; --limit) {
        L.remove();
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void measure_holder(string file_name, Holder & L) {
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
void measure_holders(string input_file) {
    int maxlen = 45392;
    ArrayStack AS = ArrayStack(maxlen);
    measure_holder(input_file, AS);
    LinkedStack LS = LinkedStack();
    measure_holder(input_file, LS);
    ArrayQueue AQ = ArrayQueue(maxlen);
    measure_holder(input_file, AQ);
    LinkedQueue LQ = LinkedQueue();
    measure_holder(input_file, LQ);
}








