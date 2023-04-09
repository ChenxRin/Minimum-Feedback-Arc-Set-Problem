#ifndef ADJACENCYLIST_H__
#define ADJACENCYLIST_H__

#include<vector>


// struct Edge {
//     int next_node;        // 下一个结点编号
//     int weight;        // 该边的权重
// };

struct Edge {
    int next_node;        // 下一个结点编号
    int cc_id;        // 该边所在连通分量的编号
    int id;            //该边的编号
    int new_node_id;   //子图里点的新编号
};

class AdjacencyList
{
public:
    AdjacencyList() {};
    AdjacencyList(int node_count);
    // AdjacencyList( const AdjacencyList &obj); 
    // ~AdjacencyList();
    // bool insert_node(int from_node, int to_node, int edge_weight);
    bool insert_node(int from_node, int to_node, int scc_id, int edge_id);
    bool del_node(int node_index, std::vector<int> node_parent);
    int get_outdegree(int node_index);
    void show_list();
    // void show_exist_node();
    std::vector<int> get_son_node(int node_index);
    void del_edge(int from_node, int to_node);
    bool judge_exist_edge(int in_node, int out_node);

    void get_out_edges(int node_index, std::vector<int> &out_node_index);
    int get_num_of_edges();
    void linegraph(int node_index, int pre_node_index, std::vector<std::vector<int> > &linelist);
    std::vector<std::vector<int>> getlinegraph1(int edge_cnt);
    std::vector<std::vector<int>> getlinegraph2(int edge_cnt);
    void out_graph_del_edge_id(int edge_id);
    void in_graph_del_edge_id(int edge_id);
    bool is_acyclic();
    std::vector<std::vector<int>> get_sublist(std::vector<int> node_id);
    int get_edge_id(int node_index);
    inline bool is_deleted(int node_index){return deleted[node_index];}
    void show_sublist();
    void give_cc_id(int node_index, int cc_id);
    bool no_self_loop(int node_index);

    inline int getNeighbor(int v, int i){return Alist[v][i]->next_node;}

private:
    std::vector<std::vector<Edge*> > Alist;
    // std::vector<bool> exist_node;

    int *visited;
    int *deleted;
    int *indegree;
    int exist_node_count;
    
};

#endif