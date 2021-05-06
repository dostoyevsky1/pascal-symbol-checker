//Author: Michael Drozdov
//NetID: MD5026
//Assignment: Homework 15
#ifndef llist_h
#define llist_h

namespace md_llist
{
template <class T>
class LList;
template <class T>
class LLNode;

template <class T>
class LLNode{
public:
    LLNode();
    LLNode(const T& newdata, LLNode<T>* newnext, LLNode<T>* newprev);
    friend class LList<T>;
    T get_data();
    void set_data(T newdata);

private:
    T data;
    LLNode<T>* next;
    LLNode<T>* prev;
};

template <class T>
class LList{
public:
    LList();
    LList(const LList& rhs);
    ~LList();
    LList& operator=(const LList& rhs);
    LLNode<T>* start();
    LLNode<T>* end();
    LLNode<T>* get_current_node();
    bool empty() const;
    void insert_at(const T& newdata, int idx);
    void add_front(const T& newdata);
    void add_back(const T& newdata);
    T pop_front();
    T pop_back();
    void clear();
    T remove_node(int idx);
    T remove_node(LLNode<T>*& node);
    int size();
    T get_node(int idx);
    T get_node(LLNode<T>*& node);
    void sort_list();

private:
    LLNode<T>* head;
    LLNode<T>* tail;
    LLNode<T>* current;
    int element_count;
};
}
#include "llist.cpp"

#endif