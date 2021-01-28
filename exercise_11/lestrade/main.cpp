#include <iostream>
#include <vector>
#include <climits>

std::vector<std::vector<int>> graph;
std::vector<int> cost;
std::vector<std::vector<int>> dp;

int solve(int position, bool on, bool parent) {
    if (graph[position].empty() && parent) {
        return 0;
    }
    
    if (graph[position].empty() && !parent) {
        return cost[position];
    }
    
    int situation = on ? 0 : (parent ? 1 : 2);
    
    if (dp[position][situation] != -1) {
        return dp[position][situation];
    }
    
    if (on) {
        dp[position][situation] = cost[position];
        
        for (int dest : graph[position]) {
            dp[position][situation] += std::min(solve(dest, true, true), solve(dest, false, true));
        }
    } else if (parent) {
        dp[position][situation] = 0;
        
        for (int dest : graph[position]) {
            dp[position][situation] += std::min(solve(dest, true, false), solve(dest, false, false));
        }
    } else {
        std::vector<int> minimumAtPosition(graph[position].size());
        int totalMinimum = 0;
        
        for (int i = 0; i < graph[position].size(); i++) {
            minimumAtPosition[i] = std::min(solve(graph[position][i], true, false), solve(graph[position][i], false, false));
            totalMinimum += minimumAtPosition[i];
        }
        
        int bestOption = INT_MAX;
        
        for (int i = 0; i < graph[position].size(); i++) {
            bestOption = std::min(bestOption, totalMinimum - minimumAtPosition[i] + solve(graph[position][i], true, false));
        }
        
        dp[position][situation] = bestOption;
    }
    
    return dp[position][situation];
}

void testcase() {
    int n; std::cin >> n;
    graph = std::vector<std::vector<int>>(n, std::vector<int>{});
    
    for (int k = 0; k < n-1; k++) {
        int i; std::cin >> i;
        int j; std::cin >> j;
        graph[i].push_back(j);
    }
    
    cost = std::vector<int>(n);
    
    for (int i = 0; i < n; i++) {
        int c; std::cin >> c;
        cost[i] = c;
    }
    
    dp = std::vector<std::vector<int>>(n, std::vector<int>(3, -1));
    std::cout << std::min(solve(0, false, false), solve(0, true, false)) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
