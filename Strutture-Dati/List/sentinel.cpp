#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class List {
public:
    class Node {
    public:
        friend class List;
        
        Node(const T& value) noexcept 
            : m_value(value), m_prev(nullptr), m_next(nullptr) {}
            
        const T& getValue() const noexcept {
            return m_value;
        }
    private:
        T m_value;
        std::shared_ptr<Node> m_prev, m_next;
    };
    
    List() {
        std::shared_ptr<Node> node = std::make_shared<Node>(0);
        node->m_prev = node->m_next = node;
        m_head = node;
    }
    
    std::size_t getLength() const noexcept {
        std::size_t length = 0;
        
        for (auto node = m_head->m_next; node != m_head; node = node->m_next) {
            ++length;
        }
        
        return length;
    }
    
    std::shared_ptr<const Node> getHead() const noexcept {
        auto node = m_head->m_next;
        
        if (node == m_head) {
            return nullptr;
        }
        
        return std::const_pointer_cast<const Node>(node);
    }
    
    std::shared_ptr<const Node> operator[](std::size_t pos) const noexcept {
        auto node = m_head->m_next;
        std::size_t i = 0;
        
        while (node != m_head && i < pos) {
            node = node->m_next;
            ++i;
        }
        
        if (node == m_head && i == pos) {
            return nullptr;
        }
        
        return std::const_pointer_cast<const Node>(node);
    }
    
    std::shared_ptr<const Node> get(std::size_t pos) const {
        auto node = operator[](pos);
        
        if (node == nullptr && m_head != m_head->m_next) {
            throw std::out_of_range("index is too big.");
        }
        
        return node;
    }

    std::shared_ptr<const Node> find(const T& value) const {
        auto node = m_head->m_next;

        while (node != m_head && node->m_value != value) {
            node = node->m_next;
        }
        
        if (node == m_head) {
            return nullptr;
        }

        return std::const_pointer_cast<const Node>(node);
    }
    
    void insert(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        node->m_next = m_head->m_next;
        m_head->m_next->m_prev = node;
        node->m_prev = m_head;
        m_head->m_next = node;
    }
    
    void remove(std::shared_ptr<const Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
    }
private:
    std::shared_ptr<Node> m_head;
};

int main() {
    List<int> l;
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    auto node1 = std::make_shared<List<int>::Node>(1);
    
    l.insert(node1);
    std::cout << "Node with value 1 inserted.\n"
        << "Value of head: " << l.getHead()->getValue() << "\n\n"; 
    
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    auto node2 = std::make_shared<List<int>::Node>(2);
    
    l.insert(node2);
    std::cout << "Node with value 2 inserted.\n"
        << "Value of head: " << l.getHead()->getValue() << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    auto node3 = std::make_shared<List<int>::Node>(3);
    
    l.insert(node3);
    std::cout << "Node with value 3 inserted.\n"
        << "Value of head: " << l.getHead()->getValue() << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    std::cout << "List = [ ";
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << l[i]->getValue() << " ";
    }
    std::cout << "]\n\n";
    
    try {
        std::cout << "List fourth element: " << l.get(3)->getValue() << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    std::cout << "Find node with value 2.\n";
    if (l.find(2) != nullptr) {
        std::cout << "Node found.\n\n";
    }
    
    l.remove(node2);
    std::cout << "Node 2 removed.\n";
    
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    std::cout << "List = [ ";
    for (std::size_t i = 0; i < 2; ++i) {
        std::cout << l[i]->getValue() << " ";
    }
    std::cout << "]\n\n";

    std::cout << "Find node with value 2.\n";
    if (l.find(2) == nullptr) {
        std::cout << "Node not found.\n\n";
    }

    try {
        std::cout << "Inserting a nullptr.\n";
        l.insert(nullptr);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
    
    try {
        std::cout << "Removing a nullptr.\n";
        l.remove(nullptr);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
    }
}