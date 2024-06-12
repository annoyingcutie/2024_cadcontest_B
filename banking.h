#include <iostream>
#include <vector>
#include "RTree.h"
#include "def.h"
#include <string>
typedef RTree<int, double, 2> MyTree;
// class Rectangle {
// public:
//     int id;
//     float x, y, width, height;

//     Rectangle(int id, float x, float y, float width, float height)
//         : id(id), x(x), y(y), width(width), height(height) {}

//     // 返回矩形的邊界框
//     float* getBounds() {
//         static float bounds[4];
//         bounds[0] = x;
//         bounds[1] = y;
//         bounds[2] = x + width;
//         bounds[3] = y + height;
//         return bounds;
//     }
// };



class FFBanking {
public:
    //Constructor
    FFBanking(Circuit circuit) {
        
        rtree ctree;
        for (int i=0; i<circuit.FF_instances.size(); i++){
            // insert all flipflops to ctree
            circuit.FF_instances[i].id = i;
            for (int j=0; j<circuit.flipflops.size(); j++){
                if ( circuit.FF_instances[i].type == circuit.flipflops[j].name ){
                    circuit.FF_instances[i].width = circuit.flipflops[j].x;
                    circuit.FF_instances[i].height = circuit.flipflops[j].y;
                    ctree.Insert( {circuit.FF_instances[i].x, circuit.FF_instances[i].y}, \
                    {circuit.FF_instances[i].x + circuit.flipflops[j].x, circuit.FF_instances[i].y + circuit.flipflops[j].y}, i);
                }
                break;
            }
        }

        // Find maximum bits of flipflop
        for (int i=0; i<circuit.flipflops.size(); i++){
            if (circuit.flipflops[i].id > max_bit) max_bit = circuit.flipflops[i].id;
        }

    }


    // void insertRectangle(int id, float x, float y, float width, float height) {
    //     Rectangle rect(id, x, y, width, height);
    //     rectangles.push_back(rect);
    //     rtree.Insert(rect.getBounds(), id);
    // }

    
    // Find all neightbors of all flipflops
    std::vector<int> findAdjacentRectangles(Instance flipflop, float epsilon = 2000) {
        neighbors.clear();
        count = 0;
        float query_MinBounds[2] = {flipflop.x - epsilon, flipflop.y - epsilon}
        float query_MaxBounds[2] = {flipflop.x + flipflop.width + epsilon, flipflop.y + flipflop.height + epsilon};
        rtree.Search(query_MinBounds[2], query_MaxBounds[2],  [](Instance const& target){
            return MySearchCallback(const_cast<Instance&>(target));
        });



        // ChatGPT ?????????????????
        // std::vector<int> adjacent_rects;
        // for (int rect_id : potential_neighbors) {
        //     if (isAdjacent(x, y, width, height, rectangles[rect_id], epsilon)) {
        //         adjacent_rects.push_back(rect_id);
        //     }
        // }
        // return adjacent_rects;
    }

private:

    // static bool searchCallback(int id, void* arg) {
    //     std::vector<int>* results = static_cast<std::vector<int>*>(arg);
    //     results->push_back(id);
    //     return true; // keep going
    // }
    int count_neighbor;
    int max_bit;
    std::vector<Instance> neighbors;

    static bool MySearchCallback(Instance& target) {
        count_neighbor++;
        neighbors.push(target);
        if (count_neighbor >= max_bit) return false;
    }

    // bool isAdjacent(float x, float y, float width, float height, const Rectangle& rect, float epsilon) {
    //     return ((std::abs(rect.x - (x + width)) <= epsilon || std::abs(x - (rect.x + rect.width)) <= epsilon) &&
    //             (rect.y < y + height && rect.y + rect.height > y)) ||
    //            ((std::abs(rect.y - (y + height)) <= epsilon || std::abs(y - (rect.y + rect.height)) <= epsilon) &&
    //             (rect.x < x + width && rect.x + rect.width > x));
    // }

    // std::vector<Rectangle> rectangles;
    // RTree<int, float, 4> rtree;
};

// int main() {
//     FFBanking rtree;

//     // 插入矩形到 R-tree 中
//     rtree.insertRectangle(0, 0.0, 0.0, 1.0, 1.0);
//     rtree.insertRectangle(1, 2.0, 0.0, 1.0, 1.0);
//     rtree.insertRectangle(2, 0.0, 2.0, 1.0, 1.0);
//     rtree.insertRectangle(3, 2.0, 2.0, 1.0, 1.0);

//     // 查詢範例：查找與矩形 (1.0, 1.0, 1.0, 1.0) 相鄰的所有矩形
//     std::vector<int> adjacent_rects = rtree.findAdjacentRectangles(1.0, 1.0, 1.0, 1.0);
//     std::cout << "相鄰的矩形: ";
//     for (int rect_id : adjacent_rects) {
//         std::cout << rect_id << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
