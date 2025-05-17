#include <iostream>
#include <vector>
using namespace std;

// Disjoint‐set (Union–Find) with union by rank ⇒ O(log n) per op
class UnionFind {
private:
    vector<int> parent, rank;
public:
    // initialize n elements: 0..n-1
    UnionFind(int n): parent(n), rank(n,0) {
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // find root of x (no path compression)
    int find(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    // union sets containing x and y
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;

        // attach smaller‐rank tree under larger‐rank root
        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[ry] < rank[rx]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;  // increase rank if same
        }
    }

    // check if x and y are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int n = 10;
    UnionFind uf(n);

    // sample unions
    uf.unite(1, 2);
    uf.unite(3, 4);
    uf.unite(2, 4);  // merges {1,2} with {3,4}

    // queries
    for (int i = 1; i <= 4; ++i) {
        cout << "root(" << i << ") = " << uf.find(i) << "\n";
    }
    cout << "1 and 3 connected? "
         << (uf.connected(1,3) ? "yes\n" : "no\n");
    cout << "5 and 6 connected? "
         << (uf.connected(5,6) ? "yes\n" : "no\n");
    return 0;
}