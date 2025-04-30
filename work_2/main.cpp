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
        cout << "2. DFS" << endl;
        cout << "3. A*" << endl; // 添加A*选项
        cout << endl;
        getline(cin, choice);
        if (choice == "BFS") bfs();
        else if (choice == "DFS") dfs_main();
        else if (choice == "A*") A_star(); 
        else if (choice == "q") break;
    }

    return 0;
}