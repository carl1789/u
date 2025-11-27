#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <functional> // For std::function

/**
 * @brief Finds the vertex with the minimum distance value, from the set of
 * vertices not yet included in the shortest path tree.
 * @param dist The vector storing the shortest distance from the source to each vertex.
 * @param sptSet The boolean vector to mark vertices included in the shortest path tree.
 * @param V The total number of vertices.
 * @return The index of the vertex with the minimum distance.
 */
int minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet, int V) {
    // Initialize min value and its index
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief Prints the constructed distance array and the paths.
 * @param dist The vector storing the shortest distance from the source.
 * @param parent The vector to store the shortest path tree.
 * @param src The source vertex.
 * @param V The total number of vertices.
 */
void printSolution(const std::vector<int>& dist, const std::vector<int>& parent, int src, int V) {
    std::cout << "\n--------------------------------------------------------" << std::endl;
    std::cout << "Shortest Paths from Source Router " << src << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Router\t\tDistance\tPath" << std::endl;

    for (int i = 0; i < V; i++) {
        if (i == src) continue; // Don't print the path to the source itself

        // Handle unreachable nodes
        if (dist[i] == INT_MAX) {
            std::cout << src << " -> " << i << "\t\t" << "INF" << "\t\t" << "No Path" << std::endl;
            continue;
        }

        std::cout << src << " -> " << i << "\t\t" << dist[i] << "\t\t" << src;
        
        // Lambda function to recursively print the path from source to j
        std::function<void(int)> printPath = 
            [&](int j) {
            // Base case: If j is the source or there's no path
            if (parent[j] == -1) {
                return;
            }
            printPath(parent[j]);
            std::cout << " -> " << j;
        };
        
        printPath(i);
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
}

/**
 * @brief Implements Dijkstra's single source shortest path algorithm.
 * @param graph The adjacency matrix representation of the network graph.
 * @param src The source vertex (the starting router).
 * @param V The total number of vertices.
 */
void dijkstra(const std::vector<std::vector<int>>& graph, int src, int V) {
    // dist[i] will hold the shortest distance from src to i
    std::vector<int> dist(V);

    // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    std::vector<bool> sptSet(V);

    // parent[i] will store the predecessor of vertex i in the shortest path
    std::vector<int> parent(V);

    // Initialize all distances as INFINITE, sptSet as false, and parent as -1
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, sptSet, V);

        // If no vertex can be reached, stop.
        if (u == -1) break;

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it's not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array and paths
    printSolution(dist, parent, src, V);
}

/**
 * @brief The main function to drive the program.
 */
int main() {
    int V; // Number of vertices (routers)

    std::cout << "========================================================" << std::endl;
    std::cout << "  OSPF (Dijkstra's) Shortest Path Simulator" << std::endl;
    std::cout << "========================================================" << std::endl;
    
    std::cout << "\nEnter the total number of routers in the network: ";
    std::cin >> V;

    if (V <= 0) {
        std::cerr << "Error: Number of routers must be positive." << std::endl;
        return 1;
    }

    // Adjacency matrix to store the network graph
    std::vector<std::vector<int>> graph(V, std::vector<int>(V));

    std::cout << "\nEnter the cost matrix for the network." << std::endl;
    std::cout << "(Enter 0 if there is no direct link between two routers)" << std::endl;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            std::cout << "Enter cost from router " << i << " to router " << j << ": ";
            std::cin >> graph[i][j];
        }
    }

    int source_router;
    std::cout << "\nAvailable routers are 0 through " << V - 1 << "." << std::endl;
    std::cout << "Please enter the source router: ";
    std::cin >> source_router;

    // Validate user input
    if (source_router < 0 || source_router >= V) {
        std::cerr << "Error: Invalid source router. Please enter a value between 0 and " << V - 1 << "." << std::endl;
        return 1; // Exit with an error code
    }

    // Run Dijkstra's algorithm from the specified source router
    dijkstra(graph, source_router, V);

    return 0;
}
