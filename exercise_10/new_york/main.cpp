#include <iostream>
#include <vector>
#include <queue>

void testcase() {
    int n; std::cin >> n;
    int m; std::cin >> m;
    int k; std::cin >> k;
    std::vector<int> predecessor(n);
    std::vector<int> temperature(n);
    std::vector<bool> isLeaf(n, true);
    std::vector<bool> startsFeasibleJourney(n, false);
    std::vector<bool> checkedAsEndOfFeasibleJourney(n, false);
    
    for (int i = 0; i < n; i++) {
        int h; std::cin >> h;
        temperature[i] = h;
    }
    
    for (int i = 0; i < n-1; i++) {
        int u; std::cin >> u;
        int v; std::cin >> v;
        predecessor[v] = u;
        isLeaf[u] = false;
    }
    
    std::vector<int> insideWindow(n, -1);
    
    for (int i = 0; i < n; i++) {
        if (!isLeaf[i]) {
            continue;
        }
        
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minTempHeap{};
        std::priority_queue<std::pair<int, int>> maxTempHeap{};
        int left = i;
        int right = i;
        int distance = 1;
        insideWindow[i] = i;
        minTempHeap.push({temperature[i], i});
        maxTempHeap.push({temperature[i], i});
        
        while(true) {
            if (maxTempHeap.top().first - minTempHeap.top().first > k || distance == m) {
                if (distance == m && maxTempHeap.top().first - minTempHeap.top().first <= k) {
                    startsFeasibleJourney[right] = true;
                }
                
                checkedAsEndOfFeasibleJourney[left] = true;
                insideWindow[left] = -1;
                
                while (!minTempHeap.empty() && insideWindow[minTempHeap.top().second] != i) {
                    minTempHeap.pop();
                }
                
                while (!maxTempHeap.empty() && insideWindow[maxTempHeap.top().second] != i) {
                    maxTempHeap.pop();
                }
                
                left = predecessor[left];
                distance--;
                
                if (checkedAsEndOfFeasibleJourney[left]) {
                    break;
                }
            } else {
                if (right == 0) {
                    break;
                }
                
                right = predecessor[right];
                distance++;
                insideWindow[right] = i;
                minTempHeap.push({temperature[right], right});
                maxTempHeap.push({temperature[right], right});
            }
        }
    }
    
    int feasibleTripCounter = 0;
    
    for (int i = 0; i < startsFeasibleJourney.size(); i++) {
        if (startsFeasibleJourney[i]) {
            std::cout << i << " ";
            feasibleTripCounter++;
        }
    }
    
    if (feasibleTripCounter == 0) {
        std::cout << "Abort mission";
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
