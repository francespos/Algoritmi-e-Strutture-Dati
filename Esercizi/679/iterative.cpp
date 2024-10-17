#include <vector>
#include <iostream>
#include <cmath>

int getStopPosition(std::vector<bool>& flags, int numBalls) {
    int stopPos = 1;
    
    for (int i = 0; i < numBalls; ++i) {
        int pos = 1;
        
        while (pos <= flags.size()) {
            bool flag = flags[pos - 1];
            flags[pos - 1] = !flag;
            stopPos = pos;
            
            if (flag) {
                pos = 2 * pos + 1;
            } else {
                pos = 2 * pos;
            }
        }
    }
    
    return stopPos;
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> stopPositions(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int depth, numBalls;
        
        std::cin >> depth;
        std::cin >> numBalls;
        
        int numFlags = std::pow(2, depth) - 1;
        std::vector<bool> flags(numFlags, false);
    
        stopPositions[i] = getStopPosition(flags, numBalls);
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