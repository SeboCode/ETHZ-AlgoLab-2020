#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

void testcase() {
    int q; std::cin >> q;
    std::set<int> s{};
    
    for (int i = 0; i < q; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        
        if (a == 0) {
            s.insert(b);
        } else {
            s.erase(b);
        }
    }
    
    if (s.empty()) {
        std::cout << "Empty" << std::endl;
    } else {
        std::copy(s.cbegin(), s.cend(), std::ostream_iterator<int> (std::cout, " "));
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
