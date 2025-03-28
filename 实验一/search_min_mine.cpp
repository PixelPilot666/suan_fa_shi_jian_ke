#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <chrono>

class Point {
    public:
        int x, y;

        Point(int x, int y) : x(x), y(y) {}

        // 计算两点间的欧氏距离
        double distance(const Point& other) const {
            return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
        }
};

// 按照x坐标排序的比较函数
bool compare_x(const Point& a, const Point& b) {
    return a.x < b.x;
}

// 按照y坐标排序的比较函数
bool compare_y(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 穷举法找出最近点对
std::pair<Point, Point> brute_force(const std::vector<Point>& points, double& min_dist) {
    int n = points.size();
    std::pair<Point, Point> closest_pair = {Point(0, 0), Point(0, 0)};
    min_dist = std::numeric_limits<double>::max();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = points[i].distance(points[j]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_pair = {points[i], points[j]};
            }
        }
    }

    return closest_pair;
}