#include "head.h"

#include <stack>
#include <iostream>
#include <unordered_set>

using namespace std;  

stack<string> open; 
unordered_set<string> closed;
int times = 0;

bool dfs(int depth, int max_depth, const string &state, const string &end_state) {
    if (depth > max_depth) return false;
    if (closed.count(state)) return false;
    closed.insert(state);
    open.push(state); 

    if (state == end_state) {
        cout << "Depth and max depth " << depth << " " << max_depth << '\n';
        while(!open.empty()) {
            string t = open.top();
            open.pop();
            for (int j = 0; j < 9; ++ j) {
                cout << t[j] << " \n"[j % 3 == 2];
            }
            cout << endl;
        }
        return true;
    }

    ++times;
    // 寻找空格坐标
    int blank_index  = state.find(' ');
    int x = blank_index / 3, y = blank_index % 3;

    for (int i = 0; i < 4; ++i) {
        int x_new = x + dx[i], y_new = y + dy[i];
        if (x_new < 0 || y_new < 0 || x_new > 2 || y_new > 2) continue;
        string tmp = state;
        swap(tmp[blank_index], tmp[x_new * 3 + y_new]);
        if (dfs(depth + 1, max_depth, tmp, end_state)) return true;
    }

    open.pop();
    return false;
}

int dfs_main()
{
    cout << "Start state: " << START_STATE << endl;
    cout << "End state: " << END_STATE << endl;
    int max_depth = 4;
    while (!dfs(0, max_depth, START_STATE, END_STATE)) {
        ++max_depth;
        closed.clear();  // 清空 
    }
    cout << "Total times: " << times << '\n';
    
    return 0;
}