#include "head.h"

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <chrono>

using namespace std;

int target_pos[256]; 

void init_target_positions() {
    for (int i = 0; i < 9; ++i) {
        target_pos[END_STATE[i]] = i;
    }
}

int manhattan_distance(const string & state) {
    int distance = 0;
    for (int i = 0; i < 9; ++i) {
        if (state[i] != ' ') {
            int target_index = target_pos[state[i]];
            int x1 = i / 3, y1 = i % 3;
            int x2 = target_index / 3, y2 = target_index % 3;
            distance += abs(x1 - x2) + abs(y1 - y2);
        }
    }
    return distance;
}

struct Node {
    string state;
    int g;
    int h;
    int blank_index;

    Node(string s, int g_val, int h_val) : state(s), g(g_val), h(h_val) {
        blank_index = s.find(' ');
    };
};

int dfs(Node node, int dm, int& times, stack<string>& open, unordered_set<string>& closed) {
    int f = node.g + node.h;

    if (f > dm) return f;
    
    if (node.state == END_STATE) {
        open.push(node.state);
        return -1;
    }

    closed.insert(node.state);
    times++;

    int x = node.blank_index / 3, y = node.blank_index % 3;
    int min_dm = INT_MAX;

    for (int i = 0; i < 4; ++i) {
        int new_x = x + dx[i], new_y = y + dy[i];
        
        if (new_x < 0 || new_x > 2 || new_y < 0 || new_y > 2) continue;
        
        string new_state = node.state;
        swap(new_state[node.blank_index], new_state[new_x * 3 + new_y]);
        
        if (closed.count(new_state)) continue;

        Node child(new_state, node.g + 1, manhattan_distance(new_state));
        int temp_dm = dfs(child, dm, times, open, closed);

        if (temp_dm == -1) {
            open.push(node.state);
            return -1;
        }

        min_dm = min(min_dm, temp_dm);
    }

    closed.erase(node.state);
    return min_dm;
}

int idA_star() {
    auto start_time = chrono::high_resolution_clock::now();
    
    cout << "初始状态: " <<  endl;
    format_print(START_STATE);
    cout << "目标状态: " << endl;
    format_print(END_STATE);
    cout << "_______________________________" << endl;
    init_target_positions();

    int times = 0;
    stack<string> open;
    unordered_set<string> closed;

    Node start(START_STATE, 0, manhattan_distance(START_STATE));
    
    int dm = 4;
    
    while(dm < 100) {
        
        closed.clear();
        
        int temp_dm = dfs(start, dm, times, open, closed);
        
        if (temp_dm == -1) {
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
            
            cout << "运行时间: " << duration << " 毫秒" << endl;
            cout << "扩展节点总数: " << times << endl;
            cout << "解路径长度: " << open.size() - 1 << endl;
            cout << "最大深度: " << dm << endl;
            cout << "\n解路径:" << endl;
            print_stack(open);
            return 0;
        }
        
        if (temp_dm > dm) {
            dm = temp_dm;
        } else {
            dm++;
        }
    }
    
    cout << "在合理深度范围内未找到解" << endl;
    return -1;
}