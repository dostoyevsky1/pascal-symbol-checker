//Author: Michael Drozdov
//NetID: MD5026
//Assignment: Homework 15
#include <iostream>
#include "llist.h"

using namespace std;
namespace md_llist
{

    template <class T>
    LLNode<T>::LLNode() : data(T()), next(nullptr), prev(nullptr) {}
    template <class T>
    LLNode<T>::LLNode(const T& newdata, LLNode<T>* newnext, LLNode<T>* newprev) : data(newdata), next(newnext), prev(newprev) {}

    template <class T>
    T LLNode<T>::get_data() { return data; }

    template <class T>
    void LLNode<T>::set_data(T newdata) {
        data = newdata;
    }

    template <class T>
    LList<T>::LList(){
        element_count = 0;
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    template <class T>
    LList<T>::LList(const LList <T> &rhs) {
        if (rhs.head == nullptr) { return; }

        LLNode<T>* tmp = rhs.head;

        head = new LLNode<T>;
        head->data = tmp->data;
        head->next = nullptr;
        current = head;
        tmp = tmp->next;

        while (tmp != nullptr)
        {
            current->next = new LLNode<T>;
            current = current->next;
            current->data = tmp->data;
            current->next = nullptr;
            tmp = tmp->next;
        }
        element_count = rhs.element_count;
    }

    template <class T>
    T LList<T>::remove_node(LLNode <T> *&node) {
        LLNode<T> *to_delete = node;
        T data = to_delete->data;
        if(head == tail){
            delete to_delete;
            head = nullptr;
            tail = nullptr;
            current = nullptr;
            --element_count;
        } else if (to_delete == head){
            to_delete->next->prev = nullptr;
            head = to_delete->next;
            delete to_delete;
            --element_count;
        } else if (to_delete == tail){
            to_delete->prev->next = nullptr;
            tail = to_delete->prev;
            delete to_delete;
            --element_count;
        } else {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
            delete to_delete;
            --element_count;
        }
        return data;
    }

    template <class T>
    T LList<T>::get_node(int idx) {
        int curr_idx = 0;
        current = head;
        while(curr_idx < idx){
            current = current->next;
            ++curr_idx;
        }
        return current->data;
    }

    template <class T>
    T LList<T>::get_node(LLNode<T>*& node){
        return node->data;
    }

    template <class T>
    T LList<T>::remove_node(int idx) {
        current = head;
        int curr_idx = 0;
        while(curr_idx <= idx){
            current = current->next;
            ++curr_idx;
        }
        LLNode<T> *to_delete = current;
        T return_data = to_delete->data;
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;

        delete to_delete;
        --element_count;
        current = head;
        return return_data;
    }

    template <class T>
    T LList<T>::pop_front() {
        if (!empty()){ return remove_node(head);}
        else {cout << "Empty List.";}
    }

    template <class T>
    T LList<T>::pop_back() {
        if (!empty()){ return remove_node(tail);}
        else {cout << "Empty List.";}
    }

    template <class T>
    void LList<T>::clear() {
        if(!empty()) {
            current = head;
            remove_node(current);
            while (!empty()) {
                current = current->next;
                remove_node(current);
            }
            element_count = 0;
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }
    }

    template <class T>
    LList<T>::~LList(){
        clear();
    }

    template <class T>
    int LList<T>::size() {
        return element_count;
    }

    template <class T>
    LList<T>& LList<T>::operator=(const LList<T>& rhs) {
        if (this == &rhs)
            return *this;
        clear();

        for(LLNode<T>* temp = rhs.head->next; temp != rhs.tail; temp = temp->next)
            add_front(temp->data);
        return *this;
    }

    template <class T>
    LLNode<T>* LList<T>::start() {
        return head;
    }

    template <class T>
    LLNode<T>* LList<T>::end() {
        return tail;
    }

    template <class T>
    LLNode<T> * LList<T>::get_current_node() {
        return current;
    }

    template <class T>
    bool LList<T>::empty() const {
        return element_count == 0;
    }

    template <class T>
    void LList<T>::add_front(const T &newdata) {
        if(element_count == 0) {
            LLNode<T> *temp = new LLNode<T>(newdata, nullptr, nullptr);
            head = temp;
            tail = temp;
            ++element_count;
        } else {
            LLNode<T> *temp = new LLNode<T>(newdata, head, nullptr);
            head->prev = temp;
            head = temp;
            ++element_count;
        }
    }

    template <class T>
    void LList<T>::add_back(const T &newdata){
        if(element_count == 0){
            LLNode<T>* temp = new LLNode<T>(newdata, nullptr, nullptr);
            head = temp;
            tail = temp;
            ++element_count;
        } else {
            LLNode<T>* temp = new LLNode<T>(newdata, nullptr, tail);
            tail->next = temp;
            tail = temp;
            ++element_count;
        }
    }

    template <class T>
    void LList<T>::insert_at(const T& newdata, int idx){
        if (idx == 0 || element_count == 0){
            add_front(newdata);
        } else if (idx == element_count && element_count != 0){
            add_back(newdata);
        } else {
            current = head;
            int curr_idx = 0;
            while(curr_idx < idx){
                current = current->next;
                ++curr_idx;
            }
            LLNode<T>* to_insert = new LLNode<T>(newdata, current, current->prev);
            current->prev->next = to_insert;
            current->prev = to_insert;
            ++element_count;
        }
    }

    template <class T>
    void LList<T>::sort_list() {
        current = head;
        LLNode<T>* index = nullptr;
        if(head == nullptr){
            return;
        } else {
            while(current != nullptr){
                index = current->next;
                while(index != nullptr){
                    if(get_node(current) < get_node(index)){
                        T temp = current->data;
                        current->data = index->data;
                        index->data = temp;
                    }
                    index = index->next;
                }
                current = current->next;
            }
        }
    }

}