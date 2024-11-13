// Complessita': O(m * n * 4^l)
#include <string>

using VecVecChar = std::vector<std::vector<char>>;

class Matrix {
private:
    std::vector<int> m_entries; 
    int m_numCols;
public:
    Matrix(int m, int n) : m_entries(m * n, 0), m_numCols(n) {}

    int getNumRows() const {
        return m_entries.size() / m_numCols;
    }

    int getNumCols() const {
        return m_numCols;
    }
    
    int operator()(int i, int j) const {
        return m_entries[i * m_numCols + j];
    }

    int& operator()(int i, int j) {
        return m_entries[i * m_numCols + j];
    }
};

struct Point {
    int x, y;
};

Point operator+(const Point& p1, const Point& p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}

bool isAValidPos(const Point& pos, const Matrix& matrix) {
    return pos.x >= 0 && pos.y >= 0   
        && pos.x < matrix.getNumRows() && pos.y < matrix.getNumCols()
        && matrix(pos.x, pos.y) == 0;
}

void pushBackIfValid(std::vector<Point>& points, const Point& pos, const Matrix& matrix) {
    if (isAValidPos(pos, matrix)) {
        points.push_back(pos);
    }
}

std::vector<Point> getCandidates(const Point& pos, const Matrix& matrix) {
    std::vector<Point> candidates{};

    // pushBackIfValid(candidates, pos + Point{-1, -1}, matrix);
    pushBackIfValid(candidates, pos + Point{0, -1}, matrix);
    // pushBackIfValid(candidates, pos + Point{1, -1}, matrix);
    pushBackIfValid(candidates, pos + Point{-1, 0}, matrix);
    pushBackIfValid(candidates, pos + Point{1, 0}, matrix);
    // pushBackIfValid(candidates, pos + Point{-1, 1}, matrix);
    pushBackIfValid(candidates, pos + Point{0, 1}, matrix);
    // pushBackIfValid(candidates, pos + Point{1, 1}, matrix);

    return candidates;
}

bool isASolution(const std::vector<Point>& positions, const std::string& word) {
    return positions.size() == word.size();
}

bool backtrack(const Point& pos, std::vector<Point>& positions, Matrix& posMatrix, 
    const VecVecChar& letterMatrix, const std::string& word) 
{
    // std::cout << pos.x << " " << pos.y << "\n";
    // std::cout << "Positions size: " << positions.size() << "\n";

    if (isASolution(positions, word)) {
        /*
        for (const auto& elem : positions) {
            auto x = elem.x;
            auto y = elem.y;

            std::cout << letterMatrix[x][y];
        }

        std::cout << "\n";
        */

        return true;
    }

    auto ret = false;
    auto candidates = getCandidates(pos, posMatrix);

    // std::cout << word[positions.size()] << "\n";
    // std::cout << "Num candidati: " << candidates.size() << "\n";

    for (auto& candidate : candidates) {
        auto x = candidate.x;
        auto y = candidate.y;

        // std::cout << x << " " << y << "\n";
        // std::cout << letterMatrix[x][y] << "\n";

        if (letterMatrix[x][y] == word[positions.size()]) {
            positions.push_back(candidate);
            posMatrix(x, y) = 1;

            ret = backtrack(candidate, positions, posMatrix, letterMatrix, word);

            posMatrix(x, y) = 0;
            positions.pop_back();
        }

        if (ret) {
            return ret;
        }
    }

    return ret;
}

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        auto numRows = board.size();
        auto numCols = board[0].size();

        std::vector<Point> positions{};
        Matrix posMatrix(numRows, numCols);

        auto ret = false;

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                Point pos{i, j};
                positions.push_back(pos);
                posMatrix(i, j) = 1;

                if (word[0] == board[i][j]) {
                    // std::cout << board[i][j] << "\n";
                    ret |= backtrack(pos, positions, posMatrix, board, word);
                }

                posMatrix(i, j) = 0;
                positions.pop_back();

                if (ret) {
                    return ret;
                }
            }
        }

        return ret;
    }
};