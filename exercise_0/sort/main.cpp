#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> values{};
    
    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        values.push_back(k);
    }
    
    int x; std::cin >> x;
    
    if (x == 0) {
        std::sort(values.begin(), values.end());
    } else {
        std::sort(values.begin(), values.end(), std::greater<int>());
    }
    
    std::copy(values.cbegin(), values.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
