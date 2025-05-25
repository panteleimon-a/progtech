#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

class City;

class Road {
public:
    City* destination;
    int length;
    
    Road(City* dest, int len) : destination(dest), length(len) {}
};

class City {
public:
    int id;
    vector<Road*> roads;
    
    City(int cityId) : id(cityId) {}
    
    ~City() {
        for (Road* road : roads) {
            delete road;
        }
    }
    
    void addRoad(City* destination, int length) {
        roads.push_back(new Road(destination, length));
    }
};

// Modified BFS to find path with minimum refills
bool findPath(const vector<City*>& cities, int A, int B, int C,
              vector<int>& resultPath, int& resultFills) {
    int n = cities.size();
    // Min paths για κάθε πόλη και καύσιμα
    vector<vector<int>> minFills(n, vector<int>(C + 1, -1)); // 0, 1, 2, ..., C

    vector<vector<tuple<int, int, bool>>> parent(n, vector<tuple<int, int, bool>>(C + 1));
    
    // Queue for BFS: {city ID, fuel}
    queue<pair<int, int>> q;
    
    // Start at city A with full tank (after initial fill)
    q.push({A, C});
    minFills[A][C] = 1; // First fill at start
    
    while (!q.empty()) {
        int cityId = q.front().first;
        int fuel = q.front().second;
        q.pop();
        
        // Current number of fills to reach this state
        int fills = minFills[cityId][fuel];
        
        // If we reached destination
        if (cityId == B) {
            // Reconstruct path
            resultPath.clear();
            vector<pair<int, int>> statePath; // {city, fuel}
            
            int currCity = cityId;
            int currFuel = fuel;
            resultFills = fills;
            
            while (true) {
                statePath.push_back({currCity, currFuel});
                
                if (currCity == A && currFuel == C) break;
                
                int prevCity = get<0>(parent[currCity][currFuel]);
                int prevFuel = get<1>(parent[currCity][currFuel]);
                bool didRefill = get<2>(parent[currCity][currFuel]);
                
                currCity = prevCity;
                currFuel = prevFuel;
            }
            
            reverse(statePath.begin(), statePath.end());
            
            // Extract just the cities for the final path
            for (auto& p : statePath) {
                resultPath.push_back(p.first);
            }
            
            return true;
        }
        
        // Try moving to neighboring cities
        City* currentCity = cities[cityId];
        for (Road* road : currentCity->roads) {
            int nextCity = road->destination->id;
            int roadLength = road->length;
            
            // Option 1: Continue with current fuel if possible
            if (roadLength <= fuel) {
                int newFuel = fuel - roadLength;
                
                if (minFills[nextCity][newFuel] == -1 || fills < minFills[nextCity][newFuel]) {
                    minFills[nextCity][newFuel] = fills;
                    parent[nextCity][newFuel] = make_tuple(cityId, fuel, false);
                    q.push({nextCity, newFuel});
                }
            }
            
            // Option 2: Refill at current city and then move
            if (roadLength <= C) {
                int newFuel = C - roadLength;
                int newFills = fills + 1;
                
                if (minFills[nextCity][newFuel] == -1 || newFills < minFills[nextCity][newFuel]) {
                    minFills[nextCity][newFuel] = newFills;
                    parent[nextCity][newFuel] = make_tuple(cityId, fuel, true);
                    q.push({nextCity, newFuel});
                }
            }
        }
    }
    
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    // Create cities
    vector<City*> cities;
    for (int i = 0; i < N; i++) {
        cities.push_back(new City(i));
    }
    
    // Add roads
    for(int i = 0; i < M; i++) {
        int U, V, L;
        cin >> U >> V >> L;
        cities[U]->addRoad(cities[V], L);
        cities[V]->addRoad(cities[U], L); // Bidirectional roads
    }
    
    int Q; // Number of queries
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int A, B, C;
        cin >> A >> B >> C; // C Fuel deposit
        
        vector<int> path;
        int fills = 0;
        
        if (findPath(cities, A, B, C, path, fills)) {
            cout << "POSSIBLE: " << fills << " fill(s)";
            // Output cities with spaces, not commas
            for (int city : path) {
                cout << ", " << city;
            }
            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    
    // Clean up memory
    for (City* city : cities) {
        delete city;
    }

    return 0;
}
/* Άλλος τρόπος για να βρούμε το μονοπάτι με τις ελάχιστες στάσεις ανεφοδιασμού
// Modified BFS to find path with minimum refills
bool findPath(const vector<vector<Road>>& graph, int A, int B, int C,
              vector<int>& resultPath, int& resultFills) {
    int n = graph.size(); // N
    // Min paths για κάθε πόλη και καύσιμα
    vector<vector<int>> minFills(n, vector<int>(C + 1, -1)); // 0, 1, 2, ..., C

    vector<vector<tuple<int, int, bool>>> parent(n, vector<tuple<int, int, bool>>(C + 1));
    
    // Queue for BFS: {city, fuel}
    queue<pair<int, int>> q;
    
    // Start at city A with full tank (after initial fill)
    q.push({A, C});
    minFills[A][C] = 1; // First fill at start
    
    while (!q.empty()) {
        int city = q.front().first;
        int fuel = q.front().second;
        q.pop();
        
        // Current number of fills to reach this state
        int fills = minFills[city][fuel];
        
        // If we reached destination
        if (city == B) {
            // Reconstruct path
            resultPath.clear();
            vector<pair<int, int>> statePath; // {city, fuel}
            
            int currCity = city;
            int currFuel = fuel;
            resultFills = fills;
            
            while (true) {
                statePath.push_back({currCity, currFuel});
                
                if (currCity == A && currFuel == C) break;
                
                int prevCity = get<0>(parent[currCity][currFuel]);
                int prevFuel = get<1>(parent[currCity][currFuel]);
                bool didRefill = get<2>(parent[currCity][currFuel]);
                
                currCity = prevCity;
                currFuel = prevFuel;
            }
            
            reverse(statePath.begin(), statePath.end());
            
            // Extract just the cities for the final path
            for (auto& p : statePath) {
                resultPath.push_back(p.first);
            }
            
            return true;
        }
        
        // Try moving to neighboring cities
        for (const Road& road : graph[city]) {
            int nextCity = road.destination;
            int roadLength = road.length;
            
            // Option 1: Continue with current fuel if possible
            if (roadLength <= fuel) {
                int newFuel = fuel - roadLength;
                
                if (minFills[nextCity][newFuel] == -1 || fills < minFills[nextCity][newFuel]) {
                    minFills[nextCity][newFuel] = fills;
                    parent[nextCity][newFuel] = make_tuple(city, fuel, false);
                    q.push({nextCity, newFuel});
                }
            }
            
            // Option 2: Refill at current city and then move
            if (roadLength <= C) {
                int newFuel = C - roadLength;
                int newFills = fills + 1;
                
                if (minFills[nextCity][newFuel] == -1 || newFills < minFills[nextCity][newFuel]) {
                    minFills[nextCity][newFuel] = newFills;
                    parent[nextCity][newFuel] = make_tuple(city, fuel, true);
                    q.push({nextCity, newFuel});
                }
            }
        }
    }
    
    return false;
}
*/

int main() {
    int N, M;
    cin >> N >> M;
    // Adj. list for road network
    vector<vector<Road>> graph(N);
    for(int i = 0; i < M; i++) {
        int U, V, L;
        cin >> U >> V >> L;
        graph[U].push_back({V, L});
        graph[V].push_back({U, L}); // Bidirectional roads
    }
    int Q; // Number of queries
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int A, B, C;
        cin >> A >> B >> C; // C Fuel deposit
        
        vector<int> path;
        int fills = 0;
        
        if (findPath(graph, A, B, C, path, fills)) {
            cout << "POSSIBLE: " << fills << " fill(s)";
            // Output cities with spaces, not commas
            for (int city : path) {
                cout << ", " << city;
            }
            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
} 