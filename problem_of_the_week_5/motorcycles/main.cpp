#include <iostream>
#include <vector>
#include <CGAL/Gmpq.h>

class Biker {
    public:
        int index;
        long position;
        CGAL::Gmpq absSlope;
        bool negative;
        
        Biker() {}
        
        Biker(int index, long position, CGAL::Gmpq slope)
            : index(index), position(position), absSlope(CGAL::abs(slope)), negative(slope < 0) {}
        
        bool operator<(Biker const &rhs) const {
            if (absSlope < rhs.absSlope) {
                return true;
            } else if (absSlope > rhs.absSlope) {
                return false;
            } else {
                if (negative != rhs.negative) {
                    return !negative;
                } else if (negative && rhs.negative) {
                    return position > rhs.position;
                } else {
                    return position < rhs.position;
                }
            }
        }
};

void testcase() {
    int n; std::cin >> n;
    std::vector<Biker> bikers(n);
    
    for (int i = 0; i < n; i++) {
        long y0; std::cin >> y0;
        long x1; std::cin >> x1;
        long y1; std::cin >> y1;
        bikers[i] = Biker(i, y0, CGAL::Gmpq(y1 - y0, x1));
    }
    
    std::sort(bikers.begin(), bikers.end());
    std::vector<bool> possible(n, false);
    possible[bikers[0].index] = true;
    long minY = bikers[0].position;
    long maxY = bikers[0].position; 
    
    for (Biker biker : bikers) {
        if (!biker.negative && biker.position > maxY) {
            possible[biker.index] = true;
        }
        
        if (biker.negative && biker.position < minY) {
            possible[biker.index] = true;
        }
        
        maxY = std::max(biker.position, maxY);
        minY = std::min(biker.position, minY);
    }
    
    for (int i = 0; i < n; i++) {
        if (possible[i]) {
            std::cout << i << ' ';
        }
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
