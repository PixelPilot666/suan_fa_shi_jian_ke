#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>

// 定义节点结构体
struct Node {
    char color;
    int value;
};

// 用于方便地打印路径向量
template<typename T>
void print_path(const std::vector<T>& path_vec, const std::string& delimiter) {
    for (size_t i = 0; i < path_vec.size(); ++i) {
        std::cout << path_vec[i] << (i == path_vec.size() - 1 ? "" : delimiter);
    }
    std::cout << std::endl;
}

int main() {
    // 优化C++的输入输出流，在处理大量输入时更高效
    std::cout << "Total number of rows in the diamond (n): ";
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::cin.ignore(); // 消耗掉 cin >> n 后留下的换行符

    // 1. 读取和解析输入
    std::cout << "Enter the diamond nodes (color and value) for each row, separated by spaces:" << std::endl;
    std::vector<std::vector<Node>> diamond_nodes(n);
    int mid_row = n / 2;
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string node_str;
        
        while (ss >> node_str) {
            Node node;
            node.color = node_str[0];
            node.value = std::stoi(node_str.substr(1));
            diamond_nodes[i].push_back(node);
        }
    }

    // 2. 初始化 DP 表和路径回溯表
    long long min_val = std::numeric_limits<long long>::min();
    std::vector<std::vector<long long>> dp(n);
    std::vector<std::vector<int>> path(n);

    for (int i = 0; i < n; ++i) {
        dp[i].resize(diamond_nodes[i].size(), min_val);
        path[i].resize(diamond_nodes[i].size(), -1);
    }

    // 设置起点
    dp[0][0] = diamond_nodes[0][0].value;

    // 3. 动态规划填充表格
    // 前半部分菱形（扩张）
    for (int i = 1; i <= mid_row; ++i) {
        for (int j = 0; j < diamond_nodes[i].size(); ++j) {
            const auto& current_node = diamond_nodes[i][j];
            long long max_prev_sum = min_val;
            int best_parent_j = -1;

            // 检查左上父节点 (i-1, j-1)
            if (j > 0 && diamond_nodes[i-1][j-1].color != current_node.color && dp[i-1][j-1] != min_val) {
                if (dp[i-1][j-1] > max_prev_sum) {
                    max_prev_sum = dp[i-1][j-1];
                    best_parent_j = j - 1;
                }
            }

            // 检查右上父节点 (i-1, j)
            if (j < diamond_nodes[i-1].size() && diamond_nodes[i-1][j].color != current_node.color && dp[i-1][j] != min_val) {
                 if (dp[i-1][j] > max_prev_sum) {
                    max_prev_sum = dp[i-1][j];
                    best_parent_j = j;
                }
            }
            
            if (best_parent_j != -1) {
                dp[i][j] = max_prev_sum + current_node.value;
                path[i][j] = best_parent_j;
            }
        }
    }

    // 后半部分菱形（收缩）
    for (int i = mid_row + 1; i < n; ++i) {
        for (int j = 0; j < diamond_nodes[i].size(); ++j) {
            const auto& current_node = diamond_nodes[i][j];
            long long max_prev_sum = min_val;
            int best_parent_j = -1;

            // 检查左上父节点 (i-1, j)
            if (diamond_nodes[i-1][j].color != current_node.color && dp[i-1][j] != min_val) {
                if (dp[i-1][j] > max_prev_sum) {
                    max_prev_sum = dp[i-1][j];
                    best_parent_j = j;
                }
            }

            // 检查右上父节点 (i-1, j+1)
            if (j + 1 < diamond_nodes[i-1].size() && diamond_nodes[i-1][j+1].color != current_node.color && dp[i-1][j+1] != min_val) {
                if (dp[i-1][j+1] > max_prev_sum) {
                    max_prev_sum = dp[i-1][j+1];
                    best_parent_j = j + 1;
                }
            }

            if (best_parent_j != -1) {
                dp[i][j] = max_prev_sum + current_node.value;
                path[i][j] = best_parent_j;
            }
        }
    }
    
    // 4. 回溯以构建路径
    long long max_path_sum = dp[n-1][0];
    std::vector<char> path_colors;
    std::vector<int> path_values;

    int current_j = 0;
    for (int i = n - 1; i >= 0; --i) {
        const auto& node = diamond_nodes[i][current_j];
        path_colors.push_back(node.color);
        path_values.push_back(node.value);

        if (i > 0) {
            current_j = path[i][current_j];
        }
    }

    std::reverse(path_colors.begin(), path_colors.end());
    std::reverse(path_values.begin(), path_values.end());

    // 5. 打印输出
    std::cout << "Max path sum: " << max_path_sum << std::endl;
    std::cout << "Path colors sequence: ";
    print_path(path_colors, " -> ");
    std::cout << "Path values sequence: ";
    print_path(path_values, " -> ");

    return 0;
}