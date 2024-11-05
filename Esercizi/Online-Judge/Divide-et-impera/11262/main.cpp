/*
Dato un insieme di punti del piano cartesiano con i rispettivi colori
(rosso o blu), trovare la parte intera della minima lunghezza dei 
collegamenti tra punti di colore diverso dato il numero k di collegamenti.
Input:
2
6 2
-3 5 blue
-3 3 red
1 5 blue
2 0 red
4 6 blue
4 -1 red
6 4
-3 5 blue
-3 3 red
1 5 blue
2 0 red
4 6 blue
4 -1 red
Output:
6
Impossible
Complessita': O(k * m * n), dove m è il numero di blu ed n il numero di rossi.
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

int getFloor(float x) {
    return static_cast<int>(x);
}

int getCeiling(float x) {
    if (x - getFloor(x) > 0) {
        return x + 1;
    } else {
        return x;
    }
}

int getSquare(int x) {
    return x * x;
}

struct Point {
    int x, y;
    
    float getFloatDistance(const Point& other) const {
        return std::sqrt(getSquare(x - other.x) + getSquare(y - other.y));
    }
    
    int getDistance(const Point& other) const {
        return getCeiling(getFloatDistance(other));
    }   
};

int getMinInt() {
    return -1000;    
}

int getMaxInt() {
    return 1000;
}

int getMaxLength() {
    auto minInt = getMinInt();
    auto maxInt = getMaxInt();
    
    Point p1{minInt, minInt};
    Point p2{maxInt, maxInt};
    
    return p1.getDistance(p2);
}

struct BlueRedIndices {
    int bluePos, redPos;
};

struct Fence {
    Point blue, red;
    
    Fence(const std::vector<Point>& blues, const std::vector<Point>& reds, 
        const BlueRedIndices& indices) 
        : blue(blues[indices.bluePos]), red(reds[indices.redPos]) {}
    
    int getLength() const {
        return blue.getDistance(red);
    }
};

BlueRedIndices findMinLengthIndices(const std::vector<Point>& blues, 
    const std::vector<Point>& reds, int bluePos, int redPos, 
    BlueRedIndices minIndices) 
{
    if (bluePos == blues.size()) {
        return minIndices;
    }
    
    BlueRedIndices indices{bluePos, redPos};
    
    Fence fence(blues, reds, indices);
    Fence minFence(blues, reds, minIndices);
    
    if (fence.getLength() < minFence.getLength()) {
        minIndices = indices;
    }
    
    if (redPos == reds.size() - 1) {
        bluePos = bluePos + 1;
        redPos = 0;
    } else {
        redPos = redPos + 1;
    }
    
    return findMinLengthIndices(blues, reds, bluePos, redPos, minIndices);
}

int findMinLength(std::vector<Point>& blues, std::vector<Point>& reds, int k,
    int minLength)
{
    if (k == 0) {
        return minLength;
    }
    
    auto minIndices = findMinLengthIndices(blues, reds, 0, 0, 
        BlueRedIndices{0, 0});
        
    Fence minFence(blues, reds, minIndices);
    minLength = minFence.getLength();
    
    blues.erase(blues.begin() + minIndices.bluePos);
    reds.erase(reds.begin() + minIndices.redPos);
    
    return findMinLength(blues, reds, k - 1, minLength);
}

int findMinLength(const std::vector<Point>& blues, 
    const std::vector<Point>& reds, int k)
{
    if (std::min(blues.size(), reds.size()) < k) {
        return -1;
    }
    
    Fence minFence(blues, reds, BlueRedIndices{0, 0});
    auto minLength = getMaxLength();

    std::vector<Point> bluesCopy(blues);
    std::vector<Point> redsCopy(reds);
    
    return findMinLength(bluesCopy, redsCopy, k, minLength);
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<std::string> resultStrings(numTestCases);
    
    for (auto& resultString : resultStrings) {
        std::vector<Point> blues{};
        std::vector<Point> reds{};
        
        int numPoints;
        std::cin >> numPoints;
        
        int numFences;
        std::cin >> numFences;
        
        for (int j = 0; j < numPoints; ++j) {
            Point point;
            
            std::cin >> point.x;
            std::cin >> point.y;
            
            std::string color;
            std::cin >> color;
            
            if (color == "blue") {
                blues.push_back(point);
            } else if (color == "red") {
                reds.push_back(point);
            }
        }
        
        auto result = findMinLength(blues, reds, numFences);
        
        resultString = std::string(result < 0 ? "Impossible" : std::to_string(
            result));
    }
    
    for (const auto& resultString : resultStrings) {
        std::cout << resultString << "\n";
    }
}