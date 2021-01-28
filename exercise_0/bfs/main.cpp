#include <iostream>
#include <vector>
#include <map>
#include <queue>

std::vector<std::vector<int>> edges;
std::map<int, int> distances;

void bfs(int first) {
    std::queue<std::pair<int, int>> queue{};
    queue.push({first, 0});
    std::vector<bool> visited(edges.size(), false);
    visited[first] = true;
    
    while (!queue.empty()) {
        auto pair = queue.front();
        queue.pop();
        int key = pair.first;
        int distance = pair.second;
        
        if (distances[key] == -1 || distance < distances[key]) {
            distances[key] = distance;
        }
        
        for (int u : edges[key]) {
            if (!visited[u]) {
                visited[u] = true;
                queue.push({u, distance + 1});
            }
        }
    }
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int v; std::cin >> v;
    edges = std::vector<std::vector<int>>(n, std::vector<int>{});
    
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    distances = std::map<int, int>{};
    
    for (int i = 0; i < n; i++) {
        distances[i] = -1;
    }
    
    bfs(v);
    
    for (auto it = distances.cbegin(); it != distances.cend(); it++) {
        std::cout << it->second << " ";
    }
    
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
