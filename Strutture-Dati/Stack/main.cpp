#include <array>
#include <iostream>

template<typename T, int N> requires (N > 0)
class Stack {
public:
    Stack() noexcept : m_items{}, m_topPos(-1) {}
    
    constexpr int getMaxLength() const noexcept {
        return N;
    }
    
    int getLength() const noexcept {
        return m_topPos + 1;
    }

    bool isEmpty() const noexcept {
        return m_topPos == -1; 
    }
    
    bool isFull() const noexcept {
        return m_topPos == N - 1;
    }
    
    T& getTop() {
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
    Stack<int, 3> s;
    
    std::cout << "Stack length: " << s.getLength() 
        << "\nStack max length: " << s.getMaxLength()
        << "\n\n";
    
    try {
        std::cout << "Popped item: " << s.pop() << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        for (int i = 0; i < 4; ++i) {
            s.push(i);
            std::cout << "Item " << i << " pushed.\n"
                << "Item on top of stack is: " 
                << s.getTop() << "\n";
                
            std::cout << "Stack length: " << s.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        for (int i = 0; i < 4; ++i) {
            std::cout << "Popped item: " << s.pop() << "\n";    
            std::cout << "Stack length: " << s.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}