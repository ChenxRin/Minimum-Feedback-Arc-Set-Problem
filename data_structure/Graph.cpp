#include "../head_file/Graph.h"
#include "../head_file/AdjacencyList.h"

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


Graph::Graph(int node_cnt) {
    AdjacencyList new_out_graph(node_cnt);
    AdjacencyList new_in_graph(node_cnt);
    out_graph = new_out_graph;
    in_graph = new_in_graph;
    out_degree.resize(node_cnt);
    in_degree.resize(node_cnt);
    delta.resize(node_cnt);
    exist_node.resize(node_cnt);
    fill(exist_node.begin(), exist_node.end(), true);
    node_count = node_cnt;
    raw_node_cnt = node_cnt;
}

// bool Graph::insert_node(int from_node, int to_node, int edge_weight) {
//     out_graph.insert_node(from_node, to_node, edge_weight);
//     in_graph.insert_node(to_node, from_node, edge_weight);
//     // update
//     update_degree(from_node);
//     update_degree(to_node);
//     return true;
// }

bool Graph::insert_node(int from_node, int to_node, int scc_id, int edge_id) {
    out_graph.insert_node(from_node, to_node, scc_id, edge_id);
    in_graph.insert_node(to_node, from_node, scc_id, edge_id);
    // update
    update_degree(from_node);
    update_degree(to_node);
    return true;
}


bool Graph::del_node(int node_index) {
    exist_node[node_index] = false;
    node_count--;
    vector<int> out_graph_son = out_graph.get_son_node(node_index);
    vector<int> in_graph_son = in_graph.get_son_node(node_index);
    out_graph.del_node(node_index, in_graph_son);
    in_graph.del_node(node_index, out_graph_son);
    // update
    update_degree(node_index);
    for(int i=0; i<out_graph_son.size(); i++)
        update_degree(out_graph_son[i]);
    for(int i=0; i<in_graph_son.size(); i++)
        update_degree(in_graph_son[i]);
    return true;
}


void Graph::del_edge(int from_node, int to_node) {
    update_degree(from_node);
    update_degree(to_node);
    out_graph.del_edge(from_node, to_node);
    in_graph.del_edge(to_node, from_node);
}


void Graph::update_degree(int node_index) {
    out_degree[node_index] = out_graph.get_outdegree(node_index);
    in_degree[node_index] = in_graph.get_outdegree(node_index);;
    delta[node_index] = out_degree[node_index]-in_degree[node_index];
}


void Graph::show_graph() {
    cout << "出度图打印：" << endl;
    out_graph.show_list();
    cout << "入度图打印：" << endl;
    in_graph.show_list();
}

void Graph::show_degree() {
    cout << "出度打印：" << endl;
    for(int i=0; i<out_degree.size(); i++)
        cout << i << ": " << out_degree[i] << endl;
    cout << "入度打印：" << endl;
    for(int i=0; i<in_degree.size(); i++)
        cout << i << ": " << in_degree[i] << endl;
    cout << "delta打印：" << endl;
    for(int i=0; i<delta.size(); i++)
        cout << i << ": " << delta[i] << endl;
}


void Graph::show_exist_node() {
    cout << "打印图中现存节点：" << endl;
    for(int i=0; i<exist_node.size(); i++)
        cout << i << " " << exist_node[i] << endl;
}

int Graph::get_source_node() {
    if(node_count==0)
        return -1;
    for(int i=0; i<in_degree.size(); i++) {
        if (exist_node[i] && in_degree[i]==0) {
            return i;
        }
    }
    return -1;
}

int Graph::get_sink_node() {
    if(node_count==0)
        return -1;
    for(int i=0; i<out_degree.size(); i++) {
        if (exist_node[i] && out_degree[i]==0) {
            return i;
        }
    }
    return -1;
}

int Graph::get_max_delta_node() {
    if(node_count==0)
        return -1;
    int node_index = -1;
    int max_delta = -2147483648;

    for(int i=0; i<delta.size(); i++) {
        if (exist_node[i] && delta[i]>max_delta) {
            node_index = i;
            max_delta = delta[i];
        }
    }
    return node_index;
}


int Graph::get_exist_node_cnt() {
    return node_count;
}


vector<int> Graph::get_out_nodes(int node_index) {
    return out_graph.get_son_node(node_index);
}

bool Graph::judge_exist_edge(int in_node, int out_node) {
    return out_graph.judge_exist_edge(in_node, out_node);
}

void Graph::get_in_edges(int node_index, std::vector<int> &in_node_index){
    in_graph.get_out_edges(node_index, in_node_index);
}

Graph Graph::linegraph(int edge_cnt){
    Graph linegraph(edge_cnt);
    std::vector<std::vector<int>> linelist(2);
    //cout<<"开始获取线图"<<endl;
    linelist = out_graph.getlinegraph2(edge_cnt);
    for(int i = 0; i < linelist[0].size(); i++){
        linegraph.insert_node(linelist[0][i], linelist[1][i], 1, 1);
    }
    //linegraph.show_graph();
    return linegraph;
}

void Graph::del_edge_id(int edge_id){
    out_graph.in_graph_del_edge_id(edge_id);
    in_graph.in_graph_del_edge_id(edge_id);
}

bool Graph::is_acyclic(){
    return out_graph.is_acyclic();
}

Graph Graph::get_subgraph(std::vector<int> node_id){
    Graph subgraph(node_id.size());
    std::vector<std::vector<int>> sublist(3);
    sublist = out_graph.get_sublist(node_id);
    //cout<<"开始插入"<<endl;
    for(int i = 0; i < sublist[0].size(); i++){
        subgraph.insert_node(sublist[0][i], sublist[1][i], 1, sublist[2][i]);
    }
    return subgraph;
}

int Graph::get_edge_id(int node_index){
    return out_graph.get_edge_id(node_index);
}

void Graph::show_subgraph(){
    out_graph.show_sublist();
}

void Graph::give_cc_id(int node_index, int cc_id){
    out_graph.give_cc_id(node_index, cc_id);
}


// int main(int argc, char const *argv[])
// {
//     Graph graph(7);
//     int x[] = {0, 2, 3, 3, 5, 6};
//     int y[] = {1, 3, 1, 0, 6, 4};
//     for(int i=0; i<6; i++)
//         graph.insert_node(x[i], y[i], 1);

//     // graph.show_graph();
//     // graph.show_degree();
//     graph.show_exist_node();

//     cout << "删除一个节点3" << endl;
//     graph.del_node(3);

//     // graph.show_graph();
//     // graph.show_degree();
//     graph.show_exist_node();

//     return 0;
// }

