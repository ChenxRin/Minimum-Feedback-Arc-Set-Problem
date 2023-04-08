#include "head_file/Graph.h"
#include "head_file/AdjacencyList.h"
#include "utils.cpp"

#include <iostream>
#include <vector>
// #include <set>
// #include <tuple>
#include <string>
#include <algorithm>
#include <fstream>
#include <time.h>

using namespace std;


// Graph get_data(string file_name, int node_count) {
//     /* 
//     本函数从txt文件中读取数据。
//     */
//     // get node_cnt
//     int node_cnt = node_count;
//     Graph graph(node_cnt);
//     //
//     ifstream infile(file_name, ios::in);
//     string line;
//     while (getline(infile, line)) {
//         int i = 0;
//         string x, y;
//         int line_len = line.length();
//         while(line[i]!=',')
//             x += line[i++];
//         i++; // skip ,
//         while(i<line_len)
//             y += line[i++];
//         graph.insert_node(stoi(x), stoi(y), 1);
//     }
//     infile.close();
//     return graph;
// }


vector<int> get_sort(Graph graph) {
    /* 
    本函数实现SortFAS算法流程。
    输入：数据的图。
    输出：经过算法的节点排列。
    */
    vector<int> sort;
    for(int i=0; i<graph.get_exist_node_cnt(); i++)
        sort.push_back(i);
    int val, min, loc;
    for(int v=graph.get_exist_node_cnt()-1; v>=0; v--) {
        val = 0;
        min = 0;
        loc = distance(sort.begin(), find(sort.begin(), sort.end(), v));
        for(int j=loc-1; j>=0; j--) {
            int w = sort[j];
            if(graph.judge_exist_edge(v, w))
                val--;
            else if(graph.judge_exist_edge(w, v))
                val++;
            if(val <= min) {
                min = val;
                loc = j;
            }
        }
        sort.erase(find(sort.begin(), sort.end(), v));
        sort.insert(sort.begin()+loc, v);
    }
    return sort;
}

// vector<tuple<int, int> > get_back_edge_set(vector<int> sort_vec, Graph graph) {
//     // tuple<int, int> tuple_name(1, 5);
//     // cout << get<0>(tuple_name) << get<1>(tuple_name) << endl;
//     vector<tuple<int, int> > back_edge_set;
//     set<int> visited_node;
//     for(int i=0; i<sort_vec.size(); i++) {
//         // if(!visited_node.empty()) {
//            vector<int> out_nodes = graph.get_out_nodes(sort_vec[i]);
//             for(int j=0; j<out_nodes.size(); j++) {
//                 if(visited_node.find(out_nodes[j]) != visited_node.end()) {
//                     // cout << sort_vec[i] << " " << out_nodes[j] << endl;
//                     back_edge_set.push_back(make_tuple(sort_vec[i], out_nodes[j]));
//                 }
//             } 
//         // }
//         visited_node.insert(sort_vec[i]);
//     }
//     return back_edge_set;
// }




double run(Graph graph, int edge_cnt) {
    clock_t start, end;
    start = clock();
    // graph.show_graph();
    vector<int> sort_vec = get_sort(graph);
    // cout << "排列结果：" << endl;
    // for(int i=0; i<sort_vec.size(); i++)
    //     cout << sort_vec[i] << " ";
    // cout << endl;
    vector<tuple<int, int> > back_edge_set = get_back_edge_set(sort_vec, graph);
    cout << "后向边数量：" << back_edge_set.size() << endl;
    cout << "FAS%:" << back_edge_set.size()*1.0/edge_cnt << endl;
    // cout << "后向边结果：" << endl;
    // for(int i=0; i<back_edge_set.size(); i++)
    //     cout << get<0>(back_edge_set[i]) << "->" << get<1>(back_edge_set[i]) << endl;
    // // 输出运行结果为：去除后向边之后的子图。
    for(int i=0; i<back_edge_set.size(); i++)
        graph.del_edge(get<0>(back_edge_set[i]), get<1>(back_edge_set[i]));
    cout << graph.is_acyclic() << endl;
    // graph.show_graph();
    // 验证生成的图是否成功：判断一下图是不是已经无环。
    // TODO：在运行完一个实例之后，增加一个操作用于释放掉相关的内存空间，节省内存空间。
    end = clock();
    return (double)(end-start)/CLOCKS_PER_SEC;
}



int main(int argc, char const *argv[])
{
    // run(get_data("./data/test.txt", 10), 60);
    // return 0;
    double running_time = 0;
    cout << "算法SortFAS运行结果如下：" << endl;
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
