// Complessita': O(n!)
#include <vector>

using VecOfInt = std::vector<int>;
using VecOfVecOfInt = std::vector<std::vector<int>>;
using VecOfBool = std::deque<bool>;

bool isASolution(const VecOfInt& positions, 
    const VecOfInt& numbers) 
{
    return positions.size() == numbers.size();     
}

void backtrack(VecOfInt& positions,  
    VecOfVecOfInt& solutions,
    const VecOfInt& numbers, 
    VecOfBool& used)
{
    if (isASolution(positions, numbers)) {
        solutions.push_back(positions);
        return;
    }

    for (int i = 0; i < numbers.size(); ++i) {
        if (used[i]) {
            continue;
        }

        used[i] = true;
        positions.push_back(numbers[i]);
        
        backtrack(positions, solutions,
            numbers, used);

        positions.pop_back();
        used[i] = false;
    }
}

VecOfVecOfInt getAllPermutations(VecOfInt& numbers) {
    VecOfInt positions{};
    VecOfVecOfInt solutions{};
    VecOfBool used(numbers.size(), false);

    backtrack(positions,solutions, numbers, used);
    return solutions;
}

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return getAllPermutations(nums);
    }
};