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
    void show_exist_node();
    void update_degree(int node_index);
    int get_source_node();
    int get_sink_node();
    int get_max_delta_node();
    int get_exist_node_cnt();
    std::vector<int> get_out_nodes(int node_index);
    // bool judge_exist_edge(int in_node, int out_node);

private:
    AdjacencyList out_graph;
    AdjacencyList in_graph;
    std::vector<int> out_degree;
    std::vector<int> in_degree;
    std::vector<int> delta;
    std::vector<bool> exist_node;
    int node_count;
};

#endif
