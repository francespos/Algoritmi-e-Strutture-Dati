#include <iostream>
#include <vector>

using List = std::vector<int>;

int findNumSequences(const std::vector<List>& lists, std::vector<int>& sequence)
{
    
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> results(numTestCases);
    
    for (auto& result : results) {
        int numColors, numLists, sequenceLen; 
        
        std::cin >> numColors;
        std::cin >> numLists;
        std::cin >> sequenceLen;

        std::vector<List> lists{};
        
        int i = 0;

        while (i < numColors) {
            int listLen;
            std::cin >> listLen;
            
            List list(listLen);
            
            for (auto& color : list) {
                std::cin >> color;
            }
            
            lists.push(list);
            i += listLen;
        }
        
        std::vector<int> sequence(sequenceLen);
        
        for (auto& color : sequence) {
            std::cin >> color;
        }
        
        result = findNumSegments(lists, sequence);
    }
    
    for (auto result : results) {
        std::cout << result << "\n";
    }
}