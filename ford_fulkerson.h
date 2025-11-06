#ifndef FORD_FULKERSON
#define FORD_FULKERSON

#include <stack>

int* find_path(const AdjacencyMatrix* residual_capacity, int numNodes, int source, int sink, bool print_progress=false){
    // Use depth first search on the residual capacity matrix to find a path with available capacity

    // delete the following two lines when you are ready to start implementing this function
    std::cout << "find_path not implemented" << std::endl;
    return NULL;

    // track which nodes have been visited using an array of booleans
    bool* visited = new bool[numNodes];

    // initialize all entries to false
    for (int i = 0; i < numNodes; i++){
        visited[i] = false;
    }

    // track which node was visited before each node, this will allow us to reconstruct the path
    int* prev = new int[numNodes];

    // to_visit tracks nodes that need to be explored, stored in a stack
    std::stack<int> to_visit;

    // add source to to_visit
    to_visit.push(source);

    //declare current, node, and edge_weight (will be used later)
    int current, node, edge_weight;

    // the following loop repeats until we reach the sink or path is empty
    // if we reach the sink, we've found a path with available capacity
    // if path is empty, we've completed the search without finding a path
    while (!to_visit.empty()){
        // TO DO: remove a node from to_visit (which is a stack), store to current
        // YOUR CODE HERE

        if (!visited[current]){
            // TO DO: mark current as visited
            // YOUR CODE HERE

            for (node = 0; node < numNodes; node++){        // iterate through the current column of residual matrix, to find all neighbors
                // TO DO: get the weight of the edge from current to node in the adjacency matrix &residual_capacity
                edge_weight = 0;    // YOUR CODE HERE - EDIT THIS LINE

                if (edge_weight != 0 && !visited[node]){            // if we find a neighbor that hasn't been visited
                    
                    // print a report on the edge we're considering
                    if (print_progress){
                        std::cout << "Trying edge (" << current << "," << node << ") with weight " << edge_weight << std::endl;
                    }

                    // TO DO: add the neighbor to to_visit, set prev[node] to be current (prev will be used to reconstruct the path)
                    // YOUR CODE HERE
                    

                    // if we found the sink, we've found a path, and we're done
                    if (node == sink){
                        break;                      
                    }
                }
            }
            // if we found the sink, we've found a path, and we're done
            if (node == sink){
                break;                      
            }
        }
    }

    int* path = NULL;

    // if we found a path, reconstruct it into an array of consecutive nodes
    if (node == sink){
        // going backwards from sink to source, push nodes along the path onto a stack          
        std::stack<int> path_nodes;
        int current = sink;
        int prev_node;
        while (current != source){
            path_nodes.push(current);
            current = prev[current];
        }
        path_nodes.push(source);

        // the size of the stack is the number of nodes along the path
        path = new int[path_nodes.size()];

        // remove nodes from the stack, place them in the path array (so they are in order from source to sink)
        int i = 0;
        while (!path_nodes.empty()){
            current = path_nodes.top();
            path_nodes.pop();
            path[i] = current;
            i++;
        }
    }

    // delete dynamically allocated arrays that we no longer need
    delete[] visited;
    delete[] prev;

    return path;    
}

int find_new_flow(const int* path, const AdjacencyMatrix* residual_capacity, int numNodes, int source, int sink, bool print_progress=false){
    // find and return the minimum available capacity of edges along the path

    // delete the following two lines when you are ready to start implementing this function
    std::cout << "find_new_flow not implemented" << std::endl;
    return 0;

    // if path is NULL (so, a call to find_path did not successfully find a path)
    if (path == NULL)
        return 0;

    // starting at the source node, we'll iterate through the edges along the path, keeping track of the smallest weight we've seen 
    // (so, the smallest residual capacity on one of these edges)
    int i = 0;      // index used to iterate through path nodes
    int current_node = path[i];     // start at path[0], which is the source
    int new_flow = INT_MAX;         // will track the smallest residual capacity we've seen
    int next_node, edge_weight;     // will hold the next node on the path, and the weight of the edge from current_node to next_node in residual capacity.

    // repeat until we reach the sink (end of path)
    while (current_node != sink){
        // TO DO: update next_node to be the next node along the path (note that current_node is path[i]). Get the weight of the edge from current_node to next_node.
        next_node = 0;      // YOUR CODE HERE - EDIT THIS LINE
        edge_weight = 0;    // YOUR CODE HERE - EDIT THIS LINE
        
        // report the weight of the edge
        if (print_progress){
            std::cout << "Edge (" << current_node << "," << next_node << ") has weight " << edge_weight << std::endl;
        }

        // TO DO: if the edge_weight is less than new_flow, update new_flow
        // YOUR CODE HERE

        // go to the next node along the path
        i++;
        current_node = path[i];
    }

    return new_flow;
}


