#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class Queue {
private:
    std::unique_ptr<T[]> m_items;
    std::size_t m_maxLength;
    
    std::size_t m_head;
    std::size_t m_tail;
public:
    constexpr explicit Queue(std::size_t maxLength) noexcept 
        : m_items(std::make_unique<T[]>(maxLength)), m_maxLength(maxLength)
        , m_head(0), m_tail(0) {}
        
    constexpr std::size_t getMaxLength() const noexcept {
        return m_maxLength; 
    }
        
    constexpr std::size_t getLength() const noexcept {
        if (m_tail >= m_head) {
            return m_tail - m_head;
        } else {
            return m_maxLength - (m_head - m_tail);
        }
    }
        
    constexpr bool isEmpty() const noexcept {
        return m_head == m_tail;
    }
    
    constexpr bool isFull() const noexcept {
        return m_head == (m_tail + 1) % m_maxLength;
    }
    
    constexpr void enqueue(const T& item) {
        if (isFull()) {
            throw std::out_of_range("queue is full");
        }
       
        m_items[m_tail] = item; 
        m_tail = (m_tail + 1) % m_maxLength;
    }
    
    [[nodiscard]] constexpr T& dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("queue is empty");
        }
        
        auto& item = m_items[m_head];
        m_head = (m_head + 1) % m_maxLength;
        
        return item;
    }
};

int main() {
    Queue<int> q(4);
    
    try {
        std::cout << "Item dequeued: " << q.dequeue() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }

    std::cout << "Queue length: " << q.getLength() << "\nQueue max length: " 
        << q.getMaxLength() << "\n\n";
        
    try {
        for (int i = 0; i < 4; ++i) {
            q.enqueue(i);
            std::cout << "Item " << i << " enqueued.\n" << "Queue length: " 
                << q.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        for (std::size_t i = 0; i < 4; ++i) {
            std::cout << "Item dequeued: " << q.dequeue() << ".\n"
                << "Queue length: " << q.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
}