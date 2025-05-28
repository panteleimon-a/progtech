#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<long long> deg(N, 0);
    vector<vector<int>> adj(N);

    // read edges, build degree array and adjacency list
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            deg[u] += 2;
            // a self‐loop doesn’t help connectivity, but we can record it once
            adj[u].push_back(u);
        } else {
            deg[u]++; deg[v]++;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    // count non-isolated vertices and pick a start
    int nonIsoCount = 0, start = -1;
    for (int i = 0; i < N; ++i) {
        if (deg[i] > 0) {
            ++nonIsoCount;
            if (start < 0) start = i;
        }
    }
    // if there are no edges at all, we’ll treat it as “CYCLE”
    if (start < 0) {
        cout << "CYCLE\n";
        return 0;
    }

    // BFS to check connectivity of the non-isolated subgraph
    vector<char> vis(N, false);
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int seen = 1;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (!vis[u] && deg[u] > 0) {
                vis[u] = true;
                q.push(u);
                ++seen;
            }
        }
    }
    if (seen != nonIsoCount) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // now do the odd-degree check
    vector<int> odd;
    for (int i = 0; i < N; ++i) {
        if (deg[i] % 2 != 0) odd.push_back(i);
    }

    if (odd.empty()) {
        cout << "CYCLE\n";
    }
    else if (odd.size() == 2) {
        int u = odd[0], v = odd[1];
        if (u > v) swap(u, v);
        cout << "PATH " << u << " " << v << "\n";
    }
    else {
        cout << "IMPOSSIBLE\n";



}    return 0;    }   