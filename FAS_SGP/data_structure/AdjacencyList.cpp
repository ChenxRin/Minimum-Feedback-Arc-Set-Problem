#include<iostream>

#include<string.h>
#include<queue>

using namespace std;

#include "../head_file/AdjacencyList.h"



AdjacencyList::AdjacencyList(int node_count) {
    Alist.resize(node_count);
    deleted = new int[node_count];
    visited = new int[node_count];
    indegree = new int[node_count];
    memset(deleted, 0, node_count*sizeof(int));
    memset(visited, 0, node_count*sizeof(int));
    memset(indegree, 0, node_count*sizeof(int));
    exist_node_count = node_count;
}


bool AdjacencyList::insert_node(int from_node, int to_node, int scc_id, int edge_id) {
    Edge* edge = new Edge();
    edge->next_node = to_node;
    edge->cc_id = scc_id;
    edge->id = edge_id;
    Alist[from_node].push_back(edge);
    indegree[to_node]++;
    return true;
}



bool AdjacencyList::del_node(int node_index, vector<int> node_parent) {
    /* 
    本函数实现删除节点跟所有子节点的连接边。
    */
    int node_cnt = Alist[node_index].size();
    for(int i = 0; i < node_cnt; i++){
        indegree[Alist[node_index][i]->next_node]--;
    }
    Alist[node_index].clear();
    // 删除节点跟所有父节点的连接边
    for(int i=0; i<node_parent.size(); i++) {
        int parent_idx = node_parent[i];
        for(int j=0; j<Alist[parent_idx].size(); j++) {
            if(Alist[parent_idx][j]->next_node==node_index) {
                Alist[parent_idx].erase(Alist[parent_idx].begin() + j);
                break;
            }
        }
    }
    deleted[node_index] = 1;
    indegree[node_index] = -1;
    exist_node_count--;
    return true;
}


void AdjacencyList::del_edge(int from_node, int to_node) {
    indegree[to_node]--;
    for(int j=0; j<Alist[from_node].size(); j++) {
        if(Alist[from_node][j]->next_node==to_node) {
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


int AdjacencyList::get_num_of_edges(){
    int n;
    for(int i = 0; i < Alist.size(); i++){
        n += Alist[i].size();
    }
    return n;
}


void AdjacencyList::linegraph(int node_index, int pre_edge_index, std::vector<std::vector<int> > &linelist){
    visited[node_index] = 1;
    for(int i = 0; i < Alist[node_index].size(); i++){
        linelist[0].emplace_back(pre_edge_index);
        linelist[1].emplace_back(Alist[node_index][i]->id);
        
        if(visited[Alist[node_index][i]->next_node] == 0){
            AdjacencyList::linegraph(Alist[node_index][i]->next_node, Alist[node_index][i]->id, linelist);
        }
        else{
            for(int j = 0; j < Alist[Alist[node_index][i]->next_node].size(); j++){
                linelist[0].emplace_back(Alist[node_index][i]->id);
                linelist[1].emplace_back(Alist[Alist[node_index][i]->next_node][j]->id);
            }
        }
    }
}

/*递归（论文中方法）,每次只能处理一个连通分量*/
std::vector<std::vector<int>> AdjacencyList::getlinegraph1(int edge_cnt){
    std::vector<std::vector<int> > linelist(2);
    //linelist.resize(edge_cnt + 1);
    linegraph(0, edge_cnt, linelist);
    linelist[0].erase(linelist[0].begin());
    linelist[1].erase(linelist[1].begin());

    return linelist;
}

/*三层循环实现*/
std::vector<std::vector<int>> AdjacencyList::getlinegraph2(int edge_cnt){
    std::vector<std::vector<int> > linelist(2);

    for(int i = 0; i < Alist.size(); i++){
        for(int j = 0; j < Alist[i].size(); j++){
            for(int k = 0; k < Alist[Alist[i][j]->next_node].size(); k++){
                linelist[0].emplace_back(Alist[i][j]->id);
                linelist[1].emplace_back(Alist[Alist[i][j]->next_node][k]->id);
            }
        }
    }
    return linelist;
}

void AdjacencyList::out_graph_del_edge_id(int edge_id){
    int k = 0, i = 0;
    while(k <= edge_id){
        k += Alist[i++].size();
    }

    for(int j = 0; j < Alist[i - 1].size(); i++){
        if(Alist[i - 1][j]->id == edge_id){
            Alist[i - 1].erase(Alist[i - 1].begin() + j);
        }
        break;
    }
}

void AdjacencyList::in_graph_del_edge_id(int edge_id){
    for(int i = 0; i < Alist.size(); i++){
        for(int j = 0; j < Alist[i].size(); j++){
            if(Alist[i][j]->id == edge_id){
                Alist[i].erase(Alist[i].begin() + j);
                break;
            }
        }
    }
}

/*使用拓扑排序进行环路检测*/
bool AdjacencyList::is_acyclic(){
    int node_cnt = exist_node_count;
    int *indegree_tmp;
    indegree_tmp = new int[Alist.size()];
    memcpy(indegree_tmp, indegree, Alist.size()*sizeof(int));

    queue<int> node;
    for(int i = 0; i < Alist.size(); i++){
        if(indegree_tmp[i] == 0){
            node.push(i);
        }
    }

    int number = 0;
    while(!node.empty()){
        int u = node.front();
        node.pop();
        number++;
        for(int i = 0; i < Alist[u].size(); i++){
            int v = Alist[u][i]->next_node;
            indegree_tmp[v]--;
            if(indegree_tmp[v] == 0)node.push(v);
        }
    }
    delete(indegree_tmp);
    return node_cnt == number;
}



std::vector<std::vector<int> > AdjacencyList::get_sublist(std::vector<int> node_id){
    std::vector<std::vector<int> > sublist;
    sublist.resize(3);
    for(int i = 0; i < node_id.size(); i++){
        Alist[node_id[i]][0]->new_node_id = i;
    } 
    int inv = 0;
    for(int i = 0; i < node_id.size(); i++){
        for(int j = 0; j < Alist[node_id[i]].size(); j++){

                if(Alist[Alist[node_id[i]][j]->next_node].size() > 0 
                && Alist[Alist[node_id[i]][j]->next_node][0]->cc_id == Alist[node_id[0]][0]->cc_id){
                    sublist[0].emplace_back(i);
                    sublist[1].emplace_back(Alist[Alist[node_id[i]][j]->next_node][0]->new_node_id);
                    sublist[2].emplace_back(node_id[i]);
                }    
                inv++;
                    
        }
    }
    return sublist;
}

int AdjacencyList::get_edge_id(int node_index){
    return Alist[node_index][0]->id;
}

void AdjacencyList::show_sublist(){
    int inv = 0;
    for(int i = 0; i < Alist.size(); i++){
        for(int j = 0; j < Alist[i].size(); j++){
            cout<<i<<"->"<<Alist[i][j]->next_node<<"  ";
            inv++;
            if(inv > 5)break;
        }
        cout<<endl;
    }
}

void AdjacencyList::give_cc_id(int node_index, int cc_id){
    Alist[node_index][0]->cc_id = cc_id;
}

bool AdjacencyList::no_self_loop(int node_index){
    for(int i = 0; i < Alist[node_index].size(); i++){
        if(node_index == Alist[node_index][i]->next_node){
            return false;
        }
    }
    return true;
}


