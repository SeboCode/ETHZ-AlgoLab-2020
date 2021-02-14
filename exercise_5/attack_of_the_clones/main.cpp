#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int n;
int m;

struct Jedi {
    public:
        int startPosition;
        int endPosition;
        
        bool operator<(Jedi const & rhs) const {
            return endPosition < rhs.endPosition;
        }
};

bool inSegment(Jedi jedi, int segment) {
    if (jedi.startPosition <= jedi.endPosition) {
        return jedi.startPosition <= segment && segment <= jedi.endPosition;
    } else {
        return segment <= jedi.endPosition || jedi.startPosition <= segment;
    }
}

int solve(std::vector<Jedi> const & jedies, Jedi const & reference) {
    std::vector<Jedi> reallocatedJedies{};
    
    for (Jedi jedi : jedies) {
        if (inSegment(reference, jedi.startPosition) || inSegment(reference, jedi.endPosition)) {
            continue;
        }
        
        if (jedi.startPosition < reference.endPosition) {
            jedi.startPosition += m;
        }
        
        if (jedi.endPosition < reference.endPosition) {
            jedi.endPosition += m;
        }
        
        if (jedi.endPosition < jedi.startPosition) {
            jedi.endPosition += m;
        }
        
        jedi.startPosition -= reference.endPosition;
        jedi.endPosition -= reference.endPosition;
        reallocatedJedies.push_back(jedi);
    }
    
    std::sort(reallocatedJedies.begin(), reallocatedJedies.end());
    int count = 0;
    int endPosition = 0;
    
    for (Jedi & jedi : reallocatedJedies) {
        if (endPosition < jedi.startPosition) {
            count++;
            endPosition = jedi.endPosition;
        }
    }
    
    return count;
}

void testcase() {
    std::cin >> n;
    std::cin >> m;
    std::vector<Jedi> jedies(n);
    std::map<int, int> segmentTable{};
    
    for (int i = 0; i < n; i++) {
        int a; std::cin >> a;
        int b; std::cin >> b;
        jedies[i] = Jedi{a, b};
        
        segmentTable[a]++;
        segmentTable[b]--;
    }
    
    int smallestSegmentIndex = -1;
    int countJedis = 0;
    int smallestSegmentJedisCount = n;
    
    for (std::pair<int, int> segment : segmentTable) {
        if (segment.second > 0) {
            countJedis += segment.second;
        }
        
        if (smallestSegmentIndex == -1 || countJedis < smallestSegmentJedisCount) {
            smallestSegmentIndex = segment.first;
            smallestSegmentJedisCount = countJedis;
        }
        
        if (segment.second < 0) {
            countJedis += segment.second;
        }
    }
    
    int amount = solve(jedies, Jedi{smallestSegmentIndex, smallestSegmentIndex});
    
    for (int i = 0; i < n; i++) {
        if (inSegment(jedies[i], smallestSegmentIndex)) {
            amount = std::max(amount, solve(jedies, jedies[i]) + 1);
        }
    }
    
    std::cout << amount << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
