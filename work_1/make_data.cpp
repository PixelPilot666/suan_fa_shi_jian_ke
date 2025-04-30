#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include <set>
#include <utility>

int main(int argc, char* argv[]) {
    int n;
    std::string filename;
    
    if (argc < 2) {
        std::cout << "Please input the number of points: ";
        std::cin >> n;
        
        std::cout << "Please input the filename(e.g. points.txt): ";
        std::cin >> filename;
    } else {
        n = std::stoi(argv[1]);
        
        if (argc >= 3) {
            filename = argv[2];
        } else {
            filename = "points.txt";
        }
    }
    
    if (filename.find('.') == std::string::npos) {
        filename += ".txt";
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    int min_coord = -10000;
    int max_coord = 10000;
    std::uniform_int_distribution<> dis(min_coord, max_coord);
    
    std::ofstream outfile(filename);
    
    if (!outfile.is_open()) {
        std::cerr << "Cannot open file " << filename << " for writing!" << std::endl;
        return 1;
    }
    
    outfile << n << std::endl;
    
    // 使用集合存储已生成的点，确保唯一性
    std::set<std::pair<int, int>> unique_points;
    
    while (unique_points.size() < n) {
        int x = dis(gen);
        int y = dis(gen);
        unique_points.insert(std::make_pair(x, y));
    }
    
    for (const auto& point : unique_points) {
        outfile << point.first << " " << point.second << std::endl;
    }
    
    outfile.close();
    std::cout << "Successfully generated " << n << " unique points and saved to file " << filename << std::endl;
    
    return 0;
}