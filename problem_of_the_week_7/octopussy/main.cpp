#include <iostream>
#include <vector>
#include <algorithm>

int n;

int solve(std::vector<bool> &visited, int index) {
    if (visited[index]) {
        return 0;
    }
    
    int timeForBallsBelow = 0;
    
    if (index <= (n - 3) / 2) {
        timeForBallsBelow = solve(visited, index * 2 + 1) + solve(visited, index * 2 + 2);
    }
    
    visited[index] = true;
    return timeForBallsBelow + 1;
}

void testcase() {
    std::cin >> n;
    std::vector<std::pair<int, int>> balls(n);
    
    for (int i = 0; i < n; i++) {
        int t; std::cin >> t;
        balls[i] = { t, i };
    }
    
    std::sort(balls.begin(), balls.end());
    std::vector<bool> visited(n, false);
    int timeUsed = 0;
    
    for (int i = 0; i < n; i++) {
        int timeLimit = balls[i].first;
        int index = balls[i].second;
        
        if (visited[index]) {
            continue;
        }
        
        timeUsed += solve(visited, index);
        
        if (timeUsed > timeLimit) {
            std::cout << "no" << std::endl;
            return;
        }
    }
    
    std::cout << "yes" << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}

/* alternative:
void testcase() {
    int n; std::cin >> n;
    std::vector<int> t(n);

    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }
    
    for (int i = 0; i <= (n - 3) / 2; i++) {
        t[2 * i + 1] = std::min(t[2 * i + 1], t[i] - 1);
        t[2 * i + 2] = std::min(t[2 * i + 2], t[i] - 1);
    }
    
    std::sort(t.begin(), t.end());
    
    for (int i = 0; i < n; i++) {
        if (t[i] < i + 1) {
            std::cout << "no" << std::endl;
            return;
        }
    }

    std::cout << "yes" << std::endl;
}
*/
