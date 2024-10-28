// La complessita' nel caso peggiore e' (n-1)(n-2)*...* 2 * k, cioe' 
// O(k * n!)
#include <cmath>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

struct Point {
    float x, y;
};

constexpr float getSquare(float x) {
    return x * x;
}

float getDistance(const Point& lhs, const Point& rhs) {
    return std::sqrt(getSquare(lhs.x - rhs.x) + getSquare(lhs.y - rhs.y));
}

struct Outpost final : public Point { 
    bool hasASatellite;
};

struct Indices {
    int p, r;    
};

/*
std::ostream& operator<<(std::ostream& out, const Indices& indices) {
    return out << "(" << indices.p << ", " << indices.r << ")";
}
*/

void setMinDistancesAndIndices(std::vector<float>& distances, 
    std::vector<int>& lastPoss, std::vector<Outpost>& outposts, int firstPos,
    int lastPos, float oldMin) 
{
    if (firstPos < outposts.size() - 1) {
        if (lastPos < outposts.size() && !(outposts[firstPos].hasASatellite && 
            outposts[lastPos].hasASatellite))
        {
            const auto value = getDistance(outposts[firstPos], 
            outposts[lastPos]);

            auto min = oldMin;

            if (value < oldMin) {
                min = value;
                lastPoss[firstPos] = lastPos;
            }

            setMinDistancesAndIndices(distances, lastPoss, outposts, firstPos, 
                lastPos + 1, min);
        } else if (lastPos < outposts.size()) {
            setMinDistancesAndIndices(distances, lastPoss, outposts, firstPos, 
            lastPos + 1, 0);
        } else {
            distances[firstPos] = oldMin;

            setMinDistancesAndIndices(distances, lastPoss, outposts, 
                firstPos + 1, firstPos + 2, INT_MAX);
        }
    }
}

void setSatellites(std::vector<float>& distances, std::vector<int>& lastPoss,
    std::vector<Outpost>& outposts, int numSatellites) 
{
    if (numSatellites > 0) {
        setMinDistancesAndIndices(distances, lastPoss, outposts, 0, 1, INT_MAX);
        
        /*
        for (auto distance : distances) {
            std::cout << distance << " ";
        }
        std::cout << "\n";
        */
        
        auto max = distances[0];
        int maxPos = 0;
        
        for (int i = 1; i < distances.size(); ++i) {
            const auto value = distances[i];
            
            if (value > max) {
                max = value;
                maxPos = i;
            }
        }
        
        if (outposts[maxPos].hasASatellite) {
            outposts[lastPoss[maxPos]].hasASatellite = true;
        } else {
            outposts[maxPos].hasASatellite = true;
        }
        
        setSatellites(distances, lastPoss, outposts, numSatellites - 1);
    }
}

float getDistance(std::vector<Outpost>& outposts, 
    int numSatellites)
{
    std::vector<float> distances(outposts.size() - 1);
    std::vector<int> lastPoss(outposts.size() - 1, 0);
    
    setSatellites(distances, lastPoss, outposts, numSatellites);
    setMinDistancesAndIndices(distances, lastPoss, outposts, 0, 1, INT_MAX);
    
    /*
    for (auto distance : distances) {
        std::cout << distance << " ";
    }
    std::cout << "\n";
    */
    
    return *(std::max_element(distances.begin(), distances.end()));
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<float> distances(numTestCases);
    
    for (int i = 0; i < numTestCases; ++i) {
        int numSatellites;
        std::cin >> numSatellites;
        
        int numOutposts;
        std::cin >> numOutposts;
        
        std::vector<Outpost> outposts(numOutposts);
        
        for (int j = 0; j < numOutposts; ++j) {
            std::cin >> outposts[j].x;
            std::cin >> outposts[j].y;
            
            outposts[j].hasASatellite = false;
        }
        
        distances[i] = getDistance(outposts, numSatellites);
    }
    
    for (int i = 0; i < numTestCases; ++i) {
        std::cout << distances[i] << "\n"; 
    }
}