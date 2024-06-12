#include <iostream>
#include <vector>
#include "RTree.h"


class Rectangle {
public:
    int id;
    float x, y, width, height;

    Rectangle(int id, float x, float y, float width, float height)
        : id(id), x(x), y(y), width(width), height(height) {}

    // 返回矩形的邊界框
    float* getMinBounds() {
        static float MinBounds[2];
        MinBounds[0] = x;
        MinBounds[1] = y;
        return MinBounds;
    }

    float* getMaxBounds() {
        static float MaxBounds[2];
        MaxBounds[0] = x + width;
        MaxBounds[1] = y + height;
        return MaxBounds;
    }
};

class RTreeWrapper {
public:
    RTreeWrapper() {}

    void insertRectangle(int id, float x, float y, float width, float height) {
        Rectangle rect(id, x, y, width, height);
        rectangles.push_back(rect);
        rtree.Insert(rect.getMinBounds(), rect.getMaxBounds(), id);
    }

    std::vector<int> findAdjacentRectangles(float x, float y, float width, float height, float epsilon = 0.1) {
        float query_bounds[4] = {x - epsilon, y - epsilon, x + width + epsilon, y + height + epsilon};
        std::vector<int> potential_neighbors;
        rtree.Search(query_bounds, searchCallback, &potential_neighbors);

        std::vector<int> adjacent_rects;
        for (int rect_id : potential_neighbors) {
            if (isAdjacent(x, y, width, height, rectangles[rect_id], epsilon)) {
                adjacent_rects.push_back(rect_id);
            }
        }
        return adjacent_rects;
    }

private:
    static bool searchCallback(int id, void* arg) {
        std::vector<int>* results = static_cast<std::vector<int>*>(arg);
        results->push_back(id);
        return true; // keep going
    }

    bool isAdjacent(float x, float y, float width, float height, const Rectangle& rect, float epsilon) {
        return ((std::abs(rect.x - (x + width)) <= epsilon || std::abs(x - (rect.x + rect.width)) <= epsilon) &&
                (rect.y < y + height && rect.y + rect.height > y)) ||
               ((std::abs(rect.y - (y + height)) <= epsilon || std::abs(y - (rect.y + rect.height)) <= epsilon) &&
                (rect.x < x + width && rect.x + rect.width > x));
    }

    std::vector<Rectangle> rectangles;
    RTree<int, float, 2> rtree;
};

int main() {
    RTreeWrapper rtree;

    // 插入矩形到 R-tree 中
    rtree.insertRectangle(0, 0.0, 0.0, 1.0, 1.0);
    rtree.insertRectangle(1, 2.0, 0.0, 1.0, 1.0);
    rtree.insertRectangle(2, 0.0, 2.0, 1.0, 1.0);
    rtree.insertRectangle(3, 2.0, 2.0, 1.0, 1.0);

    // 查詢範例：查找與矩形 (1.0, 1.0, 1.0, 1.0) 相鄰的所有矩形
    std::vector<int> adjacent_rects = rtree.findAdjacentRectangles(1.0, 1.0, 1.0, 1.0);
    std::cout << "相鄰的矩形: ";
    for (int rect_id : adjacent_rects) {
        std::cout << rect_id << " ";
    }
    std::cout << std::endl;

    return 0;
}
