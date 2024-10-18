#include <array>
#include <iostream>

template <typename T, int N>
class Stack {
public:
    Stack() noexcept : m_items{}, m_topPos(-1) {}

    bool isEmpty() noexcept { return m_topPos == -1; }
    bool isFull() noexcept { return m_topPos == N - 1; }
    
    int getLength() noexcept { return m_topPos + 1; }
    int getMaxLength() noexcept { return N; }
    
    T& top() {
        if (isEmpty()) {
            throw std::out_of_range("stack is empty.");
        }
        return m_items[m_topPos];
    }
    
    void push(const T& item) {
        if (isFull()) {
            throw std::out_of_range("stack is full.");
        }
        
        m_items[++m_topPos] = item;
    }
    
    [[nodiscard]] T& pop() {
        if (isEmpty()) {
            throw std::out_of_range("stack is empty.");
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
}