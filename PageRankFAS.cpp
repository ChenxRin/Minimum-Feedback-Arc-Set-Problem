#include "AdjacencyList.h"
#include "Graph.h"
#include "SCC.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <sys/time.h>

using namespace std;


const double alpha = 0.85;        //阻尼系数
const int max_iterations = 5;   //最大迭代次数
const double min_delta = 1e-10;    //确认迭代结束的参数

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

Graph get_data(string filename, int node_cnt, int edge_cnt) {
    Graph graph(node_cnt);
    cout<<"准备读入数据"<<endl;
    ifstream fin;
    fin.open(filename, ios::in);
    int *x;
    int *y;
    x = new int[edge_cnt];
    y = new int[edge_cnt];
    char comma;
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    for(int i = 0; i < edge_cnt; i++){
        fin>>x[i]>>comma>>y[i];
    }
    for(int j = 0; j < edge_cnt; j++){
        graph.insert_node(x[j], y[j], 1, j);
    }
    
    fin.close();
        
    delete(x);
    delete(y);
    cout<<"数据读入成功！"<<endl;
    return graph;
}

/*迭代法实现pagerank*/
int _pagerank(Graph &graph, double oldpr[], double newpr[]){
    
    int n = graph.get_exist_node_cnt();
    int run_tmp[n];
    int inv = 0;
    //cout<<"现存结点个数："<<n;
    int N = graph.get_raw_node_cnt();
    for(int i = 0; i < N; i++){
        if(!graph.is_deleted(i)){
            //cout<<i<<endl;
            oldpr[i] = (double)1 / (double)n;
            newpr[i] = 0;
            run_tmp[inv++] = i;
            if(graph.get_out_degree(i) == 0){
                graph.del_node(i);
            }
        }
        else{
            oldpr[i] = 0;
            newpr[i] = 0;
        }
    }
    int iteration_cnt = 0; //统计迭代次数

    int if_stop = 0; //记录PR值的变化，判断是否终止迭代
    double tmp_pr = 0;
    double sum_pr = 0;
    vector<int> in_nodes;
    vector<int> no_out_edge;
    for(int i = 0; i < n; i++){
        if(graph.get_out_degree(run_tmp[i]) == 0){
            no_out_edge.emplace_back(run_tmp[i]);
        }
    }
    while(!if_stop && iteration_cnt < max_iterations){
        if_stop = 1;
        for(int i = 0; i < n; i++){
                graph.get_in_edges(run_tmp[i], in_nodes);

                for(int j = 0; j < in_nodes.size(); j++){
                    tmp_pr += oldpr[in_nodes[j]] / (double)graph.get_out_degree(in_nodes[j]);
                }
                newpr[run_tmp[i]] = (1 - alpha) / (double)n + alpha * tmp_pr;  
                for(int j = 0; j < no_out_edge.size(); j++){
                    newpr[run_tmp[i]] += alpha * (oldpr[no_out_edge[j]] / (double)n);
                }          

                tmp_pr = 0;
                in_nodes.clear();
        }

        int cnt_satisfy = 0;
        for(int i = 0; i < n; i++){
                if(abs(oldpr[run_tmp[i]] - newpr[run_tmp[i]]) < min_delta){
                    cnt_satisfy++;
                }
                oldpr[run_tmp[i]] = newpr[run_tmp[i]];
        }
        
        if(cnt_satisfy < n && iteration_cnt < max_iterations){
            if_stop = 0;
            iteration_cnt++;
        }

    }

    // cout<<"迭代次数为："<<iteration_cnt<<endl;

    int maxpr_id = 0;
    sum_pr = 0;
    sum_pr += oldpr[run_tmp[0]];
    //cout<<oldpr[0]<<endl;
    for(int i = 1; i < n; i++){
        if(oldpr[run_tmp[i]] > oldpr[maxpr_id]){
            maxpr_id = run_tmp[i];
            
        }sum_pr += oldpr[run_tmp[i]];
        //cout<<oldpr[i]<<endl;
    }
    //cout<<"  "<<"删除结点"<<maxpr_id<<" "<<oldpr[maxpr_id]<<"  "<<sum_pr<<endl;
    //oldpr[maxpr_id] = 0;
    return maxpr_id;
}

void run(Graph graph, int edge_cnt){
    // cout<<"/========================原图===========================/"<<endl;
    // graph.show_graph();
    Graph linegraph(edge_cnt);
    cout<<"开始获取线图"<<endl;
    //graph = get_data();
    linegraph = graph.linegraph(edge_cnt);
    //linegraph.show_graph();
    cout<<"线图获取成功！"<<endl;
    // cout<<"/========================线图===========================/"<<endl;
    //linegraph.show_graph();
    cout<<"开始获取连通分量"<<endl;
    SCCEngine<Graph> scc_worker(&linegraph);
    scc_worker.findSCC();
    cout<<"连通分量获取成功！"<<endl;
    int numsSCC = scc_worker.getNumsSCC();
    cout<<"连通分量个数为："<<numsSCC<<endl;
    /*对连通分量进行FAS*/
    vector<int> SubgraphNodeCnt(numsSCC);
        
    SubgraphNodeCnt = scc_worker.SubGraphNodeCnt();
    cout<<"成功获取每个连通分量的结点数"<<endl;
    vector<int> dn;
    int del_cnt = 0;
    for(int i = 0; i < numsSCC; i++){        
        if(SubgraphNodeCnt[i] > 1){
            cout<<"开始生成连通分量对应的子图"<<endl;
            Graph sublinegraph(SubgraphNodeCnt[i]);            
            //cout<<"in"<<endl;
            scc_worker.GetSubGraph(sublinegraph, linegraph, i, SubgraphNodeCnt[i]);
            cout<<"成功生成子图"<<endl;
            int N = sublinegraph.get_raw_node_cnt();
            double oldpr[N] = {0};
            double newpr[N] = {0};
            cout<<"开始进行pagerankfas"<<endl;
            while(!sublinegraph.is_acyclic()){
                int del_id = _pagerank(sublinegraph, oldpr, newpr);
                dn.emplace_back(sublinegraph.get_edge_id(del_id));
                sublinegraph.del_node(del_id);
                del_cnt++;
                for(int i = 0; i < N; i++){
                    if(sublinegraph.get_out_degree(i) == 0 && !sublinegraph.is_deleted(i)){
                        sublinegraph.del_node(i);
                    }
                }
            }
        }    
    }
    cout<<"割集边数："<<del_cnt<<endl;
    double fas = (double)del_cnt/(double)edge_cnt;
    cout<<"FAS% = "<<fas<<endl;
    //==========================//
    
    //graph.show_graph();
    

    // for(int i = 0; i < del_cnt; i++){
    //     //cout<<dn[i]<<endl;
    //     graph.del_edge_id(dn[i]);
    // }
    //cout<<"/========================生成子图===========================/"<<endl;
    //graph.show_graph();
}


int main(){
    int node_cnt = 10617;
    int edge_cnt = 72172;
    string filename = "wordassociation-2011.txt";
    struct timeval t1, t2;
    double second;
    gettimeofday(&t1, NULL);
    run(get_data(filename, node_cnt, edge_cnt), edge_cnt);
    gettimeofday(&t2, NULL);
    second = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;
    cout<<"共花费"<<second<<" s"<<endl;
    return 0;
}