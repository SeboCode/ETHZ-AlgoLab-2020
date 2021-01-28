#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::pair<int, int>>> graph_type;
typedef std::vector<std::vector<long>> dp_type;

long solve(dp_type & dp, graph_type const & graph, int movesLeft, int position) {
    if (movesLeft == 0) {
        return 0;
    }
    
    if (graph[position].size() == 0) {
        return solve(dp, graph, movesLeft, 0);
    }
    
    if (dp[movesLeft][position] != -1) {
        return dp[movesLeft][position];
    }
    
    for (auto neighbour : graph[position]) {
        long maxUsingEdge = solve(dp, graph, movesLeft-1, neighbour.first) + neighbour.second;
        dp[movesLeft][position] = std::max(dp[movesLeft][position], maxUsingEdge);
    }
    
    return dp[movesLeft][position];
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    long x; std::cin >> x;
    int k; std::cin >> k;
    graph_type graph(n, std::vector<std::pair<int, int>>{});
    
    for (int i = 0; i < m; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        int p; std::cin >> p;
        graph[u].push_back({v, p}); 
    }
    
    dp_type dp = dp_type(k+1, std::vector<long>(n, -1));
    
    for (int i = 1; i < k+1; i++) {
        long achivedPoints = solve(dp, graph, i, 0);
        
        if (achivedPoints >= x) {
            std::cout << i << std::endl;
            return;
        }
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
