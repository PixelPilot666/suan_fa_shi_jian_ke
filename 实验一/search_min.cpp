#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <chrono>

struct Point {
    int x, y;
    
    // 计算两点间的欧氏距离
    double distanceTo(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

// 按照x坐标排序的比较函数
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// 按照y坐标排序的比较函数
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 穷举法找出最近点对
std::pair<Point, Point> bruteForce(const std::vector<Point>& points, double& minDist) {
    int n = points.size();
    std::pair<Point, Point> closestPair;
    minDist = std::numeric_limits<double>::max();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = points[i].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
                closestPair = {points[i], points[j]};
            }
        }
    }
    
    return closestPair;
}

// 找出跨越中线的最近点对（鸽笼原理）
std::pair<Point, Point> stripClosest(const std::vector<Point>& strip, double& minDist) {
    std::pair<Point, Point> closestPair;
    int size = strip.size();
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; j++) {
            double dist = strip[i].distanceTo(strip[j]);
            if (dist < minDist) {
                minDist = dist;
                closestPair = {strip[i], strip[j]};
            }
        }
    }
    
    return closestPair;
}

// 分治法找出最近点对
std::pair<Point, Point> closestPairDC(std::vector<Point>& pointsX, std::vector<Point>& pointsY, 
                                    double& minDist, int bruteForceThreshold) {
    int n = pointsX.size();
    
    // 如果点数小于等于阈值，使用穷举法
    if (n <= bruteForceThreshold) {
        return bruteForce(pointsX, minDist);
    }
    
    // 分割点集
    int mid = n / 2;
    Point midPoint = pointsX[mid];
    
    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
    
    std::vector<Point> leftY, rightY;
    for (const Point& p : pointsY) {
        if (p.x <= midPoint.x)
            leftY.push_back(p);
        else
            rightY.push_back(p);
    }
    
    // 递归解决左右子问题
    double leftMinDist, rightMinDist;
    std::pair<Point, Point> leftPair = closestPairDC(leftX, leftY, leftMinDist, bruteForceThreshold);
    std::pair<Point, Point> rightPair = closestPairDC(rightX, rightY, rightMinDist, bruteForceThreshold);
    
    // 选择左右子问题中距离更小的那一对
    std::pair<Point, Point> closestPair;
    if (leftMinDist <= rightMinDist) {
        minDist = leftMinDist;
        closestPair = leftPair;
    } else {
        minDist = rightMinDist;
        closestPair = rightPair;
    }
    
    // 处理跨越中线的情况
    std::vector<Point> strip;
    for (const Point& p : pointsY) {
        if (std::abs(p.x - midPoint.x) < minDist) {
            strip.push_back(p);
        }
    }
    
    // 在带状区域内寻找可能的更近点对
    std::pair<Point, Point> stripPair = stripClosest(strip, minDist);
    
    // 如果在带状区域找到了更近的点对，则更新结果
    if (minDist < leftMinDist && minDist < rightMinDist) {
        closestPair = stripPair;
    }
    
    return closestPair;
}

// 主函数用于调用分治算法
std::pair<Point, Point> findClosestPair(std::vector<Point>& points, int bruteForceThreshold) {
    // 按x和y坐标分别排序
    std::vector<Point> pointsX = points;
    std::vector<Point> pointsY = points;
    
    std::sort(pointsX.begin(), pointsX.end(), compareX);
    std::sort(pointsY.begin(), pointsY.end(), compareY);
    
    double minDist;
    return closestPairDC(pointsX, pointsY, minDist, bruteForceThreshold);
}

int main(int argc, char* argv[]) {
    std::string filename;
    int bruteForceThreshold;
    
    // 处理命令行参数
    if (argc < 2) {
        std::cout << "Please input the filename (e.g. points.txt): ";
        std::cin >> filename;
        
        std::cout << "Please input the brute force threshold: ";
        std::cin >> bruteForceThreshold;
    } else {
        filename = argv[1];
        
        if (argc >= 3) {
            bruteForceThreshold = std::stoi(argv[2]);
        } else {
            std::cout << "Please input the brute force threshold: ";
            std::cin >> bruteForceThreshold;
        }
    }
    
    // 读取点的坐标
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Cannot open file " << filename << " for reading!" << std::endl;
        return 1;
    }
    
    int n;
    infile >> n;
    
    std::vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        infile >> points[i].x >> points[i].y;
    }
    
    infile.close();
    
    std::cout << "Total points: " << n << std::endl;
    std::cout << "Brute force threshold: " << bruteForceThreshold << std::endl;
    
    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();
    
    // 寻找最近点对
    std::pair<Point, Point> closestPair = findClosestPair(points, bruteForceThreshold);
    
    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    
    // 计算最小距离
    double minDistance = closestPair.first.distanceTo(closestPair.second);
    
    // 输出结果
    std::cout << "Closest pair: (" << closestPair.first.x << ", " << closestPair.first.y 
              << ") and (" << closestPair.second.x << ", " << closestPair.second.y << ")" << std::endl;
    std::cout << "Minimum distance: " << minDistance << std::endl;
    std::cout << "Time used: " << elapsed.count() << " ms" << std::endl;
    
    return 0;
}