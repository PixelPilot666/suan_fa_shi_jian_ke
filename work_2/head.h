#pragma once

#include<vector>
#include<string>

const std::string START_STATE = "7425 6831";
const std::string END_STATE = " 24763815";

const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void print(std::vector<std::string>& t);
int bfs();
int dfs_main();
int A_star();