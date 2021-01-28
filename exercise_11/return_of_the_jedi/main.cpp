#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <boost/pending/disjoint_sets.hpp>

typedef std::tuple<int, int, int> edge_tuple;

int computeMst(std::vector<edge_tuple> const & edges, int ignoreEdge, int n, std::vector<int> &mst) {
    boost::disjoint_sets_with_storage<> disjoint_set(n);
    int mstTotal = 0;
    
    for (int i = 0; i < edges.size(); i++) {
        int source = std::get<2>(edges[i]);
        int target = std::get<1>(edges[i]);
        
        if (i != ignoreEdge && disjoint_set.find_set(source) != disjoint_set.find_set(target)) {
            mst.push_back(i);
            mstTotal += std::get<0>(edges[i]);
            disjoint_set.union_set(source, target);
            
            if (--n == 1) {
                break;
            }
        }
    }
    
    return mstTotal;
}

void testcase() {
    int n; std::cin >> n;
    int tatooine; std::cin >> tatooine;
    std::vector<edge_tuple> edges{};
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int cost; std::cin >> cost;
            edges.push_back({cost, -j, -i});
       }
    }
    
    std::sort(edges.begin(), edges.end());
    
    for (int i = 0; i < edges.size(); i++) {
        edges[i] = {std::get<0>(edges[i]), -std::get<1>(edges[i]), -std::get<2>(edges[i])};
    }
    
    std::vector<int> mstEdgeNumbers{};
    int mstSize = computeMst(edges, -1, n, mstEdgeNumbers);
    int minDifferentMst = pow(2, 20) + 1;
    
    for (int mstEdgeNumber : mstEdgeNumbers) {
        std::vector<int> dummy{};
        minDifferentMst = std::min(minDifferentMst, computeMst(edges, mstEdgeNumber, n, dummy) - mstSize);
    }
    
    std::cout << mstSize + minDifferentMst << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
