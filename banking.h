#include <vector>
#include "RTree.h"
#include "def.h"
#include "read.h"
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


            // TODO: Find best ff among every kind of bits
            int doc[50]; // record cost, #of bits be index
            for (int i=0; i<50; i++) doc[i]= -1;
            for (int i=0; i<10; i++) bestFF_temp[i]= -1;
            for (int i=0; i<circuit.flipFlops.size()){
                int cost = circuit.parameters[Beta]*circuit.gatePowers[circuit.flipFlops[i].name] + \
                circuit.parameters[Gemma]*circuit.flipFlops[i].x * circuit.flipFlops[i].y;
                if ( cost < doc[circuit.flipFlops[i].id] \
                || doc[circuit.flipFlops[i].id] == -1)
                {
                    bestFF_temp[circuit.flipFlops[i].id] = circuit.flipFlops[i]的id;
                    doc[circuit.flipFlops[i].id] = cost;

                }
            }

            for (int i=0; i<10; i++){
                if (bestFF_temp[i] != -1){
                    bestFF.push(bestFF_temp[i]);
                }
            }

            // TODO: Dynamic Programming of MBFF
            // Find lcm
            int temp = 0;
            temp = lcm(circuit.flipFlops[bestFF[0]].id, circuit.flipFlops[bestFF[1]].id);
            for (int i=2; i<bestFF.size(); i++){
                temp = lcm(temp, circuit.flipFlops[bestFF[i]].id);
            }

            table = new int*[bestFF.size()+1];
            for (int i=0; i<bestFF.size(); i++) table[i] = new int [temp +1];
            // Fill the table
            for (int i=0; i<bestFF.size()+1; i++){
                for (int j=0; j<temp +1; j++){
                    if ( i==0 || j==0 ) table[i][j] = 0;
                    
                }
            }


        }

    }

    
    // Find all neightbors of a flipflops
    std::vector<int> findAdjacentFF(Instance flipflop, float epsilon = 2000) {/////alter
        // neighbors.clear();
        neighbors_id.clear();
        // count_neighbor = 0;
        float query_MinBounds[2] = {flipflop.x - epsilon, flipflop.y - epsilon}
        float query_MaxBounds[2] = {flipflop.x + flipflop.width + epsilon, flipflop.y + flipflop.height + epsilon};
        ctree.Search(query_MinBounds[2], query_MaxBounds[2],  [](Instance const& target){
            return MySearchCallback(const_cast<Instance&>(target));
        });

    
        return neighbors_id;
    }

    // Find all neightbors of all flipflops
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
            neighbors_id_return.push(ff_list[index].id); 


            // TODO: Merge neighbors according to table and name each, decide location, save in some ds(an vector)???
            // TODO: Handle pins mapping

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
    double** table;
    int bestFF_temp[10];
    std::vector<int> bestFF;


    static bool MySearchCallback(Instance& target) {
        // count_neighbor++;
        neighbors_id.push(target.id);

        return true;
        // if (count_neighbor >= max_bit) return false;
        // else return true;

    }
};


long long gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  
// Function to return LCM of two numbers  
long long lcm(int a, int b) 
{ 
    return (a / gcd(a, b)) * b; 
}
