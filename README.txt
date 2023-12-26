A program that is capable of identifying a minimum spanning tree of an undirected, weighted graph using Kruskal’s algorithm.

The program takes as a command line argument the name of a file that contains the specification for an undirected, weighted graph, G. The file will have the following format:
The first line will be an integer, N, that represents the number of nodes in the graph.
The next N lines will represent the rows of the adjacency matrix, with each line consisting of N weights, represented as doubles.
The last line in the file will consist of the string “END.”

The program will display the cost of the MST (the sum of all the edges in the MST) to standard output and the adjacency matrix representation of the MST (an NxN matrix where all edges are 0 except for the edges that make up the MST) to standard output.

