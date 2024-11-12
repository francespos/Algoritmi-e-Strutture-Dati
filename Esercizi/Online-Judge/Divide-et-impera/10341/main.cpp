/*
Input:
0 0 0 0 -2 1
1 0 0 0 -1 2
1 -1 1 -1 -1 1
Output:
0.7071
No solution
0.7554
Complessita': O(n), dove n e' il massimo numero di iterazioni nella funzione
solve(), che dipende dalla precisione della funzione.
*/
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

class OptionalDouble {
private:
    double m_value;
    bool m_assigned;
public:    
    OptionalDouble() : m_assigned(false) {}
    OptionalDouble(double value) : m_value(value), m_assigned(true) {}
    
    double getValue() const {
        return m_value;
    }
    
    bool hasValue() const {
        return m_assigned;
    }
};

double getFunctionValue(int p, int q, int r, int s, int t, int u, double x) {
    double ret = 0.0;
    
    ret += p * std::exp(-x);
    ret += q * std::sin(x);
    ret += r * std::cos(x);
    ret += s * std::tan(x);
    ret += t * x * x;
    ret += u;
    
    return ret;
}

OptionalDouble solve(int p, int q, int r, int s, int t, int u, double precision) 
{
    // Osserviamo che la funzione f si scrive come somma di funzioni decrescenti
    // o costanti in [0, 1], quindi anch'essa e' una funzione decrescente 
    // o costante in [0, 1].
    // Condizione necessaria e sufficiente affinche' f ammetta degli zeri è che 
    // essa assuma valori opposti ai suoi estremi.
    // In tal caso, lo zero di f si può ricavare mediante il metodo di 
    // bisezione.
    auto valueIn0 = getFunctionValue(p, q, r, s, t, u, 0.0);
    auto valueIn1 = getFunctionValue(p, q, r, s, t, u, 1.0);
    
    if (valueIn0 * valueIn1 > 0.0) {
        return OptionalDouble();
    };
    
    auto a = 0.0;
    auto b = 1.0;
    
    while (b - a > precision) {
        auto c = (a + b) / 2.0;
        auto value = getFunctionValue(p, q, r, s, t, u, c);
        
        if (value > 0.0) {
            a = c;
        } else {
            b = c;
        }
    }
    
    return OptionalDouble(a);
}

std::ostream& operator<<(std::ostream& out, const OptionalDouble& x) {
    if (x.hasValue()) {
        return out << x.getValue();
    }
    
    return out << "No solution";
}

int main() {
    double precision = 1e-7;
    std::cout << std::fixed << std::setprecision(4);
    
    std::vector<OptionalDouble> results{};
    int p, q, r, s, t, u;
    
    while (std::cin >> p >> q >> r >> s >> t >> u) {
        results.push_back(solve(p, q, r, s, t, u, precision));
    }
    
    for (const auto& result : results) {
        std::cout << result << "\n";    
    }
}