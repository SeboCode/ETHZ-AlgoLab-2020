#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits>
#include <boost/pending/disjoint_sets.hpp>

typedef std::tuple<int, int, int> edge_tuple;

int computeMst(std::vector<edge_tuple> const & edges, int ignoreEdge, int n, std::vector<int> & mst) {
    int mstCost = 0;
    boost::disjoint_sets_with_storage<> disjoint_set(n);
    
    for (int i = 0; i < edges.size(); i++) {
        int source = std::get<2>(edges[i]);
        int target = std::get<1>(edges[i]);
        
        if (i != ignoreEdge && disjoint_set.find_set(source) != disjoint_set.find_set(target)) {
            mst.push_back(i);
            mstCost += std::get<0>(edges[i]);
            disjoint_set.union_set(source, target);
            
            if (--n == 1) {
                break;
            }
        }
    }
    
    return mstCost;
}

void testcase() {
    int n; std::cin >> n;
    int tatooine; std::cin >> tatooine; // Irrelevant
    std::vector<edge_tuple> edges{};
    
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int cost; std::cin >> cost;
            // The priorities of the planets is irrelevant to our task, as we
            // are only required to print the cost, not the selected edges. If
            // the MST is unique, the priority can be ignored, if it is not
            // unique, then we will compute one of the MST's for reference and
            // another one when we want to find the minimum cost of the
            // modified solution.
            edges.push_back({cost, j, i});
        }
    }
    
    std::sort(edges.begin(), edges.end());
    std::vector<int> mstEdgeNumbers{};
    computeMst(edges, -1, n, mstEdgeNumbers);
    int minModifiedMstCost = INT_MAX;
    
    for (int edge : mstEdgeNumbers) {
        std::vector<int> dummy{};
        minModifiedMstCost = std::min(minModifiedMstCost, computeMst(edges, edge, n, dummy));
    }
    
    std::cout << minModifiedMstCost << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
