#include "head.h"

#include <stack>
#include <iostream>
#include <unordered_set>

using namespace std;  

bool dfs(int depth, int max_depth, int& times, stack<string>& path, unordered_set<string>& closed, const string &state, const string &end_state) {
    if (depth > max_depth) return false;
    if (closed.count(state)) return false;

    closed.insert(state);
    ++times;

    if (state == end_state) {
        path.push(state);
        return true;
    }

    // 寻找空格坐标
    int blank_index  = state.find(' ');
    int x = blank_index / 3, y = blank_index % 3;

    for (int i = 0; i < 4; ++i) {
        int x_new = x + dx[i], y_new = y + dy[i];
        if (x_new < 0 || y_new < 0 || x_new > 2 || y_new > 2) continue;
        string tmp = state;
        swap(tmp[blank_index], tmp[x_new * 3 + y_new]);
        if (dfs(depth + 1, max_depth, times, path, closed, tmp, end_state)) {
            path.push(state);
            return true;
        } 
    }
    closed.erase(state);
    return false;
}

int iddfs_main()
{
    cout << "Start status: " <<  endl;
    format_print(START_STATE);
    cout << "Target status: " << endl;
    format_print(END_STATE);

    cout << "_______________________________" << endl;
    auto start_time = chrono::high_resolution_clock::now();
    int max_depth = 4;
    stack<string> path; 
    unordered_set<string> closed;
    int times = 0;
    while (!dfs(0, max_depth, times, path, closed, START_STATE, END_STATE)) {
        ++max_depth;
        closed.clear();
        while(!path.empty()) path.pop();
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Time used: " << duration.count() << " ms" << endl;
    cout << "Total number of extended nodes: " << times << endl;
    cout << "Lenth of path is " << path.size() - 1 << "." << endl;
    cout << "Maximum depth reached: " << max_depth << endl;
    cout << "Path: " << endl;

    print_stack(path);

    return 0;
}