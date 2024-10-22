#include <array>
#include <iostream>

template<typename T, std::size_t N> requires (N != 0)
class Stack {
public:
    Stack() noexcept : m_items{}, m_topPos(0), m_empty(true) {}
    
    constexpr std::size_t getMaxLength() const noexcept {
        return N;
    }
    
    std::size_t getLength() const noexcept {
        if (m_empty) { 
            return 0;
        }
        
        return m_topPos;
    }

    bool isEmpty() const noexcept {
        return m_empty; 
    }
    
    bool isFull() const noexcept {
        return m_topPos == N;
    }
    
    T& getTop() {
        if (isEmpty()) {
            throw std::out_of_range("stack is empty.");
        }
        return m_items[m_topPos - 1];
    }
    
    void push(const T& item) {
        if (isFull()) {
            throw std::out_of_range("stack is full.");
        }
        
        m_items[m_topPos++] = item;
        m_empty = false;
    }
    
    [[nodiscard]] T& pop() {
        if (isEmpty()) {
            throw std::out_of_range("stack is empty.");
        }
        
        --m_topPos;
        
        if (m_topPos == 0) {
            m_empty = true;
        }
        
        return m_items[m_topPos];
    }
private:
    std::array<T, N> m_items;
    std::size_t m_topPos;
    bool m_empty;
};

int main() {
    Stack<int, 3> s;
    
    std::cout << "Stack length: " << s.getLength() << "\nStack max length: " 
        << s.getMaxLength() << "\n\n";
    
    try {
        std::cout << "Popped item: " << s.pop() << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        for (int i = 0; i < 4; ++i) {
            s.push(i);
            std::cout << "Item " << i << " pushed.\n"
                << "Item on top of stack is: " << s.getTop() 
                << "\nStack length: " << s.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        for (std::size_t i = 0; i < 4; ++i) {
            std::cout << "Popped item: " << s.pop() << "\nStack length: " 
                << s.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}