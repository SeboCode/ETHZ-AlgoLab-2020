#include <iostream>
#include <vector>
#include <deque>

typedef std::vector<std::vector<std::pair<int, int>>> graph_type;

std::vector<std::vector<int>> computeAccessibility(graph_type graph) {
    std::vector<std::vector<int>> accessibility{};
    std::vector<bool> visited(graph.size(), false);
    std::deque<std::pair<int, int>> queue{};
    queue.push_back({ 0, 0 });
    
    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop_front();
        
        if (visited[current.first]) {
            continue;
        }
        
        visited[current.first] = true;
        
        if (current.second == accessibility.size()) {
            accessibility.push_back(std::vector<int>{});
        }
        
        accessibility[current.second].push_back(current.first);
        
        for (std::pair<int, int> neighbour : graph[current.first]) {
            if (!visited[neighbour.first]) {
                queue.push_back({ neighbour.first, current.second + 1 });
            }
        }
    }
    
    return accessibility;
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    long x; std::cin >> x;
    int k; std::cin >> k;
    graph_type completeGraph(n, std::vector<std::pair<int, int>>{});
    
    for (int i = 0; i < m; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        int p; std::cin >> p;
        completeGraph[u].push_back({ v, p });
    }
    
    std::vector<int> sittingSuns{};
    
    for (int i = 0; i < n; i++) {
        if (completeGraph[i].empty()) {
            sittingSuns.push_back(i);
        }
    }
    
    std::vector<std::vector<int>> accessibility = computeAccessibility(completeGraph);
    std::vector<long> lastSteps(n, 0);
    std::vector<long> currentSteps(n, 0);
    graph_type graph(n, std::vector<std::pair<int, int>>{});
    
    for (int i = 0; i < k; i++) {
        if (i < accessibility.size()) {
            for (int accessibleVertex : accessibility[i]) {
                graph[accessibleVertex] = completeGraph[accessibleVertex];
            }
        }
        
        for (int j = 0; j < n; j++) {
            for (std::pair<int, int> edge : graph[j]) {
                currentSteps[edge.first] = std::max(currentSteps[edge.first], edge.second + lastSteps[j]);
            }
        }
        
        for (int sittingSun : sittingSuns) {
            currentSteps[0] = std::max(currentSteps[0], currentSteps[sittingSun]);
        }
        
        for (int j = 0; j < n; j++) {
            if (currentSteps[j] >= x) {
                std::cout << i + 1 << std::endl;
                return;
            }
        }
        
        lastSteps = currentSteps;
        currentSteps = std::vector<long>(n, 0);
    }
    
    std::cout << "Impossible" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
