//-----------------------------------------------------------
// RP_IOTools: Graph reading, printing and some other function
//-----------------------------------------------------------

// created: 2023.3 by zlp

// TODO: for now combine with Ligra tight, reconstruct compiling system

#pragma once

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

//------------------------------------------------
// print Graph that satisfy target interface
//------------------------------------------------
struct RP_GraphPrinter{
enum GRAPH_PRINT_ENUM{
    GRAPH_PRINT_ALL,
    GRAPH_PRINT_EDGE_LIST,
    GRAPH_PRNIT_OUT_EDGES,
    GRAPH_PRINT_IN_EDGES,
};

template<class COM_Graph>
static void PrintGraphEdges(COM_Graph &G, GRAPH_PRINT_ENUM print_mode){
    size_t nums_v = G.getNumsV();
    for(size_t i=0; i<nums_v; ++i){
        switch (print_mode)
        {
        case GRAPH_PRNIT_OUT_EDGES:{
            size_t nums_d = G[i].getOutDegree();
            cout<<"[ "<<i<<" ("<<nums_d<<") ]"<<" -> : ";
            for(size_t eo=0; eo<nums_d; ++eo){
                cout<<G[i].getOutNeighbor(eo)<<" ";
            }
            cout<<endl;
        }break;
        case GRAPH_PRINT_IN_EDGES:{
            size_t nums_d = G[i].getInDegree();
            cout<<"[ "<<i<<" ("<<nums_d<<") ]"<<" <- : ";
            for(size_t eo=0; eo<nums_d; ++eo){
                cout<<G[i].getInNeighbor(eo)<<" ";
            }
            cout<<endl;
        }break;
        case GRAPH_PRINT_ALL:
        case GRAPH_PRINT_EDGE_LIST:
        default:
            break;
        }
    }
    return;
}

template<class COM_Graph>
static void PrintGraphDegrees(COM_Graph &G){
    return;
}

template<class COM_Graph>
static void PrintGraphAll(COM_Graph &G){
    return;
}

template<class COM_Graph>
static void PrintGraph(COM_Graph &G, GRAPH_PRINT_ENUM print_mode, string name){
    cout<<"===[Graph Name:"<<name<<"]-(message printing)==="<<endl;
    cout<<"[size : (|V|:"<<G.getNumsV()<<"), (|E|:"<<G.getNumsE()<<")"<<endl;
    switch (print_mode)
    {
    case GRAPH_PRINT_ALL:{
        cout<<"------------- out edges printing: "<<endl;
        PrintGraphEdges(G, GRAPH_PRNIT_OUT_EDGES);
        cout<<"------------- in edges printing: "<<endl;
        PrintGraphEdges(G, GRAPH_PRINT_IN_EDGES);
    }break;
    case GRAPH_PRNIT_OUT_EDGES:{
        cout<<"------------- out edges printing: "<<endl;
        PrintGraphEdges(G, GRAPH_PRNIT_OUT_EDGES);
    }break;
    case GRAPH_PRINT_IN_EDGES:{
        cout<<"------------- in edges printing: "<<endl;
        PrintGraphEdges(G, GRAPH_PRINT_IN_EDGES);
    }break;
    case GRAPH_PRINT_EDGE_LIST:
    default:
        break;
    }
    return;
}

};
