// a. Alexandra Fomina
// b. 2429114
// c. fomina@chapman.edu
// d. CPSC350-01
// e. Programming Assingment 6
#include <fstream>
#include <sstream>
#include "WGraph.h"
int main(int argc, char** argv)
{
    WGraph* graph;
    ifstream inputFile(argv[1]);
    if(inputFile.is_open())
    {
        int numNodes;
        inputFile >> numNodes;
        //cout << "Num nodes is " << numNodes << endl;
        graph = new WGraph(numNodes);

        //reading the adjacency matrix
        for (int i = 0; i < numNodes; ++i)
        {
            for (int j = 0; j < numNodes; ++j)
            {
                double weight;
                inputFile >> weight;
                graph->addEdge(i, j, weight);
            }
        }
        string end;
        inputFile >> end;
    }
    inputFile.close();
    graph->computeMST();
}
