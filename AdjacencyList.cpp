#include<iostream>
// #include<algorithm>
// #include<vector>

using namespace std;

#include "AdjacencyList.h"


AdjacencyList::AdjacencyList(int node_count) {
    Alist.resize(node_count);
    // exist_node.resize(node_count);
    // fill(exist_node.begin(), exist_node.end(), true);
}


// AdjacencyList::AdjacencyList(const AdjacencyList &obj)
// {
//     cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
//     for(int i=0; i<obj.Alist.size(); i++) {
//         int temp = obj.Alist[i].size();
//         for(int j=0; j<temp; j++) {
//             Edge* edge = new Edge();
//             edge->next_node = obj.Alist[i][j]->next_node;
//             edge->weight = obj.Alist[i][j]->edge_weight;
//             Alist[i].push_back(edge);
//         }
//     }
// }

bool AdjacencyList::insert_node(int from_node, int to_node, int edge_weight) {
    Edge* edge = new Edge();
    edge->next_node = to_node;
    edge->weight = edge_weight;
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


