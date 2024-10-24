// La complessita' e' Theta(d * n), dove d e' la profonfita' dell'albero e n e' 
// il numero di palle.
#include <deque>
#include <iostream>
#include <cmath>
#include <vector>

int getStopPosition(std::deque<bool>& flags, int pos, int numBalls) {
    if (pos > flags.size()) {
        return pos / 2;
    }
    
    const auto flag = flags[pos - 1];
    flags[pos - 1] = !flag;
    
    if (pos * 2 > flags.size()) {
        --numBalls;
        
        if (numBalls == 0) {
            return pos;
        }
        
        pos = 1;
    } else if (flag) {
        pos = pos * 2 + 1;
    } else {
        pos = pos * 2;
    }
    
    return getStopPosition(flags, pos, numBalls);
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> stopPositions(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int depth, numBalls;
        
        std::cin >> depth;
        std::cin >> numBalls;
        
        const auto numFlags = std::pow(2, depth) - 1;
        std::deque<bool> flags(numFlags, false);
    
        stopPositions[i] = getStopPosition(flags, 1, numBalls);
    }
    
    int endOfInput;
    std::cin >> endOfInput;

    if (endOfInput != -1) {
        return -1;
    }
    
    for (int i = 0; i < numTestCases; ++i) {
        std::cout << stopPositions[i] << "\n";
    }
}