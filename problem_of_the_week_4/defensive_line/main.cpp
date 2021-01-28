#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::vector<int>> dp_type;

int solve(dp_type &dp, std::vector<int> const &possiblePositions, int attackerCount, int defenderCount) {
    int m = dp.size();
    int n = dp[0].size();
    
    if (n - defenderCount < m - attackerCount) {
        return -1;
    }
    
    if (attackerCount == m) {
        return 0;
    }
    
    if (dp[attackerCount][defenderCount] == -2) {
        int takeAmount = -1;
        
        if (possiblePositions[defenderCount] != -1) {
            takeAmount = solve(dp, possiblePositions, attackerCount+1, possiblePositions[defenderCount]);
            
            if (takeAmount != -1) {
                takeAmount += possiblePositions[defenderCount] - defenderCount;
            }
        }
        
        int skipAmount = solve(dp, possiblePositions, attackerCount, defenderCount+1);
        dp[attackerCount][defenderCount] = std::max(takeAmount, skipAmount);
    }
    
    return dp[attackerCount][defenderCount];
}

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int k; std::cin >> k;
    std::vector<int> defenseValues{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(defenseValues));
    
    std::vector<int> possiblePositions(n, -1);
    int left = 0;
    int right = 0;
    int defense = 0;
    
    while (right <= n) {
        if (defense < k) {
            if (right == n) {
                break;
            }
            
            defense += defenseValues[right];
            right++;
        } else {
            if (defense == k) {
                possiblePositions[left] = right;
            }
            
            defense -= defenseValues[left];
            left++;
        }
    }
    
    dp_type dp(m, std::vector<int>(n, -2));
    int solution = solve(dp, possiblePositions, 0, 0);
    
    if (solution == -1) {
        std::cout << "fail" << std::endl;
    } else {
        std::cout << solution << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
