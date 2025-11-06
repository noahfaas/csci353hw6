#include <iostream>
#include <string>

#include "adjacency_matrix.h"
#include "ford_fulkerson.h"

using namespace std;

void test_adjacency_matrix(string filename, int numNodes, bool print_progress){
	// Takes a file name and a number of nodes, and prints the adjacency matrix for the graph

	cout << "Processing " << filename << ":\n";
	AdjacencyMatrix mat(filename, numNodes, print_progress);
	cout << "Adjacency Matrix:\n";
	mat.printMatrix();
	cout << endl;
}

void test_find_path(string filename, int numNodes, int source, int sink, bool print_progress){
	// Takes a file name, number of nodes, source, sink, as well as a boolean to control whether the function
	// prints its progress.
	// Uses the find_path function to find a path with available capacity.

	cout << "Processing " << filename << ":\n";
	AdjacencyMatrix mat(filename, numNodes);

	// call find_path
	int* path = find_path(&mat, numNodes, source, sink, print_progress);

	// print the path found
	cout << "Path is: ";
	if (path == NULL)
		cout << "NULL (there is no path with available capacity)";
	else{
		int i = 0;
		while (path[i] != sink){
			cout << path[i] << " ";
			i++;
		}
		cout << sink;
	}
	cout << endl << endl;	
}

void test_find_new_flow(string filename, int numNodes, int source, int sink, bool print_progress){
	// Takes a file name, number of nodes, source, sink, as well as a boolean to control whether the function
	// prints its progress.
	// Uses the find_path function to find a path with available capacity, then calls the function find_new_flow
	// to find the available capacity along the path.

	cout << "Processing " << filename << ":\n";
	AdjacencyMatrix mat(filename, numNodes);

	// print the path
	int* path = find_path(&mat, numNodes, source, sink);
	cout << "Path is: ";
	if (path == NULL)
		cout << "NULL";
	else{
		int i = 0;
		while (path[i] != sink){
			cout << path[i] << " ";
			i++;
		}
		cout << sink;
	}
	cout << endl;

	// call find_new_flow, print the flow returned.
	int new_flow = find_new_flow(path, &mat, numNodes, source, sink, print_progress);
	cout << "New flow is " << new_flow << endl << endl;	
}

void test_ff(string filename, int numNodes, int source, int sink, bool print_progress){
	// Takes a file name, number of nodes, source, sink, as well as a boolean to control whether the function
	// prints its progress.
	// Uses the function ford_fulkerson to find the maximum flow through a flow network with capacity given by
	// the graph from the file.

	// create capacity graph from file
	AdjacencyMatrix capacity(filename, numNodes);

	// call ford_fulkerson and print the max flow returned
	cout << "Ford-Fulkerson on " << filename << ":\n";
	int max_flow = ford_fulkerson(&capacity, numNodes, source, sink, print_progress);
	cout << "Max flow is " << max_flow << endl << endl;		
}


int main(){
	// call test functions to test your implementations as you work
	// each test function has an optional boolean parameter that controls whether the function being tested will
	// print some notes on its progress. To use this for debugging, change the last argument in the function
	// call to true instead of false.

	// the adjacency matrix representation is implemented for you, so this should work right away.
	cout << "**TESTING ADJACENCY MATRIX**\n\n";				
	test_adjacency_matrix("test1.csv", 5, false);
	test_adjacency_matrix("test2.csv", 5, false);
	test_adjacency_matrix("test3.csv", 6, false);
	test_adjacency_matrix("test4.csv", 7, false);
	test_adjacency_matrix("test5.csv", 8, false);
	cout << "** FINISHED TESTING ADJACENCY MATRIX **\n\n";

	cout << "**TESTING FIND_PATH**\n\n";			
	test_find_path("test1.csv", 5, 0, 1, false);
	test_find_path("test2.csv", 5, 0, 1, false);
	test_find_path("test3.csv", 6, 0, 3, false);
	test_find_path("test4.csv", 7, 1, 0, false);
	test_find_path("test5.csv", 8, 7, 0, false);
	cout << "** FINISHED TESTING FIND_PATH **\n\n";

	cout << "**TESTING FIND_NEW_FLOW**\n\n";			
	test_find_new_flow("test1.csv", 5, 0, 1, false);
	test_find_new_flow("test2.csv", 5, 0, 1, false);
	test_find_new_flow("test3.csv", 6, 0, 3, false);
	test_find_new_flow("test4.csv", 7, 1, 0, false);
	test_find_new_flow("test5.csv", 8, 7, 0, false);
	cout << "** FINISHED TESTING FIND_NEW_FLOW **\n\n";

	cout << "**TESTING FORD-FULKERSON**\n\n";			
	test_ff("test1.csv", 5, 0, 1, false);
	test_ff("test2.csv", 5, 0, 1, false);
	test_ff("test3.csv", 6, 0, 3, false);
	test_ff("test4.csv", 7, 1, 0, false);
	test_ff("test5.csv", 8, 7, 0, false);
	cout << "** FINISHED TESTING FORD-FULKERSON **\n\n";

}