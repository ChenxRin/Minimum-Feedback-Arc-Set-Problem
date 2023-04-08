#ifndef GRAPH_H__
#define GRAPH_H__

#include<vector>
#include "AdjacencyList.h"


class Graph {
public:
    Graph(int node_cnt);
    // ~Graph();
    // bool insert_node(int from_node, int to_node, int edge_weight);
    bool insert_node(int from_node, int to_node, int scc_id, int edge_id);
    bool del_node(int node_index);
    void show_graph();
    void show_degree();
    void show_exist_node();
    void update_degree(int node_index);
    int get_source_node();
    int get_sink_node();
    int get_max_delta_node();
    int get_exist_node_cnt();
    void del_edge(int from_node, int to_node);
    std::vector<int> get_out_nodes(int node_index);
    bool judge_exist_edge(int in_node, int out_node);

    int get_out_degree(int node_index);
    void get_in_edges(int node_index, std::vector<int> &in_node_index);
    Graph linegraph(int edge_cnt);
    void del_edge_id(int edge_id);
    bool is_acyclic();
    Graph get_subgraph(std::vector<int> node_id);
    int get_edge_id(int node_index);
    inline int get_raw_node_cnt(){return raw_node_cnt;}
    inline bool is_deleted(int node_index){return out_graph.is_deleted(node_index);}
    void show_subgraph();
    void give_cc_id(int node_index, int cc_id);

    //======================================================
    // interface need by SCC
    inline int getOutDegree(int v){return out_graph.get_outdegree(v);}
    inline int getOutNeighbor(int v, int i){return out_graph.getNeighbor(v, i);}
    inline size_t getNumsV(){return node_count;}
    size_t getNumsE();

private:
    AdjacencyList out_graph;
    AdjacencyList in_graph;
    std::vector<int> out_degree;
    std::vector<int> in_degree;
    std::vector<int> delta;
    std::vector<bool> exist_node;
    int node_count;
    int raw_node_cnt;
};

#endif
