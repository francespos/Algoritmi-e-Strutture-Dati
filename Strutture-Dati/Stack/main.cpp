#include <array>
#include <stdexcept>
#include <iostream>

template <typename T, int N>
class Stack {
public:
    Stack() : m_items{}, m_topPos(-1) {}

    Stack(std::initializer_list<T> items) {
        if (items.size() > N) {
            throw std::out_of_range("size of items > size of stack.");
        }
    
        int i = 0;
        
        for (auto it = items.begin();
            it != items.end() && i < N; ++it) 
        {
            m_items[i++] = *it; 
        }
        
        m_topPos = i - 1;
    }
    
    bool isEmpty() noexcept { return m_topPos == -1; }
    
    std::size_t getLength() noexcept { return m_topPos + 1; }
    std::size_t getMaxLength() noexcept { return N; }
    
    T& top() {
        return m_items[m_topPos];
    }
    
    void push(const T& item) {
        if (m_topPos == N - 1) {
            throw std::out_of_range("overflow");
        }
        
        m_items[++m_topPos] = item;
    }
    
    [[nodiscard]] T& pop() {
        if (m_topPos == -1) {
            throw std::out_of_range("underflow");
        }
        
        return m_items[m_topPos--];
    }
private:
    std::array<T, N> m_items;
    int m_topPos;
};

int main() {
    Stack<int, 3> s1{};
    
    try {
        std::cout << s1.pop() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    s1.push(1);
    std::cout << "top: " << s1.top() << "\n";
    
    s1.push(2);
    std::cout << "top: " << s1.top() << "\n";
    
    s1.push(3);
    std::cout << "top: " << s1.top() << "\n";
    
    try {
        s1.push(4);
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    std::cout << "Popped item: " << s1.pop() << "\n";
    std::cout << "Popped item: " << s1.pop() << "\n";
    std::cout << "Popped item: " << s1.pop() << "\n";
    
    try {
        std::cout << "Popped item: " << s1.pop() << "\n";        
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    Stack<int, 3> s2{1, 2};
    
    std::cout <<"Popped item: " << s2.pop();
}