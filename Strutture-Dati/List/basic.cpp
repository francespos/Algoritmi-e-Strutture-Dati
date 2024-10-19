#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class List {
public:
    struct Node {
        T value;
        std::shared_ptr<Node> prev, next;
        
        Node(const T& value) noexcept 
            : value(value), prev(nullptr), next(nullptr) {}
    };
    
    List() noexcept : m_head(nullptr) {}
    
    int getLength() const noexcept {
        int length = 0;
        
        for (auto node = m_head; node != nullptr; node = node->next) {
            ++length;
        }
        
        return length;
    }
    
    std::shared_ptr<Node> getHead() noexcept {
        return m_head;
    }
    
    std::shared_ptr<Node> operator[](int pos) {
        auto node = m_head;
        int i = 0;
        
        while (node != nullptr && i < pos) {
            node = node->next;
            ++i;
        }
        
        return node;
    }
    
    std::shared_ptr<Node> get(int pos) {
        if (pos >= getLength()) {
            throw std::out_of_range("index is too big.");
        }
        
        return operator[](pos);
    }

    std::shared_ptr<Node> find(T value) noexcept {
        auto node = m_head;

        while (node != nullptr && node->value != value) {
            node = node->next;
        }

        return node;
    }
    
    void insert(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        node->next = m_head;

        if (m_head != nullptr) {
            m_head->prev = node;
        }
        
        m_head = node;
    }
    
    void remove(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        if (node->prev == nullptr) {
            m_head = node->next;
        } else {
            node->prev->next = node->next;
        }
        
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
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
        << "Value of head: " << l.getHead()->value << "\n\n"; 
    
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    auto node2 = std::make_shared<List<int>::Node>(2);
    
    l.insert(node2);
    std::cout << "Node with value 2 inserted.\n"
        << "Value of head: " << l.getHead()->value << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    auto node3 = std::make_shared<List<int>::Node>(3);
    
    l.insert(node3);
    std::cout << "Node with value 3 inserted.\n"
        << "Value of head: " << l.getHead()->value << "\n\n"; 
        
    std::cout << "List length: " << l.getLength() << "\n\n";
    
    std::cout << "List = [ ";
    for (int i = 0; i < 3; ++i) {
        std::cout << l[i]->value << " ";
    }
    std::cout << "]\n\n";
    
    try {
        std::cout << "List fourth element: " << l.get(3)->value << "\n\n";
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
    for (int i = 0; i < 2; ++i) {
        std::cout << l[i]->value << " ";
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