#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class List {
private:
    class Node {
    public:
        friend class List;
        
        constexpr explicit Node(const T& value) noexcept 
            : m_value(value), m_prev(nullptr), m_next(nullptr) {}
            
        constexpr const T& getValue() const noexcept {
            return m_value;
        }
    private:
        T m_value;
        std::shared_ptr<Node> m_prev, m_next;
    };

    std::shared_ptr<Node> m_head;
public:
    class Iterator {
    private:
        Node* m_ptr;
    public:
        constexpr explicit Iterator(Node* ptr) noexcept : m_ptr(ptr) {}
    
        constexpr T& operator*() noexcept { 
            return m_ptr->m_value; 
        }
    
        constexpr Iterator& operator++() noexcept {
            m_ptr = m_ptr->m_next.get();
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
        const Node* m_ptr;
    public:
        constexpr explicit ConstIterator(const Node* ptr) noexcept 
            : m_ptr(ptr) {}
    
        constexpr const T& operator*() const noexcept { 
            return m_ptr->m_value; 
        }
    
        constexpr ConstIterator& operator++() noexcept {
            m_ptr = m_ptr->m_next.get();
            return *this;
        }
    
        constexpr bool operator!=(const Iterator& other) const noexcept {
            return m_ptr != other.m_ptr;
        }
    
        constexpr bool operator==(const Iterator& other) const noexcept {
            return m_ptr == other.m_ptr;
        }
    };
    
    constexpr List() {
        std::shared_ptr<Node> node = std::make_shared<Node>(T());
        node->m_prev = node->m_next = node;
        m_head = node;
    }
    
    constexpr std::size_t getLength() const noexcept {
        std::size_t length = 0;
        
        for (auto node = m_head->m_next; node != m_head; 
            node = node->m_next) 
        {
            ++length;
        }
        
        return length;
    }
    
    constexpr Iterator begin() noexcept {
        return Iterator(m_head->m_next.get());
    }
    
    constexpr Iterator end() noexcept {
        return Iterator(m_head.get());
    }
    
    constexpr ConstIterator begin() const noexcept {
        return ConstIterator(m_head->m_next.get());
    }
    
    constexpr ConstIterator end() const noexcept {
        return ConstIterator(m_head.get());
    }
    
    constexpr const T& getHead() const {
        return m_head->m_next->m_value;
    }
    
    constexpr const T& operator[](std::size_t pos) const {
        auto node = m_head->m_next;
        std::size_t i = 0;
        
        while (node != m_head && i < pos) {
            node = node->m_next;
            ++i;
        }
        
        return node->m_value;
    }
    
    constexpr const T& get(std::size_t pos) const {
        if (pos >= getLength()) {
            throw std::out_of_range("index is too big");
        }
        
        return operator[](pos);
    }

    constexpr ConstIterator find(const T& value) const {
        auto node = m_head->m_next;

        while (node != m_head && node->m_value != value) {
            node = node->m_next;
        }
        
        return ConstIterator(node.get());
    }
    
    constexpr void insert(const T& value) {
        auto node = std::make_shared<Node>(value);
        
        node->m_next = m_head->m_next;
        m_head->m_next->m_prev = node;
        node->m_prev = m_head;
        m_head->m_next = node;
    }
    
    constexpr void remove(const T& value) {
        auto node = m_head->m_next;
        
        while (node != m_head && node->m_value != value) {
            node = node->m_next;
        }
        
        if (node == m_head) {
            return;
        }
        
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
    }
};

int main() {
    List<int> l;
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    l.insert(1);
    std::cout << "Node with value 1 inserted.\n"
        << "Value of head: " << l.getHead() << "\n\n"; 
    
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    l.insert(2);
    std::cout << "Node with value 2 inserted.\n"
        << "Value of head: " << l.getHead() << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    l.insert(3);
    std::cout << "Node with value 3 inserted.\n"
        << "Value of head: " << l.getHead() << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    std::cout << "List = [ ";
    for (auto elem : l) {
        std::cout << elem << " ";
    }
    std::cout << "]\n\n";
    
    try {
        std::cout << "List fourth element: " << l.get(3) << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    std::cout << "Find node with value 2.\n";
    std::cout << "Node = " << *l.find(2) << "\n\n";
    
    l.remove(2);
    std::cout << "Node 2 removed.\n";
    
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    std::cout << "List = [ ";
    for (auto elem : l) {
        std::cout << elem << " ";
    }
    std::cout << "]\n\n";
}