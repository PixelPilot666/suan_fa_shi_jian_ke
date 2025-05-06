#pragma once

#include <vector>
#include <string>
#include <stack>

const std::string START_STATE = "7425 6831";
const std::string END_STATE = " 24763815";

const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void format_print(const std::string& s);
void print(std::vector<std::string>& t);
void print_stack(std::stack<std::string>& t);

int bfs();
int iddfs_main();
int idA_star();