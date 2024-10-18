#include <array>
#include <stdexcept>
#include <iostream>

template<typename T, int N>
class Queue {
public:
    Queue() noexcept 
        : m_items{}, m_head(0), m_tail(0) {}
        
    bool isEmpty() const noexcept {
        return m_head == m_tail;
    }
    
    bool isFull() const noexcept {
        return m_head == (m_tail + 1) % N;
    }
    
    int getLength() const noexcept {
        return m_tail - m_head; 
    }
    
    constexpr int getMaxLength() const noexcept {
        return N; 
    }
    
    T& getFront() {
        if (isEmpty()) {
            throw std::out_of_range("queue is empty.");
        }
        
        return m_items[m_head];
    }
    
    T& getBack() {
        if (isEmpty()) {
            throw std::out_of_range("queue is empty.");
        }
        
        return m_items[m_tail];
    }
    
    void enqueue(const T& item) {
        if (isFull()) {
            throw std::out_of_range("queue is full.");
        }
       
        m_items[m_tail] = item; 
        m_tail = (m_tail + 1) % N;
    }
    
    [[nodiscard]] T& deque() {
        if (isEmpty()) {
            throw std::out_of_range("queue is empty.");
        }
        
        auto& item = m_items[m_head];
        m_head = (m_head + 1) % N;
        
        return item;
    }
private:
    std::array<T, N> m_items;
    int m_head;
    int m_tail;
};

int main() {
    Queue<int, 4> q;
    
    try {
        std::cout << "Item dequeued: " << q.deque()
            << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() 
            << std::endl;
    }

    std::cout << "Queue length: " << q.getLength()
        << "\n";
        
    try {
        for (int i = 0; i < 4; ++i) {
            q.enqueue(i);
            std::cout << "Item " << i << " enqueued.\n";
            std::cout << "Queue length: " << q.getLength()
                << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() 
            << std::endl;
    }
    
    std::cout << "Queue length: " << q.getLength()
        << "\n";
    
    try {
        for (int i = 0; i < 4; ++i) {
            std::cout << "Item dequed: "<< q.deque() 
                << ".\n";
        }
        
        std::cout << "Queue length: " << q.getLength()
            << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() 
            << std::endl;
    }
    
    std::cout << "Queue length: " << q.getLength()
        << "\n";
}