#include "hashtable.h"
#include <iostream>
#include "Timer.h"
#include <fstream>
#include "stats.h"

ListNode* ListNode::find(std::string key, ListNode* L) {
  while (L != nullptr) {
    if (L->data == key) {
      return L;
    }
    L = L->next;
  }
  return nullptr;
}

ListNode* ListNode::insert(std::string key, ListNode* L) {
  ListNode *newNode = new ListNode(key, L);
  return newNode;
}

ListNode* ListNode::remove(std::string key, ListNode* L) {
    if (L == nullptr) {
        return L;
    }
    ListNode * prev = nullptr;
    for (ListNode *p=L; p!=nullptr; p=p->next) {
        if (p->data == key) {
            if (prev == nullptr) {
                L = p->next;
            } else {
                prev->next = p->next;
            }
            ListNode *newNode = p;
            return newNode;
        }
        prev = p;
    }
}

void ListNode::print(std::ostream& out, ListNode* L) {
  while (L != nullptr) {
    out << L->data << " ";
    L = L->next;
  }
}

int ListNode::length(ListNode* L) {
  int len = 0;
  while (L != nullptr) {
    ++len;
    L = L->next;
  }
  return len;
}

void ListNode::delete_list(ListNode* L) {
  while (L != nullptr) {
    ListNode* temp = L->next;
    delete L;
    L = temp;
  }
}






void HashTable::insert(const std::string& word) {
  size_t index = hasher.hash(word, capacity);
  buf[index] = ListNode::insert(word, buf[index]);
}

bool HashTable::find(const std::string& word) {
  size_t index = hasher.hash(word, capacity);
  ListNode* node = ListNode::find(word, buf[index]);
  return node != nullptr;
}

void HashTable::remove(const std::string& word) {
  size_t index = hasher.hash(word, capacity);
  buf[index] = ListNode::remove(word, buf[index]);
}

bool HashTable::is_empty() {
  for (size_t i = 0; i < capacity; ++i) {
    if (buf[i] != nullptr) {
      return false;
    }
  }
  return true;
}

bool HashTable::is_full() {
  return false; // ChainedHashTable is never full.
}

void HashTable::print(std::ostream& out) {
  for (size_t i = 0; i < capacity; ++i) {
    ListNode::print(out, buf[i]);
  }
}

HashTable::~HashTable() {
  for (size_t i = 0; i < capacity; ++i) {
    ListNode::delete_list(buf[i]);
  }
  delete[] buf;
}

size_t HashTable::number_of_entries() {
  size_t count = 0;
  for (size_t i = 0; i < capacity; ++i) {
    count += ListNode::length(buf[i]);
  }
  return count;
}

size_t HashTable::number_of_chains() {
  size_t count = 0;
  for (size_t i = 0; i < capacity; ++i) {
    if (buf[i] != nullptr) {
      ++count;
    }
  }
  return count;
}

void HashTable::get_chain_lengths(std::vector<int>& v) {
  v.clear();
  for (size_t i = 0; i < capacity; ++i) {
    v.push_back(ListNode::length(buf[i]));
  }
}





void error(string word, string msg) {
    cout << word << msg << endl;
}

void insert_all_words(string file_name, HashTable & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for (string word; in >> word;) {
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void find_all_words(string file_name, HashTable & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for (string word; in >> word;) {
        L.find(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(string file_name, HashTable & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    t.start();
    for (string word; in >> word;) {
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}


void measure_hashtable(string file_name, HashTable &L) {
    cout << L.get_name() << endl;
    insert_all_words(file_name, L);

    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
    if (!L.is_empty()) {
        error(L.get_name(), "is not empty");
    }
}

void measure_hashtables(string input_file) {
    Hasher * H[] = {
        new ChatGPTHasher{},
        new GoodrichHasher{},
        new MultHasher{},
        new PreissHasher{},
        new PJWHasher{},
        new STLHasher{},
        new SumHasher{},
        new Weiss1Hasher{},
        new Weiss2Hasher{},
        new WeissHasher{},
    };

    int S[] = {
        10000,
        1000,
        100,
        10,
        1,
    };
    for (auto size : S) {
        for (auto h : H) {
            HashTable ht(*h, size);
            measure_hashtable(input_file, ht);
        }
    }
}
