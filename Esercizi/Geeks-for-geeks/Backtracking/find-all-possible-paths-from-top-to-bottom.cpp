//{ Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

class Matrix {
private:
    std::vector<int> m_entries;
    int m_numCols;
public:
    Matrix(int numRows, int numCols) : m_entries(numRows * numCols, 0), 
        m_numCols(numCols) {}
    
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

bool isASolution(const Matrix& grid, const Point& pos) {
    auto m = grid.getNumRows() - 1;
    auto n = grid.getNumCols() - 1;
    
    return pos == Point{m, n};
}

bool isWalkable(const Matrix& grid, const Point& pos) {
    return grid(pos.x, pos.y) == 0;
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
    
    auto m = grid.getNumRows() - 1;
    auto n = grid.getNumCols() - 1;
    
    if (pos.x < m && pos.y == n) {
        pushBackIfWalkable(candidates, grid, pos + Point{1, 0});
    } else if (pos.x == m && pos.y < n) {
        pushBackIfWalkable(candidates, grid, pos + Point{0, 1});
    } else {
        pushBackIfWalkable(candidates, grid, pos + Point{1, 0}); // Prima movimento giù
        pushBackIfWalkable(candidates, grid, pos + Point{0, 1}); // Poi movimento destra
    }
    
    return candidates;
}

void backtrack(const Matrix& grid, const Point& pos, std::vector<Point>& path,
    std::vector<std::vector<Point>>& solutions) 
{
    if (isASolution(grid, pos)) {
        solutions.push_back(path);
        return;
    } 
    
    auto candidates = getCandidates(grid, pos);
    
    for (const auto& candidate : candidates) {
        path.push_back(candidate);
        backtrack(grid, candidate, path, solutions);
        path.pop_back();
    }
}

std::vector<std::vector<Point>> getSolutions(const Matrix& grid) {
    Point point{0, 0};
    std::vector<std::vector<Point>> solutions{};
    
    std::vector<Point> path{point};
    backtrack(grid, point, path, solutions);
    
    return solutions;
}

std::vector<int> convertToVecOfInts(const Matrix& grid, 
    const std::vector<Point>& points) 
{
    std::vector<int> ret{};
    
    for (const auto& point : points) {
        ret.push_back(point.x * grid.getNumCols() + point.y + 1);
    }
    
    return ret;
}

std::vector<std::vector<int>> convertToVecOfVecOfInts(
    const Matrix& grid, 
    const std::vector<std::vector<Point>>& vecOfVecOfPoints) 
{
    std::vector<std::vector<int>> ret{};
    
    for (const auto& vecOfPoints : vecOfVecOfPoints) {
        ret.push_back(convertToVecOfInts(grid, vecOfPoints));
    }
    
    return ret;
}

std::vector<std::vector<int>> getAllPossiblePaths(int m, int n) {
    Matrix grid(m, n);
    return convertToVecOfVecOfInts(grid, getSolutions(grid));
}

class Solution {
public:
    vector<vector<int>> findAllPossiblePaths(int n, int m, 
        std::vector<std::vector<int>>& grid) 
    {
        return getAllPossiblePaths(n, m);
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> grid[i][j];
            }
        }
        Solution ob;
        auto ans = ob.findAllPossiblePaths(n, m, grid);
        for (int i = 0; i < ans.size(); i++)
        {
            for (int j = 0; j < ans[i].size(); j++)
            {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
    
cout << "~" << "\n";
}
    return 0;
}

// } Driver Code Ends