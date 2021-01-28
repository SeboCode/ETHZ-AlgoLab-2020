#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> parasols{};
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(parasols));
    
    std::sort(parasols.begin(), parasols.end());
    
    int left = 0;
    int right = 0;
    int maxCustomers = 0;
    int minDistance = 0;
    int currentCustomers = 1;
    
    std::vector<int> possiblePositions{};
    
    while (right < n) {
        int distance = (parasols[right] - parasols[left]) / 2;
        
        if ((parasols[right] - parasols[left]) % 2 == 1) {
            distance++;
        }
        
        if (distance > 100) {
            left++;
            currentCustomers--;
        } else {
            int positionLeft = parasols[left] + distance;
            int positionRight = parasols[right] - distance;
            
            if (maxCustomers < currentCustomers) {
                maxCustomers = currentCustomers;
                minDistance = distance;
                possiblePositions.clear();
                possiblePositions.push_back(positionLeft);
                
                if (positionRight != positionLeft) {
                    possiblePositions.push_back(positionRight);
                }
            } else if (maxCustomers == currentCustomers && distance <= minDistance) {
                if (distance < minDistance) {
                    possiblePositions.clear();
                    minDistance = distance;
                }
                
                possiblePositions.push_back(positionLeft);
                
                if (positionRight != positionLeft) {
                    possiblePositions.push_back(positionRight);
                }
            }
            
            right++;
            currentCustomers++;
        }
    }
    
    std::sort(possiblePositions.begin(), possiblePositions.end());
    
    std::cout << maxCustomers << ' ' << minDistance << '\n';
    std::copy(possiblePositions.cbegin(), possiblePositions.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
