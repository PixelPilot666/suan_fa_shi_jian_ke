#include "head.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;


// 计算曼哈顿距离
int manhattan_distance(const string &state, const string &end_state) {
    int distance = 0;
    for (int i = 0; i < 9; ++i) {
        if (state[i] == ' ') continue;
        int target_pos = end_state.find(state[i]);
        distance += abs(i / 3 - target_pos / 3) + abs(i % 3 - target_pos % 3);
    }
    return distance;
}

struct Node {
    string state;
    vector<string> path;
    int g, h;

    Node(string s, vector<string> p, int g_val, int h_val)
        : state(s), path(p), g(g_val), h(h_val) {}

    // 优先队列比较函数
    bool operator<(const Node &other) const {
        return g + h > other.g + other.h; // 小顶堆
    }
};

int A_star() {
    cout << "Start state: " << START_STATE << endl;
    cout << "End state: " << END_STATE << endl;

    priority_queue<Node> open;
    unordered_set<string> closed;

    open.emplace(START_STATE, vector<string>{START_STATE}, 0, manhattan_distance(START_STATE, END_STATE));
    closed.insert(START_STATE);

    int times = 0;

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        if (current.state == END_STATE) {
            print(current.path);
            cout << "Found solution in " << times << " moves." << endl;
            cout << "Length of path is " << current.path.size() - 1 << "." << endl;
            return 0;
        }

        ++times;
        int blank_index = current.state.find(' ');
        int x = blank_index / 3, y = blank_index % 3;

        for (int i = 0; i < 4; ++i) {
            int x_new = x + dx[i], y_new = y + dy[i];
            if (x_new < 0 || x_new > 2 || y_new < 0 || y_new > 2) continue;

            string next_state = current.state;
            swap(next_state[blank_index], next_state[x_new * 3 + y_new]);

            if (closed.count(next_state)) continue;

            closed.insert(next_state);
            vector<string> next_path = current.path;
            next_path.push_back(next_state);
            int g = current.g + 1;
            int h = manhattan_distance(next_state, END_STATE);
            open.emplace(next_state, next_path, g, h);
        }
    }

    cout << "No solution found." << endl;
    return -1;
}

