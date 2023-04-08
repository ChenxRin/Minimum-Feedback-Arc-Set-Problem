//----------------------------------------------------------------
// SCC: find Strongly Connected Components
//----------------------------------------------------------------

// update: modify for interface from entire graph

// created: 2023.3 by zlp

// update: Tarjan's algorithm
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

using uintT = unsigned int;
using intT = int;

// Tarjan algorithm
template<class COM_Graph>
class SCCTarjan {
public:
    SCCTarjan()=default;
    SCCTarjan(size_t nums_v){
        setSize(nums_v);
    }
    // not hold any pass data
    ~SCCTarjan(){}

    // (not intrans) just set dfn and low
    // must be call after set
    // one call find SCC with v inside and others
    void tarjan(COM_Graph &G, uintT v, uintT start_tag=1){
        dfn[v] = low[v] = start_tag++;  // casuse need call recursively
        // return if already in stack
        if(!stackPush(v)){return;}
        // travel out neighbors
        for(size_t i=0; i<G.getOutDegree(v); ++i){
            uintT out_n = G.getOutNeighbor(v, i);
            if(dfn[out_n]==0){
                // new one, not been visit, DFS core
                tarjan(G, out_n, start_tag);
                low[v] = min(low[v], low[out_n]);
            }else if(isInStack(out_n)) {   // v before
                low[v] = min(low[v], low[out_n]);
            }
        }
        // judge, a loop start
        if(dfn[v]==low[v]){
            uintT last_pop;
            while((last_pop=stackPop())!=v){
                if(cc_ids[last_pop]>=0){printf("<fault>algorithm may fail, same v in two scc\n");}
                cc_ids[last_pop] = cc_nums;
            }
            cc_ids[last_pop] = cc_nums;
            // only pop here, pop to v
            ++cc_nums;
        }
        return;
    }

    // public interface, find all SCC (src==-1)
    // return: nums of SCC that find(plus org)
    intT findSCC(COM_Graph &G, intT* &ref_cc_ids, intT exist_cc_nums, intT source_v=-1){
        setSize(G.getNumsV());  // clear each time
        cc_ids = ref_cc_ids;
        cc_nums = exist_cc_nums;
        if(source_v<0){
            for(uintT v=0; v<G.getNumsV(); ++v){
                if(cc_ids[v]<0){
                    tarjan(G, v, 1);
                }
            }
        }else{
            tarjan(G, (uintT)source_v, 1);
        }
        return cc_nums;
    }

    void setSize(size_t nums_v){
        visit_tag.resize(nums_v, false);
        dfn.resize(nums_v, 0);
        low.resize(nums_v, 0);
    }

    void clear(){
        visit_tag.assign(visit_tag.size(), false);
        dfn.resize(dfn.size(), 0);
        low.assign(low.size(), 0);
    }
private:
    inline bool isInStack(uintT v){return visit_tag[v];}
    inline bool stackPush(uintT v){
        if(isInStack(v)){return false;}
        else{
            dfs_stack.push(v);
            visit_tag[v] = true;
            return true;
        }
    }
    inline uintT stackPop(){
        uintT v_b = dfs_stack.top();
        visit_tag[v_b] = false;
        dfs_stack.pop();
        return v_b;
    }
    // cc count
    intT* cc_ids{nullptr};
    intT cc_nums{0};

    // data stack
    stack<uintT> dfs_stack;
    vector<bool> visit_tag;
    // data statistic
    vector<uintT> dfn;
    vector<uintT> low;
};


// scc engine
template <class COM_Graph>
class SCCEngine {
public:
    SCCEngine()=default;
    SCCEngine(COM_Graph* gp):G_p(gp){}
    ~SCCEngine(){
        delete []cc_ids;
    }

    void combine(COM_Graph* gp){G_p=gp;}

    intT findSCC(){
        if(G_p==nullptr){return -1;}
        if(cc_ids==nullptr){
            cc_ids = new intT[G_p->getNumsV()];
            memset(cc_ids, -1, sizeof(intT)*G_p->getNumsV());   
        }
        SCCTarjan<COM_Graph> tarjan_worker;
        cc_nums = tarjan_worker.findSCC(*G_p, cc_ids, cc_nums);
        return cc_nums;
    }

    void printSCC(){
        cout<<"------------(SCC Message)-------------"<<endl;
        cout<<"[nums SCC]: "<<cc_nums<<endl;
        for(size_t i=0; i<G_p->getNumsV(); ++i){
            cout<<cc_ids[i]<<" ";
        }cout<<endl;
    }
    intT getNumsSCC(){return cc_nums;}

    //==============
    vector<intT> SubGraphNodeCnt(){
        vector<intT> NodeCnt;
        for(int i = 0; i < cc_nums; i++){
            NodeCnt.emplace_back(0);
        }
        for(int i = 0; i < G_p->getNumsV(); i++){
            NodeCnt[cc_ids[i]]++;
        }

        return NodeCnt;
    } 

    /*生成子图*/
    void GetSubGraph(COM_Graph &subgraph, COM_Graph graph, int cc_id, int node_cnt){
        int p = 0;
        vector<int> node_id;
        while(node_cnt > 0){
            if(cc_ids[p] == cc_id){
                node_cnt--;
                node_id.emplace_back(p);
                GiveccID(graph, p);
            }            
            p++;
        }
        subgraph = graph.get_subgraph(node_id);
    }

    void GiveccID(COM_Graph &graph, int node_index){
        graph.give_cc_id(node_index, cc_ids[node_index]);
    }

private:
    // static
    COM_Graph* G_p{ nullptr };
    // component res
    intT cc_nums{0};
    intT* cc_ids{ nullptr };
    // worker
};