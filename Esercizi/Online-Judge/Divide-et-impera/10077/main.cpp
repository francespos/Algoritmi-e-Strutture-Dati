// Bisogna attraversare un nodo per livello, e nel livello l-esimo si fa un 
// inserimento in un vettore di dimensione 2 + l per cui, nel caso peggiore:
// T(n) = sum_{l = 1}^(log(l) + 1) (2 + l).
// Facendo qualche conto, si ottiene una complessità O(log^2 n).
#include <string>
#include <iostream>
#include <vector>

struct Fraction {
    int n, d;
};

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return {lhs.n + rhs.n, lhs.d + rhs.d};
}

bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n == rhs.n && lhs.d == rhs.d;
}

bool operator>(const Fraction& lhs, const Fraction& rhs) {
    if (lhs.d == 0) {
        return true;
    }
    
    if (rhs.d == 0) {
        return false;
    }
    
    return static_cast<float>(lhs.n) / lhs.d > 
        static_cast<float>(rhs.n) / rhs.d;
}

int addBranch(std::vector<Fraction>& fractions, Fraction fraction) {
    int i = 0;
    
    while (fraction > fractions[i]) {
        ++i;
    }
    
    if (fraction == fractions[i]) {
        return -1;
    }
    
    fractions.insert(fractions.begin() + i, fractions[i - 1] + fractions[i]);
    
    return i;
}

void setSternBrocotRepresentation(std::string& representation, 
    std::vector<Fraction>& fractions, const Fraction& fraction, int oldPos) 
{
    int pos = addBranch(fractions, fraction);
    
    if (pos == -1) {
        return;
    }
    
    if (pos <= oldPos) {
        representation.append("L");
    } else {
        representation.append("R");
    }
    
    setSternBrocotRepresentation(representation, fractions, fraction, pos);
}

std::string getSternBrocotRepresentation(std::vector<Fraction>& fractions, 
    const Fraction& fraction)
{
    std::string representation("");
    setSternBrocotRepresentation(representation, fractions, fraction, 1);
    return representation;
}

int main() {
    std::vector<Fraction> fractions{{0, 1}, {1, 1}, {1, 0}};
    std::vector<std::string> representations;
    
    while (true) {
        int n;
        std::cin >> n;
        
        int d;
        std::cin >> d;
        
        if (n == 1 && d == 1) {
            break;
        }
        
        representations.push_back(getSternBrocotRepresentation(fractions, 
            {n, d}));
    }

    for (const auto& representation : representations) {
        std::cout << representation << "\n";
    }
}