#include <iostream>

void testcase() {
    int n; std::cin >> n;
    int sum = 0;
    int even = 0;
    int odd = 0;
    
    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        sum += k;
        
        if (sum % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }
    
    // if the sum at two separate position are even, we get an even amount of ones inbetween these two positions
    // => even choose 2
    // if the sum at two separate position are odd, we get an even amount of ones inbetween these two positions
    // => odd choose 2
    // if a sum at a position is even, we don't have to choose a starting position at which we take a sum to subtract from
    // => add even
    
    std::cout << even * (even - 1) / 2 + odd * (odd - 1) / 2 + even << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
