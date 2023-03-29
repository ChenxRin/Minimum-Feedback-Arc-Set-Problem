#include "AdjacencyList.h"
#include "Graph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


const double alpha = 0.85;        //阻尼系数
const int max_iterations = 100;   //最大迭代次数
const double min_delta = 1e-7;    //确认迭代结束的参数

// /*计算图的边数*/
// int get_nedges(char filename){
//     ifstream fin;
//     fin.open("filename", ios::in);

//     set<int> s;
//     int u, v;
//     while(fin>>u>>v){
//         s.insert(u);
//         s.insert(v);
//     }

//     int N = s.size();
//     fin.close();
//     return N;
// }

// void creat_graph(int N, char filename, Graph &graph){
//     ifstream fin;
//     fin.open("filename", ios::in);

//     int u, v;
//     double weight = 0.5 / N;
//     while(fin>>u>>v){
//         graph.insert_node(u, v, weight);
//     }
// }

Graph get_data() {
    Graph graph(4);
    int x[] = {0, 1, 2, 3, 3};
    int y[] = {1, 2, 3, 0, 1};
    for(int i=0; i<5; i++)
        graph.insert_node(x[i], y[i], 1, i);
    
    //graph.linegraph();
    return graph;
}



/*迭代法实现pagerank*/
void pagerank(Graph graph){
    
    int N = graph.get_exist_node_cnt();
    double oldpr[N];
    double newpr[N];
    for(int i = 0; i < N; i++){
        oldpr[i] = 1/(double)N;
    }
    int iteration_cnt = 0; //统计迭代次数

    int if_stop = 0; //记录PR值的变化，判断是否终止迭代
    // int out_degree = 0;
    double tmp_pr = 0;
    vector<int> in_nodes;
    while(!if_stop && iteration_cnt < max_iterations){
        if_stop = 1;
        
        for(int i = 0; i < N; i++){
            // out_degree = graph.get_out_degree(i);
            graph.get_out_edges(i, in_nodes);

            for(int j = 0; j < in_nodes.size(); j++){
                tmp_pr += oldpr[in_nodes[j]] / graph.get_out_degree(in_nodes[j]);
            }
            //cout<<tmp_pr<<endl;
            // cout<<in_nodes.size()<<endl;
            newpr[i] = (1 - alpha) / N + alpha * tmp_pr;

            tmp_pr = 0;
            in_nodes.clear();
        }

        int cnt_satisfy = 0;
        for(int i = 0; i < N; i++){
            if(abs(oldpr[i] - newpr[i]) < min_delta){
                cnt_satisfy++;
            }
            //cout<<abs(oldpr[i] - newpr[i])<<endl;
            oldpr[i] = newpr[i];
        }
        
        //cout<<cnt_satisfy<<endl;
        if(cnt_satisfy < N && iteration_cnt < max_iterations){
            if_stop = 0;
            iteration_cnt++;
        }

        //cout<<if_stop<<endl;

    }

    for(int i = 0; i < N; i++){
        cout<<oldpr[i]<<endl;
    }

    cout<<"迭代次数为："<<iteration_cnt<<endl;
}

int main(){
    Graph graph = get_data();
    graph.linegraph(5);
    graph.show_graph();
    pagerank(graph);
    
    return 0;
}