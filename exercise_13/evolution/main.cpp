#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

typedef std::unordered_map<std::string, int> nameToIndex_type; // speciesName -> speciesIndex
typedef std::vector<std::string> indexToName_type; // speciesIndex -> speciesName
typedef std::vector<int> ages_type; // speciesIndex -> speciesAge
typedef std::vector<std::vector<int>> children_type; // ancestorSpeciesIndex -> offspringSpeciesIndexList
typedef std::vector<std::vector<std::pair<int, int>>> queries_type; // speciesIndex -> ageBound, queryIndex
typedef std::vector<int> results_type; // queryIndex -> speciesName
typedef std::vector<std::pair<int, int>> stack_type; // speciesAge, speciesIndex

int findSpeciesIndexForAgeBound(stack_type const & elements, int ageBound, int left, int right) {
    if (left >= right) {
        return elements[left].second;
    }
    
    int middle = (right + left) / 2;
    
    if (elements[middle].first <= ageBound) {
        return findSpeciesIndexForAgeBound(elements, ageBound, left, middle);
    } else {
        return findSpeciesIndexForAgeBound(elements, ageBound, middle+1, right);
    }
}

void dfs(ages_type const & ages, children_type const & children, queries_type const & queries, results_type & results, stack_type & stack, int currentSpeciesIndex) {
    stack.push_back({ages[currentSpeciesIndex], currentSpeciesIndex});
    
    for (std::pair<int, int> query : queries[currentSpeciesIndex]) {
        results[query.second] = findSpeciesIndexForAgeBound(stack, query.first, 0, stack.size()-1);
    }
    
    for (int child : children[currentSpeciesIndex]) {
        dfs(ages, children, queries, results, stack, child);
    }
    
    stack.pop_back();
}

void testcase() {
    int n; std::cin >> n;
    int q; std::cin >> q;
    nameToIndex_type nameToIndex = nameToIndex_type(n);
    indexToName_type indexToName = indexToName_type(n);
    ages_type ages = ages_type(n);
    children_type children = children_type(n, std::vector<int>{});
    queries_type queries = queries_type(n, std::vector<std::pair<int, int>>{});
    results_type results = results_type(q);
    int lucaIndex = 0;
    int maxAge = 0;
    
    for (int i = 0; i < n; i++) {
        std::string name; std::cin >> name;
        int age; std::cin >> age;
        nameToIndex.insert(std::make_pair(name, i));
        indexToName[i] = name;
        ages[i] = age;
        
        if (maxAge < age) {
            lucaIndex = i;
            maxAge = age;
        }
    }
    
    for (int i = 0; i < n-1; i++) {
        std::string child; std::cin >> child;
        std::string parent; std::cin >> parent;
        children[nameToIndex.at(parent)].push_back(nameToIndex.at(child));
    }
    
    for (int i = 0; i < q; i++) {
        std::string name; std::cin >> name;
        int ageBound; std::cin >> ageBound;
        queries[nameToIndex.at(name)].push_back({ageBound, i});
    }
    
    stack_type stack = stack_type{};
    dfs(ages, children, queries, results, stack, lucaIndex);
    
    for (int result : results) {
        std::cout << indexToName[result] << " ";
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
