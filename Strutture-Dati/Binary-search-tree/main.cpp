// Funzionante, ma non ancora completo
#include <memory>
#include <iostream>
#include <concepts>
#include <type_traits>
#include <stdexcept>

template<typename Key>
class BinarySearchTree {
private:
    class Node {
    private:
        Key m_key;
        std::shared_ptr<Node> m_parent, m_left, m_right;
    public:
        friend class BinarySearchTree;
    
        constexpr explicit Node(const Key& key) noexcept 
            : m_key(key), m_parent(nullptr), m_left(nullptr)
            , m_right(nullptr) {}
    };
    
    class ConstIterator {
    private:
        const Node* m_ptr;
    public:
        constexpr explicit ConstIterator(const Node* ptr) noexcept : 
            m_ptr(ptr) {}
        
        constexpr const Key& operator*() const noexcept {
            return m_ptr->m_key;
        }
    };

    constexpr void inOrderWalk(std::shared_ptr<const Node> node, 
        std::ostream& out) const noexcept 
    {
        if (node != nullptr) {
            inOrderWalk(node->m_left, out);
            out << node->m_key << " ";
            inOrderWalk(node->m_right, out);
        }
    }
    
    constexpr ConstIterator find(std::shared_ptr<const Node> node, 
        const Key& key) const noexcept 
    {
        if (node == nullptr || key == node->m_key) {
            return ConstIterator(node);
        }
        
        if (key < node->m_key) {
            return find(node->m_left, key);
        } else {
            return find(node->m_right, key);
        }
    }
    
    std::shared_ptr<Node> m_root;
public:
    constexpr explicit BinarySearchTree() noexcept : m_root(nullptr) {}
    
    constexpr const Key& getRoot() const noexcept {
        return m_root->m_key;
    }
    
    constexpr bool isEmpty() const noexcept {
        return m_root == nullptr;
    }
    
    constexpr void inOrderWalk(std::ostream& out) const noexcept {
        inOrderWalk(m_root, out);    
    }
    
    constexpr ConstIterator find(const Key& key) const noexcept {
        auto node = m_root;
        
        while (node != nullptr && key != node->m_key) {
            if (key < node->m_key) {
                node = node->m_left;
            } else {
                node = node->m_right;
            }
        }
        
        return ConstIterator(node.get());
    }
    
    constexpr const Key& getMin() const {
        if (isEmpty()) {
            throw std::runtime_error("tree is empty.");
        }    
    
        auto node = m_root;
        
        while (node->m_left != nullptr) {
            node = node->m_left;
        }
        
        return node->m_key;
    }
    
    constexpr const Key& getMax() const {
        if (isEmpty()) {
            throw std::runtime_error("tree is empty.");
        }    
    
        auto node = m_root;
        
        while (node->m_right != nullptr) {
            node = node->m_right;
        }
        
        return node->m_key;
    }
    
    constexpr void insert(const Key& key) {
        auto node = std::make_shared<Node>(key);
        
        std::shared_ptr<Node> parent = nullptr;
        auto child = m_root;
        
        while (child != nullptr) {
            parent = child;
            
            if (node->m_key < child->m_key) {
                child = child->m_left;
            } else {
                child = child->m_right;
            }
        }
        
        node->m_parent = parent;
        
        if (parent == nullptr) {
            m_root = node;
        } else if (node->m_key < parent->m_key) {
            parent->m_left = node;
        } else {
            parent->m_right = node;
        }
    }
};

int main() {
    BinarySearchTree<int> tree;
    
    tree.insert(3);
    
    std::cout << "Nodo con chiave 3 inserito.\nChiavi in ordine: [ ";
    tree.inOrderWalk(std::cout);
    std::cout << "].\n\n";
    
    tree.insert(8);
    
    std::cout << "Nodo con chiave 8 inserito.\nChiavi in ordine: [ ";
    tree.inOrderWalk(std::cout);
    std::cout << "].\n\n";
    
    tree.insert(4);
    
    std::cout << "Nodo con chiave 4 inserito.\nChiavi in ordine: [ ";
    tree.inOrderWalk(std::cout);
    std::cout << "].\n\n";
    
    tree.insert(5);
    
    std::cout << "Nodo con chiave 5 inserito.\nChiavi in ordine: [ ";
    tree.inOrderWalk(std::cout);
    std::cout << "].\n\n";

    tree.insert(1);
    
    std::cout << "Nodo con chiave 1 inserito.\nChiavi in ordine: [ ";
    tree.inOrderWalk(std::cout);
    std::cout << "].\n\n";
    
    std::cout << "L'elemento minimo e': " << tree.getMin()
        << "\nL'elemento massimo e': " << tree.getMax() << ".\n\n";
    
    std::cout << "Cerco il nodo con chiave 4.\n"
        << "Chiave: " << *tree.find(4) << ".\n\n";
}