int ford_fulkerson(const AdjacencyMatrix* capacity, int numNodes, int source, int sink, bool print_progress=false){
    // find and return the maximum flow that can go through a flow network with capacity (argument), from source to sink

    // delete the following two lines when you are ready to start implementing this function
    std::cout << "ford_fulkerson not implemented" << std::endl;
    return 0;

    // initialize flow matrix with 0 flow on all edges
    AdjacencyMatrix flow(numNodes);

    // print the flow matrix
    if (print_progress){
        std::cout << "Capacity matrix:\n"; 
        capacity->printMatrix();
        std::cout << std::endl;

        std::cout << "Flow matrix:\n"; 
        flow.printMatrix();
        std::cout << std::endl;
    }

    // initialize max flow as 0
    int max_flow = 0;

    // initialize residual capacity matrix as a copy of the capacity matrix
    AdjacencyMatrix residual_capacity(capacity);

    // print the residual capacity matrix
    if (print_progress){
        std::cout << "Residual capacity matrix:\n"; 
        residual_capacity.printMatrix();
        std::cout << std::endl;
    }

    // TO DO: call the function find_path to find a path from source to sink with available capacity 
    int* next_path = NULL;      // YOUR CODE HERE - EDIT THIS LINE

    // declare variables we'll use in the loop
    int new_flow, current_node, next_node, edge_weight;

    // repeat while we can find a path with available capacity
    while (next_path != NULL){                          

        // TO DO: use find_new_flow to find the flow that we can push along this path
        new_flow = 0;       // YOUR CODE HERE - EDIT THIS LINE

        // TO DO: add new flow to max flow

        //update flow and residual capacity for each edge on path
        int i = 0;              // start at the source (beginning of the path)
        current_node = next_path[i];

        while (current_node != sink){       // repeat until we reach the sink
            next_node = next_path[i+1];

            // TO DO: update the flow along edge from current_node to next_node, as well as the reverse edge. You will need to use the adjacency matrix methods get_weight and set_weight.
            // YOUR CODE HERE
            



            // TO DO: update residual capacity matrix. Note that there are only two entries to update, so don't recompute the entire matrix.
            // YOUR CODE HERE
            



            // go to the next node along the path
            i++;
            current_node = next_path[i];
        }

        // report the new flow added along the path
        if (print_progress){
            std::cout << "Added new flow " << new_flow << " along path ";
            int i = 0;
            while (next_path[i] != sink){
                std::cout << next_path[i] << "->";
                i++;
            }
            std::cout << sink << std::endl;

            // print flow to check it
            std::cout << "Flow matrix:\n"; 
            flow.printMatrix();
            std::cout << std::endl;

            // print residual_capacity to check it
            std::cout << "Residual capacity matrix:\n"; 
            residual_capacity.printMatrix();
            std::cout << std::endl;
        }

        // delete dynamically allocated array for the path we just used
        delete[] path;

        // TO DO: call the function find_path to find a path from source to sink with available capacity. IMPORTANT: what matrix should you call this on? 
        next_path = NULL;       // YOUR CODE HERE - EDIT THIS LINE      
    }

    // report the capacity matrix (from the beginning), and the flow matrix that achieves the maximum flow.
    if (print_progress){
        std::cout << "Max Flow has been found.\n\n";

        std::cout << "Capacity matrix:\n"; 
        capacity->printMatrix();
        std::cout << std::endl;

        std::cout << "Flow matrix for max flow:\n"; 
        flow.printMatrix();
        std::cout << std::endl;
    }

    return max_flow;
}

#endif