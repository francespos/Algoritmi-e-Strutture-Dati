// Si consideri un labirinto 4x4 con la seguente configurazione:
// [1, 0, 0, 0]
// [1, 1, 0, 1] 
// [0, 1, 0, 0]
// [1, 1, 1, 1]
// Una cella e' percorribile se vale 1, non percorribile se vale 0.
// Trovare un percorso dalla posizione (0, 0) alla posizione (3, 3) e stampare
// la sequenza di posizioni che lo compone, supposto che ci si possa muovere
// solo verso destra e verso il basso.
// Complessita': O(2^n^2), dove n e' il numero di righe/colonne del labirinto.
#include <vector>
#include <initializer_list>
#include <iostream>

class Matrix {
private:
    std::vector<int> m_entries;
    int m_numCols;
public:
    Matrix(std::initializer_list<int> entries, int numCols) 
        : m_entries{entries}, m_numCols(numCols) {}
    
    int operator()(int i, int j) const {
        return m_entries[i *  m_numCols + j];
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

bool isASolution(const Point& pos) {
    return pos == Point{3, 3};
}

bool isWalkable(const Matrix& grid, const Point& pos) {
    return grid(pos.x, pos.y) == 1;
}

void pushBackIfWalkable(std::vector<Point>& candidates, const Matrix& grid, 
    const Point& pos)
{
    if (isWalkable(grid, pos)) {
        candidates.push_back(pos);
    }
}

std::vector<Point> getCandidates(const Matrix& grid, const Point& pos) {
    std::vector<Point> candidates{};
    
    if (pos.x < 3 && pos.y == 3) {
        pushBackIfWalkable(candidates, grid, pos + Point{1, 0});
    } else if (pos.x == 3 && pos.y < 3) {
        pushBackIfWalkable(candidates, grid, pos + Point{0, 1});
    } else {
        pushBackIfWalkable(candidates, grid, pos + Point{0, 1});
        pushBackIfWalkable(candidates, grid, pos + Point{1, 0});
    }
    
    return candidates;
}

void processSolution(std::vector<Point>& positions) {
    for (const auto& pos : positions) {
        std::cout << pos << "\n";
    }    
}

void backtrack(const Matrix& grid, const Point& pos,
    std::vector<Point>& positions) 
{
    if (isASolution(pos)) {
        processSolution(positions);
    } else {
        auto candidates = getCandidates(grid, pos);
        
        for (const auto& candidate : candidates) {
            positions.push_back(candidate);
            backtrack(grid, candidate, positions);
            positions.pop_back();
        }
    }
}

void printSolution(const Matrix& grid) {
    Point pos{0, 0};
    std::vector<Point> positions{pos};
    backtrack(grid, pos, positions);
}

int main() {
    Matrix grid({
        1, 0, 0, 0, 
        1, 1, 0, 1, 
        0, 1, 0, 0, 
        1, 1, 1, 1}, 
        4);
        
    printSolution(grid);
}