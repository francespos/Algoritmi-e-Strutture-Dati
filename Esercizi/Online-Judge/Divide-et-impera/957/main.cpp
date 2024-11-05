/*
Input:
5
20
1
2
3
6
8
12
13
13
15
16
17
18
19
20
20
21
25
26
30
31
Output:
6 16 20
*/
// La complessita' e' O(n * m), dove n e' il numero di anni ed m e' la lunghezza
// della massima sequenza di anni di durata specificata.
#include <vector>
#include <iostream>

struct Indices {
    int p, r;
};

int getLastYearIndex(const std::vector<int>& years, int firstYearIndex, 
    int duration)
{
    auto yearIndex = firstYearIndex;
    
    while (yearIndex < years.size() &&
        years[yearIndex] < years[firstYearIndex] + duration) 
    {
        ++yearIndex;
    }
    
    return yearIndex - 1;
}

Indices findMaxIndices(const std::vector<int>& years, 
    const Indices& oldMaxIndices, int duration, int pos) 
{
    if (pos < years.size()) {
        auto firstYearIndex = pos;
        auto lastYearIndex = 
            getLastYearIndex(years, firstYearIndex, duration);
        
        // Non semplifico gli 1 per far capire cosa sto facendo
        if (lastYearIndex - firstYearIndex + 1 > 
            oldMaxIndices.r - oldMaxIndices.p + 1) 
        {
            Indices indices = {firstYearIndex, lastYearIndex};
            return findMaxIndices(years, indices, duration, pos + 1);
        }
        
        return findMaxIndices(years, oldMaxIndices, duration, pos + 1);
    }
    
    return oldMaxIndices;
} 

Indices findMaxIndices(const std::vector<int>& years, int duration) {
    return findMaxIndices(years, Indices{0, getLastYearIndex(years, 0, duration)}, 
        duration, 1);
}

int main() {
    int duration;
    std::cin >> duration;
    
    int numYears;
    std::cin >> numYears;
    
    std::vector<int> years(numYears);
    
    for (int i =  0; i < numYears; ++i) {
        std::cin >> years[i];
    }
    
    const auto maxIndices = findMaxIndices(years, duration);
    
    std::cout << maxIndices.r - maxIndices.p + 1 << " " << years[maxIndices.p]
        << " " << years[maxIndices.r] << "\n";
}