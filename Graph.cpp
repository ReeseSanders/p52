#include "Graph.h"
#include "Predicate.h"

Graph::Graph(std::vector<Rule> rules){
    //make edges
    for (unsigned int i = 0; i < rules.size(); i++){
        std::vector<std::string> toMatch = rules.at(i).GetVecFollowPred();
        std::set<int> edger;
        for (unsigned int j = 0; j < toMatch.size(); j++) {
            for (unsigned int k = 0; k < rules.size(); k++)
                if (toMatch.at(j) == rules.at(k).GetName()){
                    edger.insert(k);
                }
        }
        edges.insert(std::pair<int, std::set<int>>(i, edger));
    }
    //make visited map
    for (auto i : edges){
        ifVisit.push_back(false);
        ifVisita.push_back(false);
    }

    //make inverted edges
    CreateStrong();
    invertEdges();
    PostOrderHelper(0);
    InvertPostOrder();

    PrintDependGraph();
    /*for (auto i : edges){
        std::cout << "R" << i.first << " -> ";
        for (auto j : i.second){
            std::cout << "R" << j << ", ";
        }
        std::cout << std::endl;
    }*/
}

void Graph::invertEdges(){
    ResetIfVisit();
    for (auto i :edges){
        std::set<int> empty;
        iEdges.insert(std::pair<int, std::set<int>>(i.first, empty));
    }
    for (auto i : edges){ //The Rule (outer)
        //std::cout << "In R" << i.first << std::endl;
        for (auto j : i.second) { //The Consumer
            //std::cout << "Consumer R:" << j << " matches ";
            for (auto k : edges) { //The Rule
                if (j == k.first) {
                    //std::cout << "R:" << k.first << ", ";
                    iEdges.at(k.first).insert(i.first);
                }
            }
            //std::cout << std::endl;
        }
    }
    /*for (auto i : iEdges){ //print invertedEdges
        std::cout << "R" << i.first << " -> ";
        for (auto j : i.second){
            std::cout << "R" << j << ", ";
        }
        std::cout << std::endl;
    }*/
}

void Graph::PostOrderHelper(int index){
    ResetIfVisit();
    ifVisita =ifVisit;

    for(auto i : ifVisit){
        if (!i) {
            //std::cout << "-- Running PostOrder() on " << index << "--" << std::endl;
            PostOrder(index);
        }
        index++;
    }
    //std::cout << "Post Order: " << std::endl;
    /*for (auto i : postOrder){
        //std::cout << "R" << i << "->";
    }
    //std::cout << std::endl;*/
}

int Graph::PostOrder(int index){
    //std::cout << "In R" << index << std::endl;
    ifVisit.at(index) = true;
    bool allDone = true;
    for (unsigned int i = 0; i < ifVisit.size(); i++) {
        if (!i){
            allDone = false;
        }
    }
    if (allDone) {
        postOrder.push_back(index);
        //std::cout << "All nodes have been visited" << std::endl;
        return 0;
    }
    for (auto i : iEdges.at(index)) {
        //std::cout << i << std::endl;
        if (!ifVisit.at(i)) {
            //std::cout << i << std::endl;
            //std::cout << "Calling PostOrder() on R" << i << std::endl;
            PostOrder(i);

        }
    }
    postOrder.push_back(index);
    return 0;
}

