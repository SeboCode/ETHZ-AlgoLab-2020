#include <iostream>
#include <vector>
#include <map>
#include <cmath>

int mask24 = std::pow(2, 24) - 1;
int mask16 = std::pow(2, 16) - 1;
int mask8 = std::pow(2, 8) - 1;

struct State {
    int gateDifference;
    // We use 8 bits to represent a fighterType.
    int lastSentFightersNorth;
    int lastSentFightersSouth;
    int mask;
    
    State() {};
    
    State(int fighterCount) :
        gateDifference(0), lastSentFightersNorth(0), lastSentFightersSouth(0), mask(fighterCount == 2 ? mask16 : mask24) {}
    
    State(State const & other) :
        gateDifference(other.gateDifference),
        lastSentFightersNorth(other.lastSentFightersNorth),
        lastSentFightersSouth(other.lastSentFightersSouth),
        mask(other.mask) {}
    
    void sendFighter(int fighterType, bool isNorth) {
        if (isNorth) {
            lastSentFightersNorth = ((lastSentFightersNorth << 8) & mask) + (fighterType & mask8);
            gateDifference--;
        } else {
            lastSentFightersSouth = ((lastSentFightersSouth << 8) & mask) + (fighterType & mask8);
            gateDifference++;
        }
    }
    
    int calculateExcitement(bool isNorth) const {
        int fighters = lastSentFightersSouth;
        
        if (isNorth) {
            fighters = lastSentFightersNorth;
        }
        
        int firstFighter = fighters & mask8;
        int secondFighter = (fighters >> 8) & mask8;
        int thirdFighter = (fighters >> 16) & mask8;
        int excitementFactor = (firstFighter && firstFighter != secondFighter && firstFighter != thirdFighter) + (secondFighter && secondFighter != thirdFighter) + (thirdFighter != 0);
        return excitementFactor * 1000 - (1 << std::abs(gateDifference));
    }
    
    bool operator <(State const & rhs) const {
        if (lastSentFightersNorth != rhs.lastSentFightersNorth) {
            return lastSentFightersNorth < rhs.lastSentFightersNorth;
        }
        
        if (lastSentFightersSouth != rhs.lastSentFightersSouth) {
            return lastSentFightersSouth < rhs.lastSentFightersSouth;
        }
        
        return gateDifference < rhs.gateDifference;
    }
};

void storeBestExcitementScore(std::map<State, int> & next, State const & state, bool isNorth, int currentExcitement) {
    int roundExcitement = state.calculateExcitement(isNorth);
    
    if (roundExcitement < 0) {
        return;
    }
    
    const auto it = next.find(state); 
    
    if (it != next.end()) {
        // It can happen that we end up in the same state, as we can add a
        // fighter to the south or the north. Therefore we could have one state,
        // where adding the current fighter to the north gives us state S and
        // another state, where adding the current fighter to the south gives
        // us S as well.
        it->second = std::max(it->second, roundExcitement + currentExcitement);
    } else {
        next.emplace_hint(it, state, roundExcitement + currentExcitement);
    }
}

void testcase() {
    int n; std::cin >> n;
    int k; std::cin >> k; // useless
    int m; std::cin >> m;
    
    // We store the best possible excitement level for each state that we can
    // be in, after each fighter that has been processed.
    std::map<State, int> current;
    current.insert({State(m), 0});
    std::map<State, int> next;
    
    for (int i = 0; i < n; i++) {
        int fighterType; std::cin >> fighterType; fighterType++;
        next.clear();
        
        for (auto const & element : current) {
            State chooseNorthState(element.first);
            chooseNorthState.sendFighter(fighterType, true);
            storeBestExcitementScore(next, chooseNorthState, true, element.second);
            State chooseSouthState(element.first);
            chooseSouthState.sendFighter(fighterType, false);
            storeBestExcitementScore(next, chooseSouthState, false, element.second);
        }
        
        // With this, current once again contains all possible states with its
        // maximal excitement level.
        std::swap(next, current);
    }
    
    int best = 0;
    
    for (auto const & element : current) {
        best = std::max(best, element.second);
    }
    
    std::cout << best << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    
    for (int i = 0; i < t; i++) {
        testcase();
    }
}
