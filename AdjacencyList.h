#ifndef ADJACENCYLIST_H__
#define ADJACENCYLIST_H__

#include<vector>

struct Edge {
    int next_node;        // 下一个结点编号
    int weight;        // 该边的权重
    int id;            //该边的编号
};

class AdjacencyList
{
public:
    AdjacencyList() {};
    AdjacencyList(int node_count);
    // ~AdjacencyList();
    bool insert_node(int from_node, int to_node, int edge_weight, int edge_id);
    bool del_node(int node_index, std::vector<int> node_parent);
    int get_outdegree(int node_index);
    void show_list();
    // void show_exist_node();
    std::vector<int> get_son_node(int node_index);
    void del_edge(int from_node, int to_node);
    bool judge_exist_edge(int in_node, int out_node);

    void get_out_edges(int node_index, std::vector<int> &out_node_index);
    int get_num_of_edges();
    void linegraph(int node_index, int pre_node_index, std::vector<std::vector<Edge*> > &linelist);
    void init_visited();
    void getlinegraph1(int edge_cnt);
    void getlinegraph2(int edge_cnt);

    //==============================================
    inline int getNeighbor(int v, int i){return Alist[v][i]->next_node;}
private:
    std::vector<std::vector<Edge*> > Alist;
    // std::vector<bool> exist_node;
    int *visited;
};

#endif