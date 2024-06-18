#include "banking.h"


FFBanking::FFBanking(){}

void FFBanking::run()
{
    buildTree();
    std::cout<<"Finish buildTree()..." << std::endl;
    selectFF();
    std::cout<<"Finish selectFF()..." << std::endl;
    buildTable();
    std::cout<<"Finish buildTable()..." << std::endl;
    banking();
    std::cout<<"Finish banking()..." << std::endl;
}


void FFBanking::buildTree(){
    
    // Get ff instances and insert them into rtree B
    auto& c = getParam();
    
    flipflops.reserve(c.getFFSize());
    for (int id = 0; id < c.getFFSize(); id++)
    {
        FF& f = c.get_inst_FF(id);
        flipflops.emplace_back(std::make_pair(Box(  Point(f.getX(), f.getY()),\
         Point( f.getX() + f.getW(), f.getY() + f.getH())  ), id));
    }
    B.insert(flipflops.begin(), flipflops.end());
}

void FFBanking::selectFF(){

    // Select only one ff from each number of bits
    auto& c = getParam();
    bool exist;
    for (int i=0; i<c.getFFListSize(); i++){
        exist = false;
        for (int j=0; j<useList.size(); j++){
            if (c.getFF(i).getBits() == useList[j].getBits() ){
                exist = true;
                if ( calPACost(c.getFF(i)) < calPACost(useList[j]) ){
                    useList.erase(useList.begin() + j);
                    useList.push_back(c.getFF(i));
                    break;
                }
            }
        }
        if (!exist){
            useList.push_back(c.getFF(i));
        }
    }
}

void FFBanking::buildTable(){

    // Calculating the lcm of number of bits
    bitsLCM = lcm( useList[0].getBits(), useList[1].getBits() );
    for (int i=2; i<useList.size(); i++) bitsLCM = lcm(bitsLCM, useList[i].getBits());

    
    // Sort
    for (int i = useList.size()-1; i>=1; i--){
        for (int j=0; j<= (i-1); j++){
            if (useList[j].getBits() > useList[j+1].getBits()){
                std::swap(useList[j], useList[j+1]);
            }
        }
    }

    // DP
    std::vector<int> bits;
    for (int i=0; i<useList.size(); i++) bits.push_back(useList[i].getBits());
    std::vector<double> costs;
    for (int i=0; i<useList.size(); i++) costs.push_back(calPACost(useList[i]));

    // DP table
    for (int i = 0; i <= useList.size(); ++i) {
        dp[i][0] = 0;
    }
    for (int i=0; i<=useList.size(); i++){
        for (int j=0; j<=bitsLCM; j++){
            for (int k=0; k<useList.size(); k++){
                FF_count[i][j][useList.get_FF_type_id()] = 0;
            }
            
        }
    }

    // 動態規劃求解最小cost
    for (int i = 1; i <= useList.size(); ++i) {
        for (int j = 1; j <= bitsLCM; ++j) {
            // 不選擇第i種flip-flop
            dp[i][j] = dp[i-1][j];
            FF_count[i][j] = FF_count[i-1][j]

            int tempCost = dp[i][j - bits[i-1]] + costs[i-1];
            if (tempCost < dp[i][j]) {
                dp[i][j] = tempCost;
                FF_count[i][j] = FF_count[i][j - bits[i-1]];
                FF_count[i][j][useList[i-1].get_FF_type_id()] += 1;  // 記錄選擇的flip-flop索引
            }
        }
    }
}

void FFBanking::banking(){
    auto& c = getParam();
    for (int i=0; i<c.getFFSize(); i++){
        TBmerge.push_back(c.get_inst_FF(i));
    }

    std::vector<BoxWithID> box_neighbors; // id is the index of the ff in FF_inst
    std::vector<FF> neighbors;
    int totalBits;
    int index;
    int quotient;
    int nameCount = 0;
    std::unordered_map<int, int> FF_total_count; // < type id of ff, number of ff used >

    for (int i=0; i<TBmerge.size(); i++){
        Box queryBox(  Point(TBmerge[i].getX() - c.searchRange, TBmerge[i].getY() - c.searchRange), \
        Point(TBmerge[i].getX() + c.searchRange, TBmerge[i].getY() + c.searchRange)  );
        box_neighbors.clear(); 
        neighbors.clear();
        B.query(bgi::intersects(queryBox), std::back_inserter(box_neighbors));
        for (int j=0; j<box_neighbors.size(); j++){ // erase flipflops that are found to avoid re-merge
            if (int k=0; k<TBmerge.size(); k++){
                if (box_neighbors[j].second == TBmerge[k].get_FF_id()) { // if their instance id are the same, erase
                    neighbors.push_back(TBmerge[k]);
                    TBmerge.erase(TBmerge.begin() + k);
                    break;
                }
            }   
        }

        totalBits = 0; // Calculate total bits in the cluster
        for (int j=0; j<neighbors.size(); j++){
            totalBits += neighbors[j].getBits();
        }
        // Decide how to divide bits
        index = bitsLCM;
        FF_total_count.clear();
        while(totalBits != 0){
            totalBits = totalBits % index;
            quotient = totalBits / index;
            for (int j=0; j<useList.size(); j++){
                FF_total_count[useList[j].get_FF_type_id()] += FF_count[useList.size()][index][useList[j].get_FF_type_id()] *quotient;
            }
            index--;
        }
        int count_index = 0;
        int count_bit = 0;
        for (int j=0; j<useList.size(); j++){
            for (int k=0; k<FF_total_count[useList[j].get_FF_type_id()]; k++){
                double x = neighbors[count_index].getX();
                double y = neighbors[count_index].getY();
                
                FF ff(useList[j].getBits(), ("Z"+to_string(nameCount)), x , y);
                c.addFFresult();
                count_index ++;
                nameCount ++;
                int pinCount = 0;
                for (int l=0; l<useList[j].getBits(); l++){
                    mappings[neighbors[count_bit].get_Inst_name() +"/D"] = "Z"+to_string(nameCount)+"/D"+to_string(pinCount);
                    mappings[neighbors[count_bit].get_Inst_name() +"/Q"] = "Z"+to_string(nameCount)+"/D"+to_string(pinCount);
                    count_bit++;
                    pinCount++;
                }
            }
        }
        

    }
}



double FFBanking::calPACost(FF& ff){
    auto& c = getParam();
    double cost;
    double area = ff.getW() * ff.getH();
    cost = c.getParameter("Beta")* ff.get_Power() + c.getParameter("Gamma")* area;
    return cost;
}

