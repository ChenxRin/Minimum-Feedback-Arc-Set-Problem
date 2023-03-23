#ifndef GRAPH_H__
#define GRAPH_H__

#include<vector>
#include "AdjacencyList.h"


class Graph {
public:
    Graph(int node_cnt);
    // ~Graph();
    bool insert_node(int from_node, int to_node, int edge_weight);
    bool del_node(int node_index);
    void show_graph();
    void show_degree();
    void update_degree(int node_index);

private:
    AdjacencyList out_graph;
    AdjacencyList in_graph;
    std::vector<int> out_degree;
    std::vector<int> in_degree;
    std::vector<int> delta;
};

#endif
