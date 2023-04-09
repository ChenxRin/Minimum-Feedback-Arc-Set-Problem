#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>


using namespace std;


Graph get_data(string file_name, int node_count) {
    /* 
    本函数从txt文件中读取数据。
    输入：数据文件的路径，一共的节点数量。
    输出：根据数据构建好的图数据结构。
    */
    int node_cnt = node_count;
    Graph graph(node_cnt);
    ifstream infile(file_name, ios::in);
    string line;
    while (getline(infile, line)) {
        int i = 0;
        string x, y;
        int line_len = line.length();
        while(line[i]!=',')
            x += line[i++];
        i++;
        while(i<line_len)
            y += line[i++];
        graph.insert_node(stoi(x), stoi(y), 0, 0);
    }
    infile.close();
    return graph;
}


vector<tuple<int, int> > get_back_edge_set(vector<int> sort_vec, Graph graph) {
    /* 
    本函数统计输入排列的后向边集合。
    输入：节点的排列，相关的图数据结构。
    输出：后向边集合，作为最小反馈弧集合。
    */
    vector<tuple<int, int> > back_edge_set;
    set<int> visited_node;
    for(int i=0; i<sort_vec.size(); i++) {
           vector<int> out_nodes = graph.get_out_nodes(sort_vec[i]);
            for(int j=0; j<out_nodes.size(); j++)
                if(visited_node.find(out_nodes[j]) != visited_node.end())
                    back_edge_set.push_back(make_tuple(sort_vec[i], out_nodes[j]));
        visited_node.insert(sort_vec[i]);
    }
    return back_edge_set;
}
