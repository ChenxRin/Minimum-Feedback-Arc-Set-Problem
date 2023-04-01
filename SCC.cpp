#include "SCC.hpp"
#include "Graph.h"

Graph get_data() {
    Graph graph(7);
    int x[] = {0, 1, 2, 3, 3, 4, 5, 6};
    int y[] = {1, 2, 3, 1, 0, 5, 6, 4};
    for(int i=0; i<8; i++)
        graph.insert_node(x[i], y[i], 1, i);
    return graph;
}

int main(int argc, char* argv[]){
    Graph test_graph = get_data();
    test_graph.show_graph();
    SCCEngine<Graph> scc_worker(&test_graph);
    scc_worker.findSCC();
    scc_worker.printSCC();
}