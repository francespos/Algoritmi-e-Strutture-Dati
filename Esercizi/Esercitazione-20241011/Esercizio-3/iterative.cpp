/*
Input
5
4 2
3 4
10 1
2 2
8 128 
-1
Output
12
7
512
3
255
*/
#include <vector>
#include <iostream>
#include <cmath>

int getStopPosition(std::vector<int>& flags, int numBalls) {
    int stopPos = 1;
    
    for (int i = 0; i < numBalls; ++i) {
        int pos = 1;
        
        while (pos <= flags.size()) {
            auto flag = flags[pos - 1];
            flags[pos - 1] = flag == 1 ? 0 : 1;
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
        
        auto numFlags = std::pow(2, depth) - 1;
        std::vector<int> flags(numFlags, 0);
    
        stopPositions[i] = getStopPosition(flags, numBalls);
    }
    
    int endOfInput;
    std::cin >> endOfInput;
    
    for (int i = 0; i < numTestCases; ++i) {
        std::cout << stopPositions[i] << "\n";
    }
}