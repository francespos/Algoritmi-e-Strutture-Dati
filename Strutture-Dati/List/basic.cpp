#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class List {
private:
    class Node {
    private:
        T m_value;
        std::shared_ptr<Node> m_prev, m_next;
    public:
        friend class List;
        
        constexpr explicit Node(const T& value) noexcept 
            : m_value(value), m_prev(nullptr), m_next(nullptr) {}
            
        constexpr const T& getValue() const noexcept {
            return m_value;
        }
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

    constexpr explicit List() noexcept : m_head(nullptr) {}
    
    constexpr std::size_t getLength() const noexcept {
        std::size_t length = 0;
        
        for (auto node = m_head; node != nullptr; node = node->m_next) {
            ++length;
        }
        
        return length;
    }

    constexpr Iterator begin() noexcept {
        return Iterator(m_head.get());
    }
    
    constexpr Iterator end() noexcept {
        return Iterator(nullptr);
    }
    
    constexpr ConstIterator begin() const noexcept {
        return ConstIterator(m_head.get());
    }
    
    constexpr ConstIterator end() const noexcept {
        return ConstIterator(nullptr);
    }

    constexpr const T& getHead() const {
        return m_head->m_value;
    }
    
    constexpr const T& operator[](std::size_t pos) const {
        auto node = m_head;
        std::size_t i = 0;
        
        while (node != nullptr && i < pos) {
            node = node->m_next;
            ++i;
        }
        
        return node->m_value;
    }
    
    constexpr const T& get(std::size_t pos) const {
        if (m_head == nullptr) {
            throw std::runtime_error("list is empty");
        }
        
        if (pos >= List::getLength()) {
            throw std::out_of_range("index is too big");
        }
        
        return operator[](pos);
    }

    constexpr ConstIterator find(const T& value) const {
        auto node = m_head;

        while (node != nullptr && node->m_value != value) {
            node = node->m_next;
        }

        return ConstIterator(node.get());
    }
    
    constexpr void insert(const T& value) noexcept {
        auto node = std::make_shared<Node>(value);
        
        node->m_next = m_head;

        if (m_head != nullptr) {
            m_head->m_prev = node;
        }
        
        m_head = node;
    }
    
    constexpr void remove(const T& value) noexcept {
        auto node = m_head;
        
        while (node != nullptr && node->m_value != value) {
            node = node->m_next;
        }
        
        if (node == nullptr) {
            return;
        }
        
        if (node->m_prev == nullptr) {
            m_head = node->m_next;
        } else {
            node->m_prev->m_next = node->m_next;
        }
        
        if (node->m_next != nullptr) {
            node->m_next->m_prev = node->m_prev;
        }
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