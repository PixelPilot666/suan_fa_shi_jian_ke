#include "head.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    string choice = "";
    
    while (true)
    {
        cout << "Input your choice. (or 'q' to quit)\n" << endl;
        cout << "1. BFS" << endl;
        cout << "2. IDDFS" << endl;
        cout << "3. IDA*" << endl; // 添加A*选项
        cout << endl;
        getline(cin, choice);
        if (choice == "1") bfs();
        else if (choice == "2") iddfs_main();
        else if (choice == "3") idA_star(); 
        else if (choice == "q") break;
    }

    return 0;
}