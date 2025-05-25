#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
class Graph {
    private:
        int V;  // number of vertices
        std::unordered_map<int, std::unordered_set<int>> adj;
    public:
        Graph(int V) {
            if (V < 0) {
                std::cerr << "Error: Number of vertices cannot be negative." << std::endl;
                exit(EXIT_FAILURE);
            }
            this->V = V;
            for (int i = 0; i < V; ++i) {
                adj[i] = std::unordered_set<int>();
            }
        } // constructor

        void addEdge(int u, int v) {
            if (u >= 0 && u < V && v >= 0 && v < V) { // bounds checking
                    if (!isAdjacent(u, v)) {
                        adj[u].insert(v); // directed graph
                    }
                } else {
                    std::cerr << "Error: Vertex out of bounds." << std::endl;
                }
            }

        bool isAdjacent(int v, int vis) const {
            if (v < 0 || v >= V || vis < 0 || vis >= V) {
                std::cerr << "Error: Vertex out of bounds." << std::endl;
                return false;
            }
            auto it = adj.find(v);
            if (it == adj.end()) {
                std::cerr << "Error: Vertex " << v << " not found in adjacency list." << std::endl;
                return false;
            }
            return it->second.find(vis) != it->second.end();
        }
        
        bool hasCycleUtil(int v, std::vector<bool>& visited, std::vector<bool>& recursionStack, std::vector<int>& path) const {
            visited[v] = true; // Mark the current node as visited
            recursionStack[v] = true; // Add the current node to the recursion stack
            path.push_back(v); // Add the current node to the path

            for (int neighbor : adj.at(v)) {
                if (!visited[neighbor]) {
                    if (hasCycleUtil(neighbor, visited, recursionStack, path))
                        return true;
                } else if (recursionStack[neighbor]) { // Back edge found: cycle detected
                    // Cycle is from neighbor back to current node
                    // Find the start of the cycle in the current path
                    auto it = std::find(path.begin(), path.end(), neighbor);
                    if (it != path.end()) {
                        path.erase(path.begin(), it); // Keep only the cycle part
                    }
                    return true;
                }
            }
            recursionStack[v] = false; // Remove the current node from the recursion stack
            path.pop_back(); // Backtrack: remove the current node from the path
            return false;
        }

        bool cycle(std::vector<int>& path) const {
            std::vector<bool> visited(V, false);
            std::vector<int> parent(V, -1); // To reconstruct the cycle
            for (int i = 0; i < V; ++i) {
                if (!visited[i]) {
                    std::vector<bool> recursionStack(V, false);
                    if (hasCycleUtil(i, visited, recursionStack, path))
                    return true;
                }
            }
            return false;
        }
};
/*
 
int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u >= 0 && u < n && v >= 0 && v < n) {
            g.addEdge(u, v);
        } else {
            std::cerr << "Error: Edge (" << u << ", " << v << ") is out of bounds." << std::endl;
        }
    }
    std::vector<int> path;
    bool c = g.cycle(path);
    if (c) {
        std::cout << "CYCLE" << std::endl;
        for (int i =0 ; i < path.size() ; ++i) {
            std::cout << path[i] <<  (i == path.size()-1 ? "\n" : " ");
        }
    } else {
        std::cout << "NO CYCLE" << std::endl;
    }
}
 */