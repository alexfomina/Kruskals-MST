///a. Alexandra Fomina
// b. 2429114
// c. fomina@chapman.edu
// d. CPSC350-01
// e. Programming Assingment 6

#ifndef WGraph_H
#define WGraph_H
#include "PQueue.h"
#include <iostream>
#include <limits>

//a weighted, undirected WGraph implemented with adjacency matrix
//fixed size
typedef unsigned int VertexID;
class WGraph{
    public:
        WGraph();
        WGraph(unsigned int sz);
        ~WGraph();
        void addEdge(VertexID i, VertexID j, double w);
        void removeEdge(VertexID i, VertexID j);
        bool areAdjacent(VertexID i, VertexID j);
        double cheapestCost(VertexID i, VertexID j);
        void calcFW();
        void computeMST();
        bool edgeExists(VertexID i, VertexID j);
    private:
        double** m_adj; //is there an edge between two vertices and what's the weight of
        //the edge
        double** m_conn; //more general, is there a path between a start and a finish and
        /////what's the cost (all parts summed)
        double** m_mst; //adjacency matrix representation of MST
        unsigned int m_size; //nodes in WGraph (fixed)
        struct Edge {
            int start;
            int end;
            double weight;
            Edge(int s, int d, double w) : start(s), end(d), weight(w) {}
            double getWeight(){ return weight;}
            static bool compareEdges(const Edge& edge1, const Edge& edge2) {
            return edge1.weight > edge2.weight; // Use '>' instead of '<' for a min queue
            }
        };
        PQueue<Edge*>* edgeList;

};
#endif