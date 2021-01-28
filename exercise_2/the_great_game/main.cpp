#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::vector<int>> dp_type;

int solve(dp_type &dp, std::vector<std::vector<int>> const &transitions, int currentPosition, int boundIndex) {
    if (dp[boundIndex][currentPosition] != -1) {
        return dp[boundIndex][currentPosition];
    }
    
    int endResult = 0;
    
    for (int position : transitions[currentPosition]) {
        int currentResult = solve(dp, transitions, position, (boundIndex + 1) % 2) + 1;
    
        if (endResult == 0) {
            endResult = currentResult;
        } else {
            endResult = boundIndex == 0 ? std::min(endResult, currentResult) : std::max(endResult, currentResult);
        }
    }
    
    dp[boundIndex][currentPosition] = endResult;
    return dp[boundIndex][currentPosition];
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int r; std::cin >> r; r--;
    int b; std::cin >> b; b--;
    std::vector<std::vector<int>> transitions(n, std::vector<int>{});
    
    for (int i = 0; i < m; i++) {
        int u; std::cin >> u; u--;
        int v; std::cin >> v; v--;
        transitions[u].push_back(v);
    }
    
    dp_type dp(2, std::vector<int>(n, -1));
    int redSteps = solve(dp, transitions, r, 0);
    int blackSteps = solve(dp, transitions, b, 0);
    
    if (redSteps < blackSteps) {
        std::cout << 0 << std::endl;
    } else if (redSteps > blackSteps) {
        std::cout << 1 << std::endl;
    } else {
        if (redSteps % 2 == 1) {
            std::cout << 0 << std::endl;
        } else {
            std::cout << 1 << std::endl;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