void Graph::PrintDependGraph(){
    std::cout << "Dependency Graph" << std::endl;
    for (auto i : edges){
        std::cout << "R" << i.first << ":";
        for (auto j = i.second.begin(); j != i.second.end(); j++){
            std::cout << "R" << *j;
            if (std::next(j) != i.second.end()){
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::CreateStrong(){
    //std::cout << "In CreateStrong()" << std::endl;
    ResetIfVisit();
    /*for (auto i : ifVisit){
        std::cout << i.first;
        if (i.second) {
            std::cout << " is true" << std::endl;
        } else {
            std::cout << " is false" << std::endl;
        }
    }*/

    for (auto i : edges){
        //std::cout << "In forloop at edge:" << i.first << std::endl;
        //bool asd = ifVisit.at(i.first);
        if (!ifVisit.at(i.first)){
            //std::cout << "Visited Nodes" << std::endl;
            for (auto j : ifVisit){
                if (j){
                    //std::cout << "R" << j.first << ",";
                }
            }
            //std::cout << std::endl;
            ifVisita = ifVisit;
            std::set<int> comp;
            FindSCC(comp, i.first, i.first);
            comp.insert(i.first);
            SCC.insert(comp);
            for (auto j : comp){
                ifVisit.at(j) = true;
            }
        }
    }

    /*for(auto i : SCC){
        int iter = 1;
        std::cout << "SCC" << iter << ":";
        for (auto j : i){
            std::cout << "R" << j << ",";
        }

        std::cout << std::endl;
    }*/

}

bool Graph::FindSCC(std::set<int>& comp, int origin, int current){
    //std::cout << "Origin = " << origin << " and Current = " << current << std::endl;
    if (edges.at(current).empty()){return false;} //No connections
    if (current != origin && ifVisita.at(current)){return false;} //already been visited and not origin
    if (current == origin && ifVisita.at(current)) {return true;} //returned back to origin

    ifVisita.at(current) = true;
    if (ifVisita.at(current)){
        //std::cout << current << "has been visited" << std::endl;
    } else {
        //std::cout << current << "has not been visited" << std::endl;
    }
    for(auto i : edges.at(current)){
        if(FindSCC(comp, origin, i)){
            //std::cout << "Returned true" << std::endl;
            comp.insert(i);
            return true;
        }
    }
    return false;

}

void Graph::ResetIfVisit(){
    //std::cout << "In ResetIfVisit()" << std::endl;
    for (unsigned int i = 0; i < ifVisit.size(); i++) {
        ifVisit.at(i) = false;
        if (ifVisit.at(i)) {
            std::cout << "Failure to reset" << std::endl;
        }
    }

    /*for (auto j : ifVisit){
        int iter = 0;
        std::cout << j.first;
        if (j.second) {
            std::cout << " is true" << std::endl;
        } else {
            std::cout << " is false" << std::endl;
        }
    }*/
}
std::vector<std::set<int>> Graph::GetRuleSCC(){
    std::vector<std::set<int>> orderSets;
    ResetIfVisit();
    for (auto i : postOrder){ //for every rule i == int
        //std::cout << "Rule " << i;
        if (!ifVisit.at(i)){ //if it hasn't been added yet
            //std::cout << " has not been added yet";
            bool success = false;
            for (auto j : SCC){ //for every Strongly connected componenent j == set<int>
                if(!success){
                    //std::cout << " and looking at SCC:";
                    //PrintSCC(j);
                    for (auto k = j.begin(); k != j.end(); k++) { //for each element in set of component k == iter of set<int>
                        //std::cout << " specifically " << *k;
                        if (i == *k) {
                            //std::cout << "and Rule " << i << " = " << *k << std::endl;
                            orderSets.push_back(j); //add the set
                            //std::cout << "So we push back set ";
                            //PrintSCC(orderSets.back());
                            for (auto h : orderSets.back()){ //h == int in set<int>
                                //std::cout << h << "has been added" << std::endl;
                                ifVisit.at(h) = true;//add every element of set to been visited
                                success = true;
                            }

                        }
                    }
                }
            }
        }
    }
    /*for (unsigned int i = 0; i < orderSets.size(); i++){
       // std::cout << i << " SCC is ";
        for (auto j : orderSets.at(i)){
            //std::cout << "R" << j << ",";
        }
        //std::cout << std::endl;
    }*/
    return orderSets;
}

void Graph::InvertPostOrder(){

    std::stack<int> stapo;
    for (auto i : postOrder){
        //std::cout << i << std::endl;
        stapo.push(i);
    }
    std::vector<int> newPost;
    while (!stapo.empty()){
        newPost.push_back(stapo.top());
        stapo.pop();
    }
    postOrder = newPost;
    /*for (auto i : postOrder){
        //std::cout << i << std::endl;
    }*/
}

void Graph::PrintSCC(std::set<int> scc) {
    unsigned int iter = 0;
    //std::cout << scc.size();
    for (auto it = scc.begin(); it != scc.end(); it++) {
        std::cout << "R" << *it;
        if(iter != scc.size() - 1){
            std::cout << ",";
        }
        iter++;
    }
}