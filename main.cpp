#include <iostream>
#include "llist.h"

using namespace std;
using namespace md_llist;

template <class T>
class Stack{
private:
    LList<T> data;
public:
    void push(T new_item){ data.add_front(new_item); }
    T pop(){ return data.pop_front(); }
    T top() { return data.get_node(0); }
    bool is_empty(){ return data.empty(); }
    int size(){ return data.size(); }
    void clear(){ data.clear(); }
    void print(){ for(int i = 0; i < size(); ++i){ cout << data.get_node(i);} }
};

int main() {
    Stack<int> S;

    for(int i = 0; i < 5; ++i){
        S.push(i);
    }

    S.print();
    cout << endl;
    cout << S.size() << endl;
    cout << S.top() << endl;
    cout << S.pop() << endl;
    cout << S.is_empty()<< endl;
    cout << S.size() << endl;
    cout << S.top() <<endl;
    S.clear();
    cout << S.size();

    return 0;
}
