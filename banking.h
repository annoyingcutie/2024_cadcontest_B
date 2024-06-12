#include <vector>
#include "RTree.h"
#include "def.h"
#include <string>
typedef RTree<int, double, 2> rtree;


class FFBanking {
public:
    //Constructor
    FFBanking(Circuit circuit) {
        // circuit = x;
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

    
    // Find all neightbors of all flipflops
    std::vector<int> findAdjacentFF(Instance flipflop, float epsilon = 2000) {
        // neighbors.clear();
        neighbors_id.clear();
        count_neighbor = 0;
        float query_MinBounds[2] = {flipflop.x - epsilon, flipflop.y - epsilon}
        float query_MaxBounds[2] = {flipflop.x + flipflop.width + epsilon, flipflop.y + flipflop.height + epsilon};
        ctree.Search(query_MinBounds[2], query_MaxBounds[2],  [](Instance const& target){
            return MySearchCallback(const_cast<Instance&>(target));
        });

        
        for (int i=0; i<neighbors_id.size(), i++){
            neighbors_id.push(neighbors[i].id);
        }
        return neighbors_id;
    }

    void findAllAdjacentFF(std::vector<Instance> ff_list){
        int index = 0;
        while(!ff_list.empty()){
            std::vector<int> neighbors_id_return;
            neighbors_id_return = findAdjacentFF(ff_list[index]);
            //
            for (int i=0; i<neighbors_id_return.size(); i++){
                std::vector<Instance>::iterator itor = ff_list.begin();
                while (itor != ff_list.end()){
                    if (*itor.id == neighbors_id_return[i]){
                        itor = ff_list.erase(itor);
                        break;
                    } 
                    else itor++;
                }
            }
            ff_list.erase(ff_list.begin()+index);



            index++;
        }
    }

    std::vector<Instance> resultFF;



private:
    // Circuit circuit;
    int count_neighbor;
    int max_bit;
    // std::vector<Instance> neighbors;
    std::vector<int> neighbors_id;

    static bool MySearchCallback(Instance& target) {
        count_neighbor++;
        neighbors_id.push(target.id);
        if (count_neighbor >= max_bit) return false;
        else return true;
    }
};
