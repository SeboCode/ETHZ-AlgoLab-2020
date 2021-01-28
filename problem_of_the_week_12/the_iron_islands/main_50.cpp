#include <iostream>
#include <vector>

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    int w; std::cin >> w;
    std::vector<std::vector<int>> waterWays(w+1, std::vector<int>{});
    std::vector<int> requiredMen(n);
    
    for (int i = 0; i < n; i++) {
        int c; std::cin >> c;
        requiredMen[i] = c;
    }
    
    for (int i = 0; i < w; i++) {
        int l; std::cin >> l;
        int r0; std::cin >> r0;
        
        for (int j = 0; j < l-1; j++) {
            int r; std::cin >> r;
            waterWays[i].push_back(r);
        }
    }
    
    int max = 0;
    
    for (int i = 0; i < w+1; i++) {
        for (int j = i+1; j < w+1; j++) {
            std::vector<int> islands(waterWays[i].size() + waterWays[j].size() + 1);
            int counter = 0;
            
            for (int k = waterWays[i].size() - 1; k >= 0; k--) {
                islands[counter] = waterWays[i][k];
                counter++;
            }
            
            islands[counter] = 0;
            counter++;
            
            for (int island : waterWays[j]) {
                islands[counter] = island;
                counter++;
            }
            
            int left = 0;
            int right = 1;
            int usedSoldiers = requiredMen[islands[left]];
            
            while(right <= islands.size()) {
                if (usedSoldiers >= k) {
                    if (usedSoldiers == k) {
                        max = std::max(max, right - left);
                    }
                    
                    usedSoldiers -= requiredMen[islands[left]];
                    left++;
                } else {
                    if (right == islands.size()) {
                        break;
                    }
                    
                    usedSoldiers += requiredMen[islands[right]];
                    right++;
                }
            }
        }
    }
    
    std::cout << max << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
