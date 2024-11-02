#include <iostream>
#include <memory>

namespace Dsa {
    template<typename T>
    class Stack {
    private:
        std::unique_ptr<T[]> m_items;
        std::size_t m_maxLength;
        
        std::size_t m_topPos;
        bool m_empty;
    public:
        class Iterator {
        private:
            T* m_ptr;
        public:
            explicit constexpr Iterator(T* ptr) noexcept : m_ptr(ptr) {}
        
            constexpr T& operator*() noexcept { 
                return *m_ptr; 
            }
        
            constexpr Iterator& operator++() noexcept {
                ++m_ptr;
                return *this;
            }
        
            constexpr bool operator!=(const Iterator& other) const noexcept {
                return m_ptr != other.m_ptr;
            }
        
            constexpr bool operator==(const Iterator& other) const noexcept {
                return m_ptr == other.m_ptr;
            }
        };
        
        class ConstIterator {
        private:
            const T* m_ptr;
        public:
            explicit constexpr ConstIterator(const T* ptr) noexcept : m_ptr(ptr)
            {}
        
            constexpr const T& operator*() const noexcept { 
                return *m_ptr; 
            }
        
            constexpr ConstIterator& operator++() noexcept {
                ++m_ptr;
                return *this;
            }
        
            constexpr bool operator!=(const Iterator& other) const noexcept {
                return m_ptr != other.m_ptr;
            }
        
            constexpr bool operator==(const Iterator& other) const noexcept {
                return m_ptr == other.m_ptr;
            }
        };
    
        constexpr explicit Stack(std::size_t maxLength) 
            : m_items(std::make_unique<T[]>(maxLength)), m_maxLength(maxLength)
            , m_topPos(0), m_empty(true) {}
            
        constexpr std::size_t getMaxLength() const noexcept {
            return m_maxLength;
        }
        
        constexpr std::size_t getLength() const noexcept {
            if (m_empty) { 
                return 0;
            }
            
            return m_topPos;
        }
        
        constexpr Iterator begin() { 
            return Iterator(m_items.get()); 
        }
        
        constexpr ConstIterator begin() const { 
            return Iterator(m_items.get()); 
        }
        
        constexpr Iterator end() { 
            return Iterator(m_items.get() + m_topPos); 
        }
        
        constexpr ConstIterator end() const { 
            return Iterator(m_items.get() + m_topPos); 
        }
    
        constexpr bool isEmpty() const noexcept {
            return m_empty; 
        }
        
        constexpr bool isFull() const noexcept {
            return m_topPos == m_maxLength;
        }
        
        constexpr T& getTop() {
            if (Stack::isEmpty()) {
                throw std::out_of_range("stack is empty");
            }
            return m_items[m_topPos - 1];
        }
        
        constexpr void push(const T& item) {
            if (Stack::isFull()) {
                throw std::out_of_range("stack is full");
            }
            
            m_items[m_topPos++] = item;
            m_empty = false;
        }
        
        [[nodiscard]] constexpr T& pop() {
            if (Stack::isEmpty()) {
                throw std::out_of_range("stack is empty");
            }
            
            --m_topPos;
            
            if (m_topPos == 0) {
                m_empty = true;
            }
            
            return m_items[m_topPos];
        }
    };
}

int main() {
    Dsa::Stack<int> s(3);
    
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
    
    std::cout << "Verifico se funzionano gli iteratori; elementi nello stack: ";
    
    for (auto elem : s) {
        std::cout << elem << " ";
    }
    
    std::cout << "\n\n";
    
    try {
        for (std::size_t i = 0; i < 4; ++i) {
            std::cout << "Popped item: " << s.pop() << "\nStack length: " 
                << s.getLength() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}