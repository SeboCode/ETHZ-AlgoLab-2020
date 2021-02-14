#include <iostream>
#include <vector>
#include <unordered_map>

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k;
    int w; std::cin >> w;
    std::vector<int> requiredMen(n);
    std::vector<std::vector<int>> waterways(w); 
    
    for (int i = 0; i < n; i++) {
        int c; std::cin >> c;
        requiredMen[i] = c;
    }
    
    for (int i = 0; i < w; i++) {
        int l; std::cin >> l;
        waterways[i] = std::vector<int>(l);
        
        for (int j = 0; j < l; j++) {
            std::cin >> waterways[i][j];
        }
    }
    
    int maxAttackableIslands = 0;
    // Stores the maximum amount of islands we can conquer with the given
    // amount of soldiers.
    std::unordered_map<int, int> maxIslandsWithSoldiers{};
    
    for (std::vector<int> waterway : waterways) {
        int left = 0;
        int right = 0;
        int usedSoldiers = requiredMen[waterway[left]];
        
        // This loop looks at the maximum amount of islands we can conquer,
        // when we only look at the current waterway (including Pyke).
        while (right <= waterway.size()) {
            if (usedSoldiers >= k) {
                if (usedSoldiers == k) {
                    maxAttackableIslands = std::max(maxAttackableIslands, right - left + 1);
                }
                
                usedSoldiers -= requiredMen[waterway[left]];
                left++;
            } else {
                right++;
                
                if (right == waterway.size()) {
                    break;
                }
                
                usedSoldiers += requiredMen[waterway[right]];
            }
        }
        
        usedSoldiers = 0;
        std::vector<int> usedSoldiersList{};
        
        // This loop calculates all men we use, when we attack the island next
        // to Pyke and walking outwards on the current waterway (excluding
        // Pyke). We use this information to determin, if we can conquer more
        // islands by conquering over Pyke into another waterway.
        for (int i = 1; i < waterway.size(); i++) {
            usedSoldiers += requiredMen[waterway[i]];
            
            if (usedSoldiers >= k) {
                break;
            }
            
            usedSoldiersList.push_back(usedSoldiers);
        }
        
        // This loop checks, if there is a way we can conquer a part of our
        // current waterway, conquer Pyke and the continue onward into another
        // waterway. Keep in mind that it doesn't matter, if we start conquering
        // in waterway A and end at waterway B or the other way around.
        for (int i = 0; i < usedSoldiersList.size(); i++) {
            auto it = maxIslandsWithSoldiers.find(k - usedSoldiersList[i] - requiredMen[waterway[0]]);
            
            if (it != maxIslandsWithSoldiers.end()) {
                // +3, because we have to count the Pyke and
                // because the stored value and i both start with 0.
                maxAttackableIslands = std::max(maxAttackableIslands, it->second + i + 3);
            }
        }
        
        // This loop now adds all possible soldier usages of the current
        // waterway to our map. If there is already another waterway, that
        // requires the same amount of soldiers to continue onwards, we store
        // the one where we conquer more islands.
        for (int i = 0; i < usedSoldiersList.size(); i++) {
            auto it = maxIslandsWithSoldiers.find(usedSoldiersList[i]);
            
            if (it != maxIslandsWithSoldiers.end()) {
                it->second = std::max(it->second, i);
            } else {
                maxIslandsWithSoldiers.emplace_hint(it, usedSoldiersList[i], i);
            }
        }
    }
    
    std::cout << maxAttackableIslands << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
