#ifndef ADJACENCY_MATRIX
#define ADJACENCY_MATRIX

#include <iostream>
#include <fstream>
#include <string>

class AdjacencyMatrix{
	// class to represent the adjacency matrix of a weighted, directed graph
private:
	int V;					//number of nodes in the graph
	int** adjMatrix;		//adjacency matrix of a graph

public:
	AdjacencyMatrix(int numVertices){
		// Constructor: takes a number of vertices in the graph, and constructs the adjacency matrix of the graph with no edges (all entries are 0)
		// Nodes are numbered 0, 1, 2, ..., numVertices-1
		V = numVertices;

		// set up adjacency matrix, as an array of arrays. 
		// Dimensions of the matrix are numVertices by numVertices.
		// adjMatrix[i][j] will be 0 if there is no edge from j to i, and will be the weight if there is such an edge.
		// all values in matrix are initialized to 0. Edges will be filled in later.
		adjMatrix = new int*[V];	
		for (int i = 0; i < V; i++){
			adjMatrix[i] = new int[V]();
		}
	}

	AdjacencyMatrix(const AdjacencyMatrix* other){
		// Constructor: takes another adjacency matrix, and makes a clone (deep copy) of it
		// Nodes are numbered 0, 1, 2, ..., numVertices-1
		V = other->V;

		// set up adjacency matrix, as an array of arrays. 
		// Dimensions of the matrix are numVertices by numVertices.
		// adjMatrix[i][j] will be 0 if there is no edge from j to i, and will be the weight if there is such an edge.
		// all values in matrix are initialized to 0. Edges will be filled in later.
		adjMatrix = new int*[V];	
		for (int i = 0; i < V; i++){
			adjMatrix[i] = new int[V]();
		}

		// copy all entries from other.AdjMatrix into the new adjacency matrix for this graph
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++){
				adjMatrix[i][j] = other->adjMatrix[i][j];
			}
		}
	}

	AdjacencyMatrix(std::string filename, int numVertices, bool printProgress = false){
		// Constructor: takes a file name and the number of vertices in the graph, and constructs the adjacency matrix of the graph
		// Nodes are numbered 0, 1, 2, ..., numVertices-1
		// printProgress controls whether we print each edge as we add it to the graph
		V = numVertices;

		// set up adjacency matrix, as an array of arrays. 
		// Dimensions of the matrix are numVertices by numVertices.
		// adjMatrix[i][j] will be 0 if there is no edge from j to i, and will be the weight if there is such an edge.
		// all values in matrix are initialized to 0. Edges will be filled in later.
		adjMatrix = new int*[V];	
		for (int i = 0; i < V; i++){
			adjMatrix[i] = new int[V]();
		}

		// open the file with name provided. 
		//	The file is a csv file, listing the edges of the graph. For example, the file could contain:
		//	0, 2, 5
		//	1, 2, 3
		//	3, 1, 8
		//	This means that there is an edge from node 0 to node 2 with weight 5, an edge from node 1 to node 2 with weight 3,
		//	and an edge from node 3 to node 1 with weight 8. You can assume that each edge is only listed once.
		std::ifstream edgeFile;
		edgeFile.open(filename);

		// these variables will be used to store the two nodes and weight of each edge as we process the file
		std::string v1_string, v2_string, w_string;
		int v1, v2, w;

		// read from the file, and update adjacency matrix for each edge in the file
		while (std::getline(edgeFile, v1_string, ',') && std::getline(edgeFile, v2_string, ',') && std::getline(edgeFile, w_string, '\n')){
			// read nodes and weight of edge, convert to ints
			// read until the comma, store in v1_string (this is the first node)
			// read until the next comma, store in v2_string (this is the second node)
			// read until the newline, store in w_string (this is the weight of the edge)
			v1 = std::stoi(v1_string);	
			v2 = std::stoi(v2_string);
			w = std::stoi(w_string);

			// at this point, the edge is from node v1 to node v2 with weight w.

			// make sure node names are valid
			if (v1 < 0 || v1 >= V || v2 < 0 || v2 >= V){
				std::cout << "Invalid node in edge (" << v1 << "," << v2 << ")\nNumber of nodes is " << V << std::endl;
				edgeFile.close();
				return;
			}			

			// there is an edge from v1 to v2, we'll add it to the adjacency matrix
			if (printProgress){
				std::cout << "Adding edge from " << v1 << " to " << v2 << " with weight " << w << std::endl;
			}

			// update the adjacency matrix to include this edge
			adjMatrix[v2][v1] = w;
		}

		edgeFile.close();

	}

	void printMatrix() const {
		// Use this function to view your adjacency matrix, to check that it was set up correctly.
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++){				// print row
				std::cout << adjMatrix[i][j] << "\t";
			}
			std::cout << std::endl;						// print line break between row
		}
	}

	int get_weight(int i, int j) const {
		// accesses and returns entry (i,j)
		// if there is an edge from node i to node j, returns the weight. returns 0 otherwise
		// returns -1 if i or j is out of range
		if (i < 0 || j < 0 || i >= V || j >= V){
			std::cout << "Invalid node in call to get entry (" << i << "," << j << ")\nNumber of nodes is " << V << std::endl;
			return -1;
		}
		return adjMatrix[j][i];
	}

	void set_weight(int i, int j, int new_weight){
		// accesses and returns entry (i,j)
		// if there is an edge from node i to node j, returns the weight. returns 0 otherwise
		// returns -1 if i or j is out of range
		if (i < 0 || j < 0 || i >= V || j >= V){
			std::cout << "Invalid node in call to get entry (" << i << "," << j << ")\nNumber of nodes is " << V << std::endl;
			return;
		}
		adjMatrix[j][i] = new_weight;
	}

	~AdjacencyMatrix(){
		// This is the destructor. It deletes the dynamically allocated arrays, so that we don't have memory leaks.
		for (int i = 0; i < V; i++){
			delete[] adjMatrix[i];		//delete every row
		}
		delete[] adjMatrix;				//delete the array of rows
	}
};

#endif