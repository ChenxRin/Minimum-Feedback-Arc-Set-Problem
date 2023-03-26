//----------------------------------------------------------------
// SCC: find Strongly Connected Components
//----------------------------------------------------------------

// created: 2023.3 by zlp

// update: (1)Tarjan's algorithm
//         (2)

#include "RP_IOTools.hpp"
#include "ligra.h"

struct BFS_F {
  uintE* Parents;
  BFS_F(uintE* _Parents) : Parents(_Parents) {}
  //在edgeMap中为(ngh, v_id)
  inline bool update (uintE s, uintE d) { //Update，更新边 <s,d>
    if(Parents[d] == UINT_E_MAX) { Parents[d] = s; return 1; }
    else return 0;
  }
  inline bool updateAtomic (uintE s, uintE d){ //atomic version of Update
    return (CAS(&Parents[d],UINT_E_MAX,s));
  }
  //cond function checks if vertex has been visited yet
  //如果需要被应用到<s,d>，返回1，否则返回0
  inline bool cond (uintE d) { return (Parents[d] == UINT_E_MAX); } 
};

template <class vertex>
void Compute(graph<vertex>& GA, commandLine P) {
  timer t_all;  
  long start = P.getOptionLongValue("-r",0);
  long n = GA.n;
  //creates Parents array, initialized to all -1, except for start
  uintE* Parents = newA(uintE,n);
  parallel_for(long i=0;i<n;i++) Parents[i] = UINT_E_MAX;
  Parents[start] = start;
  vertexSubset Frontier(n,start); //creates initial frontier, 起始点为start
  long last_nz_size=0;
  while(!Frontier.isEmpty()){ //loop until frontier is empty
    vertexSubset output = edgeMap(GA, Frontier, BFS_F(Parents));
    last_nz_size = (Frontier.size()!=0)?Frontier.size():last_nz_size;    
    Frontier.del();
    Frontier = output; //set new frontier
  }
  RP_GraphPrinter::PrintGraph(GA, RP_GraphPrinter::GRAPH_PRNIT_OUT_EDGES, "test print");
  printf("<BFS>[checking message]: last Frontier size: %ld\n", last_nz_size);
  Frontier.del();
  free(Parents); 
}