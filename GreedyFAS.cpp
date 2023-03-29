#include "Graph.h"
#include "AdjacencyList.h"

#include<iostream>
#include<vector>
#include<set>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;


Graph get_data(string file_name) {
    /* 
    本函数从txt文件中读取数据。
    */
    // get node_cnt
    int node_cnt = 7;
    Graph graph(node_cnt);
    //
    ifstream infile(file_name, ios::in);
    string line;
    while (getline(infile, line)) {
        int i = 0;
        string x, y;
        int line_len = line.length();
        while(line[i]!=',')
            x += line[i++];
        i++; // skip ,
        while(i<line_len)
            y += line[i++];
        graph.insert_node(stoi(x), stoi(y), 1);
    }
    infile.close();
    // int x[] = {0, 1, 2, 3, 3, 4, 5, 6};
    // int y[] = {1, 2, 3, 1, 0, 5, 6, 4};
    // for(int i=0; i<8; i++)
    //     graph.insert_node(x[i], y[i], 1);
    return graph;
}

// stoi(str)

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
            s2.insert(s2.begin(), node_index);
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
    s1s2.insert(s1s2.end(), s1.begin(), s1.end());
    s1s2.insert(s1s2.end(), s2.begin(), s2.end());
    return s1s2;
}

vector<tuple<int, int> > get_back_edge_set(vector<int> min_sort, Graph graph) {
    // tuple<int, int> tuple_name(1, 5);
    // cout << get<0>(tuple_name) << get<1>(tuple_name) << endl;
    vector<tuple<int, int> > back_edge_set;
    set<int> visited_node;
    for(int i=0; i<min_sort.size(); i++) {
        // if(!visited_node.empty()) {
           vector<int> out_nodes = graph.get_out_nodes(min_sort[i]);
            for(int j=0; j<out_nodes.size(); j++) {
                if(visited_node.find(out_nodes[j]) != visited_node.end()) {
                    // cout << min_sort[i] << " " << out_nodes[j] << endl;
                    back_edge_set.push_back(make_tuple(min_sort[i], out_nodes[j]));
                }
            } 
        // }
        visited_node.insert(min_sort[i]);
    }
    return back_edge_set;
}


void run(Graph graph) {
    // graph.show_graph();
    // graph.show_degree();

    // cout << "删除一个节点3" << endl;
    // graph.del_node(3);

    graph.show_graph();
    // graph.show_degree();
    vector<int> min_sort = get_min_sort(graph);
    cout << "线性排列结果：" << endl;
    for(int i=0; i<min_sort.size(); i++)
        cout << min_sort[i] << " ";
    cout << endl;
    graph.show_graph();
    vector<tuple<int, int> > back_edge_set = get_back_edge_set(min_sort, graph);
    cout << "后向边数量：" << back_edge_set.size() << endl;
    cout << "后向边结果：" << endl;
    for(int i=0; i<back_edge_set.size(); i++)
        cout << get<0>(back_edge_set[i]) << "->" << get<1>(back_edge_set[i]) << endl;
    // 输出运行结果为：去除后向边之后的子图。
    for(int i=0; i<back_edge_set.size(); i++)
        graph.del_edge(get<0>(back_edge_set[i]), get<1>(back_edge_set[i]));
    graph.show_graph();
    // TODO：在运行完一个实例之后，增加一个操作用于释放掉相关的内存空间，节省内存空间。
}


int main(int argc, char const *argv[])
{
    string file_name = "./data/example.txt";
    run(get_data(file_name));
    return 0;
}








