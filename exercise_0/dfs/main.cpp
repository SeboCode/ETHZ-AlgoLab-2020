#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>

std::vector<std::set<int>> edges;

void dfs(int& counter, int v, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& finish) {
    visited[v] = true;
    disc[v] = counter;
    counter++;
    
    for (int u : edges[v]) {
        if (!visited[u]) {
            dfs(counter, u, visited, disc, finish);
        }
    }
    
    finish[v] = counter;
    counter++;
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int v; std::cin >> v;
    edges = std::vector<std::set<int>>(n, std::set<int>{});
    
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        edges[a].insert(b);
        edges[b].insert(a);
    }
    
    std::vector<int> disc(n, -1);
    std::vector<int> finish(n, -1);
    std::vector<bool> visited(n, false);
    int counter = 0;
    dfs(counter, v, visited, disc, finish);
    
    std::copy(disc.cbegin(), disc.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    
    std::copy(finish.cbegin(), finish.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
