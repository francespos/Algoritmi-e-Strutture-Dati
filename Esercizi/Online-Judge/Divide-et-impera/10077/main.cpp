/*
Input:
5 7
878 323
1 1
Output:
LRRL
RRLRRLRLLLLRLRRR
Complessita': la complessita', supposta costante la 
compelssita' ammortizzata dell'append di std::string
e' O(log n)
*/
#include <string>
#include <iostream>
#include <vector>

struct Fraction {
    int n, d;
};

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction{lhs.n + rhs.n, lhs.d + rhs.d};
}

bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n == rhs.n && lhs.d == rhs.d;
}

bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n * rhs.d - rhs.n * lhs.d < 0;
}

void setRepresentation(std::string& representation,
    const Fraction& left, const Fraction& target, const Fraction& right) 
{
    auto mid = left + right;
    
    if (target == mid) {
        return;
    }
    
    if (target < mid) {
        representation.append("L");
        setRepresentation(representation, left, target, mid);
    } else {
        representation.append("R");
        setRepresentation(representation, mid, target, right);
    }
}

std::string getRepresentation(const Fraction& target) {
    std::string representation("");
    
    setRepresentation(representation, 
        Fraction{0, 1}, target, Fraction{1, 0});
        
    return representation;
}

int main() {
    std::vector<std::string> representations;
    
    while (true) {
        int n;
        std::cin >> n;
        
        int d;
        std::cin >> d;
        
        if (n == 1 && d == 1) {
            break;
        }
        
        representations.push_back(getRepresentation(Fraction{n, d}));
    }

    for (const auto& representation : representations) {
        std::cout << representation << "\n";
    }
}