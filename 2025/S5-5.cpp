#include <iostream>
#include <vector>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count; // Number of connected components

public:
    UnionFind(int n) {
        count = n;
        parent.resize(n + 1); // +1 because villages are numbered from 1 to N
        rank.resize(n + 1, 0);
        
        // Initialize each village as its own component
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Find root of the set containing x (with path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return; // Already in the same set
        }
        
        // Union by rank optimization
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        count--; // Decrease the number of components
    }

    // Get number of connected components
    int getCount() const {
        return count;
    }
};

int main() {
    int N, M, K;
    std::cin >> N >> M >> K;
    
    // Initialize Union-Find data structure
    UnionFind uf(N);
    
    // Process existing roads
    for (int i = 0; i < M; i++) {
        int A, B;
        std::cin >> A >> B;
        uf.unite(A, B);
    }
    
    // Get the initial number of connected components (village groups)
    int initialGroups = uf.getCount();
    
    // Calculate the minimum possible number of groups after building K new roads
    // Each new road can reduce the number of groups by at most 1
    int minGroups = initialGroups - K;
    
    // We cannot have fewer than 1 group
    if (minGroups < 1) {
        minGroups = 1;
    }
    
    std::cout << minGroups << std::endl;
    
    return 0;
}
