#include "Graph.h"
#include "AdjacencyList.h"

#include<iostream>
#include<vector>
#include<set>
#include <tuple>

using namespace std;


Graph get_data() {
    Graph graph(7);
    int x[] = {0, 2, 3, 3, 5, 6};
    int y[] = {1, 3, 1, 0, 6, 4};
    for(int i=0; i<6; i++)
        graph.insert_node(x[i], y[i], 1);
    return graph;
}


vector<int> get_min_sort(Graph graph) {
    vector<int> s1;
    vector<int> s2;
    int node_index = -1;
    // 只要图里还有节点就继续
    while(graph.get_exist_node_cnt()) {
        // step 1
        node_index = graph.get_source_node();
        if(node_index!=-1) {
            graph.del_node(node_index);
            s1.push_back(node_index);
            continue;
        }
        // step 2
        node_index = graph.get_sink_node();
        if(node_index!=-1) {
            graph.del_node(node_index);
            s2.push_front(node_index);
            continue;
        }
        // step 3
        node_index = graph.get_max_delta_node();
        if(node_index!=-1) {
            graph.del_node(node_index);
            s1.push_back(node_index);
        }
    }
    vector<int> s1s2;
    s1s2.insert(s1s2.end(), s1.begin(), s1.end())
    s1s2.insert(s1s2.end(), s2.begin(), s2.end())
    return s1s2;
}

set<tuple<int, int>> get_back_edge_set(vector<int> min_sort, Graph graph) {
    // tuple<int, int> tuple_name(1, 5);
    // cout << get<0>(tuple_name) << get<1>(tuple_name) << endl;
    set<tuple<int, int>> back_edge_set;
    set<int> visited_node;
    for(int i=0; i<min_sort.size(); i++) {
        vector<int> out_nodes = get_out_nodes(i);
        for(int j=0; j<out_nodes.size(); j++) {
            if(visited_node.find(out_nodes[j]->next_node) != visited_node.end()) {
                back_edge_set.insert(make_tuple(out_nodes[j]->next_node, i));
            }
        }
    }
    return back_edge_set;
}


void run(Graph graph) {
    // graph.show_graph();
    // graph.show_degree();

    // cout << "删除一个节点3" << endl;
    // graph.del_node(3);

    // graph.show_graph();
    // graph.show_degree();
    vector<int> min_sort = get_min_sort(graph);
    set<tuple<int, int>> back_edge_set = get_back_edge_set(min_sort, graph);
}


int main(int argc, char const *argv[])
{
    run(get_data());
    return 0;
}








