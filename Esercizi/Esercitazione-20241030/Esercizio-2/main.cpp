/* 
Input:
2
Feldberg 10 5
56 14 51 58 88
26 94 24 39 41
24 16 8 51 51
76 72 77 43 10
38 50 59 84 81
5 23 37 71 77
96 10 93 53 82
94 15 96 69 9
74 0 62 38 96
37 54 55 82 38
Spiral 5 5 
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
Output:
Feldberg: 7
Spiral: 25
*/
#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>
#include <algorithm>

class Matrix {
public:
    Matrix(int numRows, int numCols) : m_entries(numRows * numCols), 
        m_numCols(numCols) {}

    Matrix(std::initializer_list<int> entries, int numCols) 
        : m_entries{entries}, m_numCols(numCols) {}
    
    int operator[](int i, int j) const {
        return m_entries[i *  m_numCols + j];
    }
    
    int& operator[](int i, int j) {
        return m_entries[i *  m_numCols + j];
    }
    
    int getNumRows() const {
        return m_entries.size() / m_numCols;
    }
    
    int getNumCols() const {
        return m_numCols;
    }
private:
    std::vector<int> m_entries;
    int m_numCols;
};

struct Point {
    int x, y;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

void pushBackIfLower(std::vector<Point>& candidates, const Matrix& grid, 
    const Point& curr, const Point& next)
{
    if (grid[curr.x, curr.y] > grid[next.x, next.y]) {
        candidates.push_back(next); 
    }
}

std::vector<Point> getCandidates(const Matrix& grid, const Point& pos) {
    std::vector<Point> candidates{};
    
    auto maxX = grid.getNumRows() - 1;
    auto maxY = grid.getNumCols() - 1;
    
    // Consideriamo prima i quattro angoli della griglia, poi tutti i punti che
    // si trovano ai quattro lati della griglia.
    if (pos == Point(0, 0)) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
    } else if (pos == Point(0, maxY)) {
        pushBackIfLower(candidates, grid, pos, pos + Point(1, 0));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
    } else if (pos == Point(maxX, 0)) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    } else if (pos == Point(maxX, maxY)) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    } else if (pos.x == 0) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(1, 0));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
    } else if (pos.y == 0) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(1, 0));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    } else if (pos.x == maxX) {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    } else if (pos.y == maxY) {
        pushBackIfLower(candidates, grid, pos, pos + Point(1, 0));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    } else {
        pushBackIfLower(candidates, grid, pos, pos + Point(0, 1));
        pushBackIfLower(candidates, grid, pos, pos + Point(1, 0));
        pushBackIfLower(candidates, grid, pos, pos + Point(0, -1));
        pushBackIfLower(candidates, grid, pos, pos + Point(-1, 0));
    }
    
    return candidates;
}

int backtrack(const Matrix& grid, const Point& pos,
    std::vector<Point>& positions) 
{
    auto candidates = getCandidates(grid, pos);
    int maxPathLength = positions.size();
    
    for (const auto& candidate : candidates) {
        positions.push_back(candidate);

        auto pathLength = backtrack(grid, candidate, positions);
        
        if (pathLength > maxPathLength) {
            maxPathLength = pathLength;
        }
        
        positions.pop_back();
    }

    return maxPathLength;
}

int getSolution(const Matrix& grid) {
    std::vector<int> solutions{};
    
    for (int i = 0; i < grid.getNumRows(); ++i) {
        for (int j = 0; j < grid.getNumCols(); ++j) {
            Point pos(i, j);
            std::vector<Point> positions{};
            
            solutions.push_back(backtrack(grid, pos, positions));
        }
    }
    
    return *std::max_element(solutions.begin(), solutions.end()) + 1;
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<std::string> names{};
    std::vector<int> solutions{};
    
    for (int k = 0; k < numTestCases; ++k) {
        std::string name{};
        std::cin >> name;
        names.push_back(name);
        
        int numRows, numCols;
        
        std::cin >> numRows;
        std::cin >> numCols;
        
        Matrix grid(numRows, numCols);

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cin >> grid[i, j];
            }
        }
        
        solutions.push_back(getSolution(grid));
    }
    
    for (int k = 0; k < numTestCases; ++k) {
        std::cout << names[k] << ": " << solutions[k] << "\n";
    }
}