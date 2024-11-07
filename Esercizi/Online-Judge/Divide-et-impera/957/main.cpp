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
Complessita':
O(n^2).
*/
#include <vector>
#include <iostream>
#include <sstream>

struct Indices {
    int p, r;    
    
    int getSize() const {
        return r - p + 1;
    }
};

void setIndices(Indices& indices, const std::vector<int>& years, int duration) {
    if (indices.r < years.size() && 
        years[indices.r] - years[indices.p] + 1 <= duration) 
    {
        indices.r += 1;
        setIndices(indices, years, duration);
    }
    
    if ((indices.r < years.size() && 
        years[indices.r] - years[indices.p] + 1 > duration) || 
        indices.r == years.size())
    {
        indices.r -= 1;
    }
}

void setMaxSizeIndices(Indices& indices, Indices& maxSizeIndices, 
    const std::vector<int>& years, int duration)
{
    if (indices.p == years.size()) {
        return;
    }
    
    setIndices(indices, years, duration);
    
    if (indices.getSize() > maxSizeIndices.getSize()) {
        maxSizeIndices = indices;
    }
    
    indices.p +=  1;
    indices.r = indices.p;
    
    setMaxSizeIndices(indices, maxSizeIndices, years, duration);
}

Indices getMaxSizeIndices(const std::vector<int>& years, int duration) {
    Indices indices{0, 0};
    Indices maxSizeIndices{0, 0};
    
    setMaxSizeIndices(indices, maxSizeIndices, years, duration);
    return maxSizeIndices;
}

int main() {
    int duration;
    
    while (std::cin >> duration) {  
        int numYears;
        std::cin >> numYears;
        
        std::vector<int> years(numYears);
        
        for (auto& year : years) {
            std::cin >> year;
        }

        auto indices = getMaxSizeIndices(years, duration);

        std::cout << indices.getSize() << " "
            << years[indices.p] << " " 
            << years[indices.r] << "\n";
    }
}