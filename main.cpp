#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    map<int, int> parent;
    map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    void clear() {
        parent.clear();
        rank.clear();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        // Read all constraints
        vector<tuple<int, int, int>> constraints;
        constraints.reserve(n);
        
        for (int i = 0; i < n; i++) {
            int x, y, e;
            cin >> x >> y >> e;
            constraints.emplace_back(x, y, e);
        }
        
        UnionFind uf;
        
        // Process all equality constraints first
        for (const auto& [x, y, e] : constraints) {
            if (e == 1) {  // x == y
                uf.unite(x, y);
            }
        }
        
        // Check all inequality constraints
        bool valid = true;
        for (const auto& [x, y, e] : constraints) {
            if (e == 0) {  // x != y
                if (uf.connected(x, y)) {
                    valid = false;
                    break;
                }
            }
        }
        
        cout << (valid ? "YES" : "NO") << '\n';
        
        uf.clear();
    }
    
    return 0;
}