#include "head.h"

#include <iostream>
using namespace std;

void format_print(const string& s) {
    for (int i = 0; i < 9; i++) {
        cout << s[i] << " ";
        if ((i+1) % 3 == 0) cout << endl;
    }
    cout << endl;
}

void print(vector<string>& t) {
    int len = t.size();
    for (int i = 0; i < len; i++) {
        format_print(t[i]);
    }
}

void print_stack(std::stack<std::string>& t) {
    int len = t.size();
    for (int i = 0; i < len; i++) {
        format_print(t.top());
        t.pop();
    }
}
