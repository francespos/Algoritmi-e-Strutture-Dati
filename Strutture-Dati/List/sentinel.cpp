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
    
    List() {
        std::shared_ptr<Node> node = std::make_shared<Node>(0);
        node->prev = node->next = node;
        m_head = node;
    }
    
    int getLength() const noexcept {
        int length = 0;
        
        for (auto node = m_head->next; node != m_head; node = node->next) {
            ++length;
        }
        
        return length;
    }
    
    std::shared_ptr<Node> getHead() noexcept {
        auto node = m_head->next;
        
        if (node == m_head) {
            return nullptr;
        }
        
        return node;
    }
    
    std::shared_ptr<Node> operator[](int pos) noexcept {
        auto node = m_head->next;
        
        int i = 0;
        
        while (node != m_head && i < pos) {
            node = node->next;
            ++i;
        }
        
        if (node == m_head && i == pos) {
            return nullptr;
        }
        
        return node;
    }
    
    std::shared_ptr<Node> get(int pos) {
        auto node = operator[](pos);
        
        if (node == nullptr && m_head != m_head->next) {
            throw std::out_of_range("index is too big.");
        }
        
        return node;
    }

    std::shared_ptr<Node> find(const T& value) {
        auto node = m_head->next;

        while (node != m_head && node->value != value) {
            node = node->next;
        }
        
        if (node == m_head) {
            return nullptr;
        }

        return node;
    }
    
    void insert(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        node->next = m_head->next;
        m_head->next->prev = node;
        node->prev = m_head;
        m_head->next = node;
    }
    
    void remove(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::invalid_argument("argument is a nullptr.");
        }
        
        node->prev->next = node->next;
        node->next->prev = node->prev;
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