#include<iostream>
#include<vector>

using namespace std;


struct Edge {
    int next_node;        // 下一个结点编号
    int weight;        // 该边的权重
};

class AdjacencyList
{
public:
    AdjacencyList(int node_count);
    // ~AdjacencyList();
    bool insert_node(int from_node, int to_node, int edge_weight);
    bool del_node(int node_index, vector<int> node_parent);
    int get_outdegree(int node_index);
    void show_list();
    vector<int> get_parent_node(int node_index);
private:
    vector<vector<Edge*> > Alist;

};