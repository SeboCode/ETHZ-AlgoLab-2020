#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void testcase() {
    int n; std::cin >> n;
    std::vector<int> v{};
    
    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        v.push_back(k);
    }
    
    int d; std::cin >> d;
    v.erase(v.begin() + d);
    int a; std::cin >> a;
    int b; std::cin >> b;
    v.erase(v.begin() + a, v.begin() + b + 1);
    
    if (v.empty()) {
        std::cout << "Empty" << std::endl;
    } else {
        std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int> (std::cout, " "));
        std::cout << std::endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
