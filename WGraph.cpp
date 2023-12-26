// a. Alexandra Fomina
// b. 2429114
// c. fomina@chapman.edu
// d. CPSC350-01
// e. Programming Assingment 6

#include "WGraph.h"
#include <set>
#include <algorithm>

/// @brief Default constructor for Weighted Graph
WGraph::WGraph(){
    m_size = 0;
    m_adj = NULL;
    m_conn = NULL;
}

/// @brief Overloaded constructor to create a weight graph with sz nodes
/// @param sz 
WGraph::WGraph(unsigned int sz){
    m_size = sz;
    //allocate sz * sz adj matrix
    m_adj = new double*[sz];
    m_conn = new double*[sz];
    m_mst = new double*[sz];
    for(int i = 0; i < m_size; ++i){
        m_adj[i] = new double[sz];
        m_conn[i] = new double[sz];
        m_mst[i] = new double[sz];
    }
    //start with edges
    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j){
            m_adj[i][j] = std::numeric_limits<double>::max(); //essentially infinity
            m_conn[i][j] = std::numeric_limits<double>::max();
            m_mst[i][j] = 0; //initalize the matrix with no values
        }
    }
    edgeList = new PQueue<Edge*>(true); //set it up as a min queue
}

/// @brief Default destructor for weighted graph 
WGraph::~WGraph(){
    // Deallocate the adjacency matrix
    for (int i = 0; i < m_size; ++i) {
        delete[] m_adj[i];
        delete[] m_conn[i];
        delete[] m_mst[i];
    }
    delete[] m_adj;
    delete[] m_conn;
    delete[] m_mst;

    // Deallocate the priority queue
    delete edgeList;
}

/// @brief Adds an edge to the weighted graph given the vertices and weight
/// @param i 
/// @param j 
/// @param w 
void WGraph::addEdge(VertexID i, VertexID j, double w){
    if(i < m_size && j < m_size){
        m_adj[i][j] = w;
        m_adj[j][i] = w;
        if(i != j && w > 0) //not necessary to add edges on the diagonals
        {   Edge* myE = new Edge(i, j, w);
            edgeList->add(myE);
        }
    }
        
}

/// @brief Removes an edge from the graph given the vertices
/// @param i 
/// @param j 
void WGraph::removeEdge(VertexID i, VertexID j){
    if(i < m_size && j < m_size){
        m_adj[i][j] = std::numeric_limits<double>::max();
        m_adj[j][i] = std::numeric_limits<double>::max();
    }
}

/// @brief checks to see if two vertices are adjacent
/// @param i 
/// @param j 
/// @return 
bool WGraph::areAdjacent(VertexID i, VertexID j){
    return (m_adj[i][j] < std::numeric_limits<double>::max());
}

/// @brief Calculates FW based on the graph
void WGraph::calcFW(){ //runtime complexity O(v^3)
    for(int i = 0; i < m_size; ++i){
        for(int j = 0; j < m_size; ++j){
            m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
        }
    }   
    for(int im = 0; im < m_size; ++ im){ //intermediate points --> transitive closure
        for(int source = 0; source < m_size; ++source){ //source = starting point
            for(int sink = 0; sink <m_size; ++sink){ //sink = ending point
                if(source == sink){
                    continue;
                }
                else if(m_conn[source][im] != std::numeric_limits<double>::max() &&
                m_conn[im][sink] != std::numeric_limits<double>::max() &&
                m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink])
                {
                    m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
                }
            }
        }
    }
}
/// @brief finds the cheapest cost between 2 vertices
/// @param i 
/// @param j 
/// @return 
double WGraph::cheapestCost(VertexID i, VertexID j){
    return m_conn[i][j]; //constant
}

/// @brief Computes MST for the weighted graph
void WGraph::computeMST()
{
    double sum = 0;
    set<set<int>*> vertexSet;
    for (int i = 0; i < m_size; ++i) {
        set<int>* v = new set<int>();
        v->insert(i);
        vertexSet.insert(v);
    }
    set<Edge*> resultList;
    while (vertexSet.size() > 1 && edgeList->size() > 0) {
        Edge* nextEdge = edgeList->remove();
        //cout << "current edge weight is " << nextEdge->getWeight() << endl;
        set<int>* vSet1 = nullptr;
        set<int>* vSet2 = nullptr;
        // Find vSet1 and vSet2 in vertexSet
        for (const auto& vSet : vertexSet) {
            if (vSet->count(nextEdge->start) > 0) {
                vSet1 = vSet;
            } else if (vSet->count(nextEdge->end) > 0) {
                vSet2 = vSet;
            }
        }
        if (vSet1 != nullptr && vSet2 != nullptr && vSet1 != vSet2) {
            resultList.insert(nextEdge);
            m_mst[nextEdge->start][nextEdge->end] = nextEdge->getWeight();
            m_mst[nextEdge->end][nextEdge->start] = nextEdge->getWeight();
            sum += nextEdge->getWeight();
            // Erase vSet1 and vSet2 from vertexSet
            vertexSet.erase(vSet1);
            vertexSet.erase(vSet2);
            // Update vSet1 to include elements from vSet2
            vSet1->insert(vSet2->begin(), vSet2->end());
            // Insert the updated vSet1 back into vertexSet
            vertexSet.insert(vSet1);
        }
    }
    cout << "The total cost of the MST is: " << sum << endl;
    cout << "MST adjacency matrix: " << endl;
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            cout << m_mst[i][j] << " ";
        }
        cout << endl;
    }
}