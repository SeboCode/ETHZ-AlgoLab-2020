#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::vector<int>> dp_type;

int solve(dp_type &dp, std::vector<int> const &coins, int left, int right) {
    if (left > right) {
        return 0;
    }
    
    if (left == right) {
        return coins[left];
    }
    
    if (dp[left][right] == -1) {
        int both = solve(dp, coins, left+1, right-1);
        int doubleRight = solve(dp, coins, left, right-2);
        int doubleLeft = solve(dp, coins, left+2, right);
        
        // We pick the smallest possible option, since our friend will play optimal as well
        int pickLeft = std::min(both, doubleLeft) + coins[left];
        // We pick the smallest possible option, since our friend will play optimal as well
        int pickRight = std::min(both, doubleRight) + coins[right];
        
        // We pick the best of the two options
        dp[left][right] = std::max(pickLeft, pickRight);
    }
    
    return dp[left][right];
}

void testcase() {
    int n; std::cin >> n;
    std::vector<int> coins{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(coins));
    dp_type dp(n, std::vector<int>(n, -1));
    std::cout << solve(dp, coins, 0, n-1) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
