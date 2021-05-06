#include <iostream>
#include "llist.h"
#include <fstream>
#include <utility>
#include <string>

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

bool check_symbol_balance(string file_path);

int main() {
    Stack<int> S;

    string file_path = "/Users/mdrozdov/CLionProjects/pascal-symbol-checker/test.txt";
    cout << check_symbol_balance(file_path);

    return 0;
}

bool check_symbol_balance(string file_path){
    ifstream in_stream(file_path,ios::in);
    string line;
    Stack<string> S;
    int line_count = 0;
    while(getline(in_stream, line)) {
        ++line_count;
        string newstr;
        if(line == "begin"){
            S.push(line);
        } else if (line == "end" && S.is_empty()) {
            cout << "Error unmatched character in line: " << line_count << endl;
            return false;
        } else if (line == "end" && !S.is_empty()){
            newstr = S.pop();
            if (newstr != "begin"){
                cout << "Error unmatched character in line: " << line_count << endl;
                return false;
            }
        } else {
            for(char i : line){
                newstr = "";
                if(i == '(' || i == '{' || i == '['){
                    S.push(newstr+i);
                } else if ((i == ')' || i == '}' || i == ']') && S.is_empty()) {
                    cout << "Error unmatched character in line: " << line_count << endl;
                    return false;
                } else if ((i == ')' || i == '}' || i == ']') && !S.is_empty()){
                    newstr = S.pop();
                    if ((i == ')' && newstr != "(") || (i == ']' && newstr != "[") || (i == '}' && newstr != "{")){
                        cout << "Error unmatched character in line: " << line_count << endl;
                        return false;
                    }
                }
            }
        }
    }
    in_stream.close();
    in_stream.clear();

    if (!S.is_empty()){
        cout << "Error unmatched character in line: " << line_count << endl;
        return false;
    }
    return true;
}

