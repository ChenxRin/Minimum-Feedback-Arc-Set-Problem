#include "head_file/Graph.h"
#include "head_file/AdjacencyList.h"
#include "utils.cpp"
#include "SCC.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;


vector<int> get_min_sort(Graph graph) {
    /* 
    本函数实现GreedyFAS算法流程。
    输入：数据的图。
    输出：经过算法的节点排列。
    */
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
        graph.del_node(node_index);
        s1.push_back(node_index);
    }
    vector<int> s1s2;
    s1s2.insert(s1s2.end(), s1.begin(), s1.end());
    s1s2.insert(s1s2.end(), s2.begin(), s2.end());
    return s1s2;
}


double run(Graph graph, int edge_cnt) {
    clock_t start, end;
    start = clock();
    // graph.show_graph();
    vector<int> min_sort = get_min_sort(graph);
    // cout << "线性排列结果：" << endl;
    // for(int i=0; i<min_sort.size(); i++)
    //     cout << min_sort[i] << " ";
    // cout << endl;
    vector<tuple<int, int> > back_edge_set = get_back_edge_set(min_sort, graph);
    cout << "后向边数量：" << back_edge_set.size() << endl;
    cout << "FAS%:" << back_edge_set.size()*1.0/edge_cnt << endl;
    // cout << "后向边结果：" << endl;
    // for(int i=0; i<back_edge_set.size(); i++)
    //     cout << get<0>(back_edge_set[i]) << "->" << get<1>(back_edge_set[i]) << endl;
    // // 输出运行结果为：去除后向边之后的子图。
    // for(int i=0; i<back_edge_set.size(); i++)
    //     graph.del_edge(get<0>(back_edge_set[i]), get<1>(back_edge_set[i]));
    // graph.show_graph();
    end = clock();
    return (double)(end-start)/CLOCKS_PER_SEC;
}


int main(int argc, char const *argv[])
{
    double running_time = 0;
    cout << "算法GreedyFAS运行结果如下：" << endl;
    cout << "数据集wordassociation-2011.txt结果：" << endl;
    string file_name = "./data/wordassociation-2011.txt";
    running_time = run(get_data(file_name, 10617), 72172);
    cout << "运行时间为：" << running_time << " s" << endl;
    cout << "数据集enron.txt结果：" << endl;
    file_name = "./data/enron.txt";
    running_time = run(get_data(file_name, 69244), 276143);
    cout << "运行时间为：" << running_time << " s" << endl;

    return 0;
}








