#include<iostream>
#include<string.h>
// #include<algorithm>
// #include<vector>

using namespace std;

#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(int node_count) {
    Alist.resize(node_count);
    // exist_node.resize(node_count);
    // fill(exist_node.begin(), exist_node.end(), true);
}


bool AdjacencyList::insert_node(int from_node, int to_node, int edge_weight, int edge_id) {
    Edge* edge = new Edge();
    edge->next_node = to_node;
    edge->weight = edge_weight;
    edge->id = edge_id;
    // cout << edge->next_node << " " << edge->weight << endl;
    Alist[from_node].push_back(edge);
    return true;
}

bool AdjacencyList::del_node(int node_index, vector<int> node_parent) {
    // todo
    // 删除节点跟所有子节点的连接边
    int node_cnt = Alist[node_index].size();
    // 别删数据
    // for(int i=0; i<node_cnt; i++) {
    //     delete Alist[node_index][i];
    // }
    // exist_node[node_index] = false;
    Alist[node_index].clear();
    // 删除节点跟所有父节点的连接边
    for(int i=0; i<node_parent.size(); i++) {
        int parent_idx = node_parent[i];
        for(int j=0; j<Alist[parent_idx].size(); j++) {
            if(Alist[parent_idx][j]->next_node==node_index) {
                // 别删数据
                // delete Alist[parent_idx][j];
                Alist[parent_idx].erase(Alist[parent_idx].begin() + j);
                break;
            }
        }
    }
    return true;
}


void AdjacencyList::del_edge(int from_node, int to_node) {
    for(int j=0; j<Alist[from_node].size(); j++) {
        if(Alist[from_node][j]->next_node==to_node) {
            // 别删数据
            // delete Alist[parent_idx][j];
            Alist[from_node].erase(Alist[from_node].begin() + j);
            break;
        }
    }
}


vector<int> AdjacencyList::get_son_node(int node_index) {
    vector<int> node_son;
    int node_cnt = Alist[node_index].size();
    for(int i=0; i<node_cnt; i++) {
        node_son.push_back(Alist[node_index][i]->next_node);
    }
    return node_son;
}


int AdjacencyList::get_outdegree(int node_index) {
    return Alist[node_index].size();
}

// AdjacencyList::~AdjacencyList() {
//     for(int i=0; i<Alist.size(); i++) {
//         int temp = Alist[i].size();
//         for(int j=0; j<temp; j++) {
//             delete Alist[i][j];
//         }
//         Alist[i].clear();
//     }
// }

void AdjacencyList::show_list() {
    for(int i=0; i<Alist.size(); i++) {
        cout << "node: " << i << " edge: " ;
        int temp = Alist[i].size();
        for(int j=0; j<temp; j++) {
            cout << i << "->" << Alist[i][j]->next_node << ", ";
        }
        cout << endl;
    }
}

bool AdjacencyList::judge_exist_edge(int in_node, int out_node) {
    for(int i=0; i<Alist[in_node].size(); i++)
        if(Alist[in_node][i]->next_node == out_node)
            return true;
    return false;
}

void AdjacencyList::get_out_edges(int node_index, std::vector<int> &out_node_index){
    int size = AdjacencyList::get_outdegree(node_index);
    for(int i = 0; i < size; i++){
        out_node_index.emplace_back(Alist[node_index][i]->next_node);
    }
}

void AdjacencyList::init_visited(){
    visited = new int[Alist.size()];
    memset(visited, 0, Alist.size() * sizeof(int));
}

int AdjacencyList::get_num_of_edges(){
    int n;
    for(int i = 0; i < Alist.size(); i++){
        n += Alist[i].size();
    }
    return n;
}

void AdjacencyList::linegraph(int node_index, int pre_edge_index, std::vector<std::vector<Edge*> > &linelist){
    visited[node_index] = 1;
    for(int i = 0; i < Alist[node_index].size(); i++){
        Edge *edge = new Edge;
        edge->next_node = Alist[node_index][i]->id;
        linelist[pre_edge_index].emplace_back(edge);
        // cout<<node_index<<"->"<<Alist[node_index][i]->next_node<<"\t"<<pre_edge_index<<"->"<<Alist[node_index][i]->id<<endl;
        // if(pre_edge_index == 2)cout<<"---------\n"<<Alist[node_index][i]->id<<"  "<<node_index<<"  "<<i<<"  "<<linelist[2][i]->next_node<<"\n---------\n"<<endl;
        if(visited[Alist[node_index][i]->next_node] == 0){
            //cout<<"in!"<<endl;
            AdjacencyList::linegraph(Alist[node_index][i]->next_node, Alist[node_index][i]->id, linelist);
        }
        else{
            for(int j = 0; j < Alist[Alist[node_index][i]->next_node].size(); j++){
                Edge *edge1 = new Edge;
                edge1->next_node = Alist[Alist[node_index][i]->next_node][j]->id;
                linelist[Alist[node_index][i]->id].emplace_back(edge1);
            }
        }
    }
}

/*递归（论文中方法）*/
void AdjacencyList::getlinegraph1(int edge_cnt){
    std::vector<std::vector<Edge*> > linelist;
    linelist.resize(edge_cnt + 1);
    init_visited();
    linegraph(0, edge_cnt, linelist);
    linelist.pop_back();

    Alist.swap(linelist);
    // for(int i = 0; i < edge_cnt; i++){
    //     for(int j = 0; j < Alist[i].size(); j++){
    //         cout<<i<<" "<<Alist[i][j]->next_node<<endl;
    //     }
    // }
}

/*三层循环实现*/
void AdjacencyList::getlinegraph2(int edge_cnt){
    std::vector<std::vector<Edge*> > linelist;
    linelist.resize(edge_cnt);
    //std::vector<Edge*> tmp_list;

    for(int i = 0; i < Alist.size(); i++){
        for(int j = 0; j < Alist[i].size(); j++){
            for(int k = 0; k < Alist[Alist[i][j]->next_node].size(); k++){
                Edge *edge = new Edge;
                edge->next_node = Alist[Alist[i][j]->next_node][k]->id;
                linelist[Alist[i][j]->id].emplace_back(edge);
            }
            // linelist.emplace_back(tmp_list);
            // tmp_list.clear();
        }
    }

    Alist.swap(linelist);
}

// void AdjacencyList::show_exist_node() {
//     for(int i=0; i<exist_node.size(); i++)
//         cout << i << " " << exist_node[i] << endl;
// }


// int main(int argc, char const *argv[])
// {
//     // 插入示例
//     AdjacencyList graph(7);
//     int x[] = {0, 2, 3, 3, 5, 6};
//     int y[] = {1, 3, 1, 0, 6, 4};
//     for(int i=0; i<6; i++)
//         graph.insert_node(x[i], y[i], 1);

//     // cout << graph.get_outdegree(0) << endl;
//     // graph.show_list();
//     vector<int> node_parent;
//     node_parent.push_back(2);
//     graph.del_node(3, node_parent);
//     // graph.show_list();

//     return 0;
// }


