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
            for (int j=0; j<circuit.flipFlops.size(); j++){
                if ( circuit.FF_instances[i].type == circuit.flipFlops[j].name ){
                    circuit.FF_instances[i].width = circuit.flipFlops[j].x;
                    circuit.FF_instances[i].height = circuit.flipFlops[j].y;
                    ctree.Insert( {circuit.FF_instances[i].x, circuit.FF_instances[i].y}, \
                    {circuit.FF_instances[i].x + circuit.flipFlops[j].x, circuit.FF_instances[i].y + circuit.flipFlops[j].y}, i);
                }
                break;
            }
        }

        // // Find maximum bits of flipflop
        // for (int i=0; i<circuit.flipFlops.size(); i++){
        //     if (circuit.flipFlops[i].id > max_bit) max_bit = circuit.flipFlops[i].id;
        // }
        for (int i=0; i<circuit.flipFlops.size(); i++){
            bits.push(circuit.flipFlops[i].id);
        }

        for (int i=0; i<bits.size(); i++){
            for (int j=0; j<bits.size){

            }
        }
    }

    
    // Find all neightbors of all flipflops
    std::vector<int> findAdjacentFF(Instance flipflop, float epsilon = 2000) {/////alter
        // neighbors.clear();
        neighbors_id.clear();
        // count_neighbor = 0;
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
            if ( !neighbors_id_return.empty() ){
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
            }
            ff_list.erase(ff_list.begin()+index);

            resultFF 


            index++;
        }
    }

    std::vector<Instance> resultFF;



private:
    // Circuit circuit;
    // int count_neighbor;
    // int max_bit;
    // std::vector<Instance> neighbors;
    std::vector<int> bits;
    std::vector<int> neighbors_id;

    static bool MySearchCallback(Instance& target) {
        // count_neighbor++;
        neighbors_id.push(target.id);

        return true;
        // if (count_neighbor >= max_bit) return false;
        // else return true;

    }
};
