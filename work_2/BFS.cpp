#include "head.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int bfs() {

    cout << "初始状态: " <<  endl;
    format_print(START_STATE);
    cout << "目标状态: " << endl;
    format_print(END_STATE);

    cout << "_______________________________" << endl;

    queue<vector<string>> open;
    unordered_set<string> closed;
    
    open.push({START_STATE});
    closed.insert(START_STATE);

    int times = 0;

    while(!open.empty()){
        vector<string> current = open.front();
        open.pop();
        string state = current.back();
        if (state == END_STATE) {
            print(current);
            cout << "Found solution in " << times << " moves." << endl;
            cout << "Lenth of path is " << current.size() - 1 <<"."<< endl;
            break;
        }
        times++;
        int blank_index = state.find(' ');
        int x = blank_index / 3, y = blank_index % 3;
        for (int i = 0; i < 4; i++) {
            int x_new = x + dx[i], y_new = y + dy[i];
            if (x_new < 0 || x_new > 2 || y_new < 0 || y_new > 2) continue;

            string tmp = state;
            swap(tmp[blank_index], tmp[x_new * 3 + y_new]);
            
            if (closed.count(tmp)) continue;
            closed.insert(tmp);
            current.emplace_back(tmp);
            open.emplace(current);
            current.pop_back();
        }
    }
    return 0;
}