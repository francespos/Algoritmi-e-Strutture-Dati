// Incompleta e non testata

#include <array>
#include <stdexcept>

template<typename T, int N>
class Queue {
    Queue() noexcept 
        : m_values{}, head(0), tail(0) {}
        
    bool isEmpty() noexcept {
        return m_head == m_tail;
    }
    
    bool isFull() noexcept {
        return m_head == m_tail + 1;
    }
    
    int getLength() noexcept { return m_tail - m_head; }
    int getMaxLength() noexcept { return N; }
    
    void enqueue(const T& item) {
        if (isFull()) {
            throw std::out:of_memory("Queue is full.");
        }
       
        m_items[m_tail++] = item; 
    }
    
    T& deque() {
        if (isEmpty()) {
            throw std::out_of_memory("Queue is empty");
        }
        
        return m_items[m_head--];
    }
private:
    std::array<T, N> m_values;
    int m_head;
    int m_tail;
};