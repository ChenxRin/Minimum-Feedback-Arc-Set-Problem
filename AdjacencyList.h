#ifndef ADJACENCYLIST_H__
#define ADJACENCYLIST_H__

#include<vector>


struct Edge {
    int next_node;        // 下一个结点编号
    int weight;        // 该边的权重
};

class AdjacencyList
{
public:
    AdjacencyList() {};
    AdjacencyList(int node_count);
    // ~AdjacencyList();
    bool insert_node(int from_node, int to_node, int edge_weight);
    bool del_node(int node_index, std::vector<int> node_parent);
    int get_outdegree(int node_index);
    void show_list();
    // void show_exist_node();
    std::vector<int> get_son_node(int node_index);
    void del_edge(int from_node, int to_node);
    bool judge_exist_edge(int in_node, int out_node);
private:
    std::vector<std::vector<Edge*> > Alist;
    // std::vector<bool> exist_node;
};

#endif