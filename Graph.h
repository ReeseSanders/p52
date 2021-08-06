#ifndef PROJECT1_GRAPH_H
#define PROJECT1_GRAPH_H
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include "Rule.h"

class Graph {
private:
    std::map<int, std::set<int>> edges;
    std::map<int, std::set<int>> iEdges;
    std::vector<bool> ifVisit;
    std::vector<bool> ifVisita;
    std::vector<int> postOrder;
    std::set<std::set<int>> SCC;
public:
    Graph(std::vector<Rule> rules);

    void invertEdges();
    int PostOrder(int index);
    void PostOrderHelper(int index);
    void PrintDependGraph();
    void CreateStrong();
    bool FindSCC(std::set<int>& comp, int origin, int current);
    void ResetIfVisit();
    std::vector<std::set<int>> GetRuleSCC();
    void InvertPostOrder();
    void PrintSCC(std::set<int> scc);
};

#endif //PROJECT1_GRAPH_H
