#include <iostream>
#include <vector>
#include <set>
#include <iterator>

typedef std::vector<std::vector<int>> undirected_graph;

undirected_graph graph{};
std::vector<int> dfsValues;
std::vector<int> lowValues;
std::set<std::pair<int, int>> criticalBridges;
int dfsNumber;

void dfs(int v, int pred) {
    dfsValues[v] = dfsNumber;
    lowValues[v] = dfsNumber;
    dfsNumber++;
    
    for (int u : graph[v]) {
        if (u == pred) {
            continue;
        }
        
        if (dfsValues[u] == -1) {
            dfs(u, v);
            lowValues[v] = std::min(lowValues[v], lowValues[u]);
        } else {
            lowValues[v] = std::min(lowValues[v], dfsValues[u]);
        }
        
        if (dfsValues[v] < lowValues[u]) {
            if (u < v) {
                criticalBridges.insert({u, v});
            } else {
                criticalBridges.insert({v, u});
            }
        }
    }
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    graph = undirected_graph(n, std::vector<int>{});
    
    for (int i = 0; i < m; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    dfsValues = std::vector<int>(n, -1);
    lowValues = std::vector<int>(n, -1);
    criticalBridges = std::set<std::pair<int, int>>{};
    dfsNumber = 0;
    
    for (int i = 0; i < n; i++) {
        if (dfsValues[i] == -1) {
            dfs(i, -1);
        }
    }
    
    std::cout << criticalBridges.size() << '\n';
    
    for (auto criticalBridge : criticalBridges) {
        std::cout << criticalBridge.first << ' ' << criticalBridge.second << '\n';
    }
    
    std::cout << std::flush;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
