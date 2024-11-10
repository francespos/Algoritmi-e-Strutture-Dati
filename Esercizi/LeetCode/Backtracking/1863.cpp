// Complessita': O(2^n)

#include <deque>
#include <vector>

using Subset = std::deque<bool>;

Subset getCandidates() {
    return Subset{false, true};
}

bool isASolution(const Subset& subset, int solutionLenght) {
    return subset.size() == solutionLenght;
}

void backtrack(Subset& subset, std::vector<Subset>& subsets,
    int solutionLenght) 
{
    if (isASolution(subset, solutionLenght)) {
        subsets.push_back(subset);
        return;
    }

    auto candidates = getCandidates();

    for (const auto& candidate : candidates) {
        subset.push_back(candidate);
        backtrack(subset, subsets, solutionLenght);
        subset.pop_back();
    }
}

std::vector<int> convertToVector(const Subset& subset, 
    const std::vector<int>& set) 
{
    std::vector<int> ret{};

    for (int i = 0; i < subset.size(); ++i) {
        if (subset[i]) {
            ret.push_back(set[i]);
        }
    }

    return ret;
}

int getXorTotal(const std::vector<int>& set) {
    int ret = 0;

    for (const auto& elem : set) {
        ret ^= elem;
    }

    return ret;
}

int getXorTotalSum(const std::vector<Subset>& subsets, 
    const std::vector<int>& set) 
{
    int ret = 0;

    for (const auto& subset : subsets) {
        ret += getXorTotal(convertToVector(subset, set));
    }

    return ret;
}

int getXorTotalSum(const std::vector<int>& set) {
    Subset subset{};
    std::vector<Subset> subsets{};
    int solutionLenght = set.size();

    backtrack(subset, subsets, solutionLenght);
    return getXorTotalSum(subsets, set);
}

class Solution {
public:
    int subsetXORSum(const std::vector<int>& nums) {
        return getXorTotalSum(nums);   
    }
};