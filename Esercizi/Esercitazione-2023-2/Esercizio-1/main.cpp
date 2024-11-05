/*
Input:
3 
4 
5 
8
Output:
2 
10 
92 
*/

#include <vector>
#include <initializer_list>
#include <iostream>

class Matrix {
private:
    std::vector<int> m_entries;
    int m_numCols;
public:
    Matrix(int numRows, int numCols) : m_entries(numRows * numCols, 0), 
        m_numCols(numCols) {}

    Matrix(std::initializer_list<int> entries, int numCols) 
        : m_entries{entries}, m_numCols(numCols) {}
    
    int operator()(int i, int j) const {
        return m_entries[i *  m_numCols + j];
    }
    
    int& operator()(int i, int j) {
        return m_entries[i *  m_numCols + j];
    }
    
    int getNumRows() const {
        return m_entries.size() / m_numCols;
    }
    
    int getNumCols() const {
        return m_numCols;
    }
};

struct Point {
    int x, y;
};

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point operator+(const Point& lhs, const Point& rhs) {
    return Point{lhs.x + rhs.x, lhs.y + rhs.y};
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    return out << "(" << point.x << ", " << point.y << ")";
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (int i = 0; i < matrix.getNumRows(); ++i) {
        out << "[ ";
        for (int j = 0; j < matrix.getNumCols(); ++j) {
            out << matrix(i, j) << " ";
        }
        out << "]\n";
    }
    
    return out;
}

std::vector<Point> getCandidates(const Matrix& grid, const Point& pos) {
    std::vector<Point> candidates{};
    
    if (pos.y == grid.getNumCols() - 1) {
        return candidates;
    }
    
    for (int i = 0; i < grid.getNumRows(); ++i) {
        auto isAValidCandidate = true;
    
        for (int j = pos.y; j >= 0 ; --j) {
            if (grid(i, j) == 1) {
                isAValidCandidate = false;
                break;
            }
        }
        
        auto i2 = i - 1;
        auto j = pos.y;
        
        while (i2 >= 0 && j >= 0) {
            if (grid(i2, j) == 1) {
                isAValidCandidate = false;
                break;
            }
            
            --i2; --j;
        }
        
        i2 = i + 1;
        j = pos.y;
        
        while (i2 < grid.getNumRows() && j >= 0) {
            if (grid(i2, j) == 1) {
                isAValidCandidate = false;
                break;
            }
            
            ++i2; --j;
        }
        
        if (isAValidCandidate) {
            Point point{i, pos.y + 1};
            candidates.push_back(point);
            
            // std::cout << point << "\n";
            // std::cout << grid;
        }
    }
    
    return candidates;
}

bool isASolution(const Matrix& grid, Point pos) {
    return pos.y == grid.getNumCols() - 1; 
}

void makeMove(Matrix& grid, const Point& pos) {
    grid(pos.x, pos.y) = 1;
}

void unmakeMove(Matrix& grid, const Point& pos) {
    grid(pos.x, pos.y) = 0;    
}

int backtrack(Matrix& grid, const Point& pos,
    std::vector<Point>& positions, int result) 
{
    if (isASolution(grid, pos)) {
        // std::cout << "Una soluzione trovata" << "\n";
        return result + 1;
    } else {
        auto candidates = getCandidates(grid, pos);
        
        for (const auto& candidate : candidates) {
            makeMove(grid, candidate);
            positions.push_back(candidate);
            
            result = backtrack(grid, candidate, positions, result);
            
            unmakeMove(grid, candidate);
            positions.pop_back();
        }
    }
    
    // std::cout << "Sono arrivato ad un vicolo cieco\n";
    return result;
}

int getSolution(Matrix& grid) {
    std::vector<int> solutions(grid.getNumRows());
    
    for (int i = 0; i < solutions.size(); ++i) {
        std::vector<Point> positions{};
        
        Point point{i, 0};
        makeMove(grid, point);
        
        // std::cout << "Soluzioni per " << point << ":\n";
        auto solution = backtrack(grid, point, positions, 0);
        
        unmakeMove(grid, point);
        solutions[i] = solution < 0 ? 0 : solution; 
    }
    
    int ret = 0;
    
    for (auto solution : solutions) {
        ret += solution;
    }
    
    return ret;
}

int main() {
    int numTestCases;
    std::cin >> numTestCases;
    
    std::vector<int> solutions(numTestCases);
    
    for (auto& solution : solutions) {
        int n;
        std::cin >> n;
        
        Matrix grid(n, n);
        solution = getSolution(grid);
    }
    
    for (auto solution : solutions) {
        std::cout << solution << "\n";
    }
}