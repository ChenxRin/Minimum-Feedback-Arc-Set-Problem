//--------------------------------------------------------------------
// PageRank Counting
//--------------------------------------------------------------------

// created: 2023.3 by zlp

#include "ligra.h"
#include "math.h"

// PageRank Counting (实际计算PageRank的回调类)
template <class vertex>
struct PR_Count_F {
    double* p_curr, *p_next;
    vertex* V;
    PR_Count_F(double* _p_curr, double* _p_next, vertex* _V) : 
    p_curr(_p_curr), p_next(_p_next), V(_V) {}
    inline bool update(uintE s, uintE d){ //update function applies PageRank equation
        p_next[d] += p_curr[s]/V[s].getOutDegree();
        return 1;
    }
    inline bool updateAtomic (uintE s, uintE d) { //atomic Update
        writeAdd(&p_next[d],p_curr[s]/V[s].getOutDegree());
        return 1;
    }
    // always true
    inline bool cond (intT d) { return cond_true(d); }
};

// vertex map (更新顶点信息)
struct PR_VertexConv_F {
    double damping;
    double addedConstant;
    double* p_curr;
    double* p_next;
    PR_VertexConv_F(double* _p_curr, double* _p_next, double _damping, intE n) :
        p_curr(_p_curr), p_next(_p_next), 
        damping(_damping), addedConstant((1-_damping)*(1/(double)n)){}
    inline bool operator () (uintE i) {
        p_next[i] = damping*p_next[i] + addedConstant;
        return 1;
    }
};

// resets p
struct PR_Vertex_Reset {
    double* p_curr;
    PR_Vertex_Reset(double* _p_curr): p_curr(_p_curr) {}
    inline bool operator () (uintE i) {
        p_curr[i] = 0.0;
        return 1;
    }
};

//-----------------------------------------------------
// actual pagerank runner
//-----------------------------------------------------
template<class vertex, class COM_Graph>
class PageRankEngine {
public:
    // default args
    const double DEFAULT_DAMPING = 1;
    const double DEFAULT_EPSILON = 0.0001;

    PageRankEngine()=default;
    PageRankEngine(COM_Graph* g_p, size_t max_it_time):G_p(g_p),max_iter_times(max_it_time){}
    ~PageRankEngine(){}     //setting no data hold
  
    void combine(COM_Graph* g_p, size_t max_time){
        G_p=g_p;  max_iter_times=max_time;
    }

    double* doPageRanking(double damping=0.0, double epsilon=0.0, double* pass_p_curr=nullptr, double* pass_p_next=nullptr){
        COM_Graph &GA = *G_p;
        intE n = GA.n;
        if(damping==0.0){damping=saved_damping;}
        if(epsilon==0.0){epsilon=saved_epsilon;}

        double one_over_n = 1/(double)n;
        double* p_curr = (pass_p_curr==nullptr)?newA(double,n):pass_p_curr;
        {parallel_for(long i=0;i<n;i++) p_curr[i] = one_over_n;}
        double* p_next = (pass_p_next==nullptr)?newA(double,n):pass_p_next;
        {parallel_for(long i=0;i<n;i++) p_next[i] = 0;} //0 if unchanged

        bool* frontier = newA(bool,n);    // dense frontier
        {parallel_for(long i=0;i<n;i++) frontier[i] = 1;}

        vertexSubset Frontier(n,n,frontier);    

        long iter = 0;
        double L1_norm = 0.0;
        while(iter++ < max_iter_times) {
        edgeMap(GA,Frontier,PR_Count_F<vertex>(p_curr,p_next,GA.V),0, no_output);
        vertexMap(Frontier,PR_VertexConv_F(p_curr,p_next,damping,n));
        //compute L1-norm between p_curr and p_next
        {parallel_for(long i=0;i<n;i++) {
            p_curr[i] = fabs(p_curr[i]-p_next[i]);
        }}
        L1_norm = sequence::plusReduce(p_curr,n);
        if(L1_norm < epsilon) break;
            //reset p_curr
            vertexMap(Frontier,PR_Vertex_Reset(p_curr));
            swap(p_curr,p_next);
        }
        printf("<PageRank>[check message]: iter nums:%ld, L1 norm:%f\n", iter, L1_norm);
        Frontier.del(); 
        if(pass_p_next==nullptr){free(p_next);} 
        return p_curr;
    }

private:
    // 绑定图结构
    COM_Graph* G_p{nullptr};
    size_t max_iter_times{0};
    // 执行PageRank的参数信息
    double saved_damping{DEFAULT_DAMPING};
    double saved_epsilon{DEFAULT_EPSILON};
};

template <class vertex>
void Compute(graph<vertex>& GA, commandLine P) {
    long maxIters = P.getOptionLongValue("-maxiters",100);

    PageRankEngine<vertex, graph<vertex>> pr_runner(&GA, maxIters);
    double* p_curr = pr_runner.doPageRanking();
    free(p_curr);
}
