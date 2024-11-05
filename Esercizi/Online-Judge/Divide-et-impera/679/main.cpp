/*
Input:
5
4 2
3 4
10 1
2 2
8 128 
-1
Output:
12
7
512
3
255
La complessita' e' Theta(d * n), dove d e' la profonfita' dell'albero e n e' 
il numero di palle.
*/
#include <iostream>
#include <cmath>
#include <vector>

int getStopPosition(std::vector<int>& flags, int pos, int numBalls) {
    if (pos > flags.size()) {
        return pos / 2;
    }
    
    auto flag = flags[pos - 1];
    flags[pos - 1] = flag == 1 ? 0 : 1;
    
    if (pos * 2 > flags.size()) {
        --numBalls;
        
        if (numBalls == 0) {
            return pos;
        }
        
        pos = 1;
    } else if (flag == 1) {
        pos = pos * 2 + 1;
    } else {
        pos = pos * 2;
    }
    
    return getStopPosition(flags, pos, numBalls);
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> results(numTestCases);
    
    for (auto& result : results) {
        int depth, numBalls;
        
        std::cin >> depth;
        std::cin >> numBalls;
        
        auto numFlags = std::pow(2, depth) - 1;
        std::vector<int> flags(numFlags, 0);
    
        result = getStopPosition(flags, 1, numBalls);
    }
    
    int endOfInput;
    std::cin >> endOfInput;
    
    for (auto result : results) {
        std::cout << result << "\n";
    }
}