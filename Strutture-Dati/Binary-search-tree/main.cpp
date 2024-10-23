// Funzionante, ma non ancora completo
#include <memory>
#include <iostream>
#include <concepts>
#include <type_traits>
#include <stdexcept>

template<typename T>
concept Printable = requires(std::ostream& out, T t) {
    {out << t} -> std::same_as<std::ostream&>;
};

template<typename T>
concept PrintableAndOrdered = Printable<T> && std::totally_ordered<T>;

template<PrintableAndOrdered Key>
class BinarySearchTree {
public:
    class Node {
    public:
        friend class BinarySearchTree;
    
        Node(const Key& key) noexcept 
            : m_key(key), m_parent(nullptr), m_left(nullptr), m_right(nullptr) 
        {}
    private:
        Key m_key;
        std::shared_ptr<Node> m_parent, m_left, m_right;
    };
    
    BinarySearchTree() noexcept : m_root(nullptr) {}
    
    std::shared_ptr<const Node> getRoot() const noexcept {
        return std::const_pointer_cast<const Node>(m_root);
    }
    
    bool isEmpty() const noexcept {
        return m_root == nullptr;
    }
    
    void inorderWalk(std::shared_ptr<const Node> node, std::ostream& out) const 
        noexcept 
    {
        if (node != nullptr) {
            inorderWalk(node->m_left, out);
            out << node->m_key << " ";
            inorderWalk(node->m_right, out);
        }
    }
    
    std::shared_ptr<const Node> find(std::shared_ptr<const Node> node, 
        const Key& key) const noexcept 
    {
        if (node == nullptr || key == node->m_key) {
            return std::const_pointer_cast<const Node>(node);
        }
        
        if (key < node->m_key) {
            return find(node->m_left, key);
        } else {
            return find(node->m_right, key);
        }
    }
    
    std::shared_ptr<const Node> find(const Key& key) const noexcept {
        auto node = m_root;
        
        while (node != nullptr && key != node->m_key) {
            if (key < node->m_key) {
                node = node->m_left;
            } else {
                node = node->m_right;
            }
        }
        
        return std::const_pointer_cast<const Node>(node);
    }
    
    const Key& getMin() const {
        if (isEmpty()) {
            throw std::runtime_error("tree is empty.");
        }    
    
        auto node = m_root;
        
        while (node->m_left != nullptr) {
            node = node->m_left;
        }
        
        return node->m_key;
    }
    
    const Key& getMax() const {
        if (isEmpty()) {
            throw std::runtime_error("tree is empty.");
        }    
    
        auto node = m_root;
        
        while (node->m_right != nullptr) {
            node = node->m_right;
        }
        
        return node->m_key;
    }
    
    void insert(std::shared_ptr<Node> node) {
        if (node == nullptr) {
            throw std::runtime_error("cannot insert a nullptr.");
        }
        
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
private:
    std::shared_ptr<Node> m_root;
};

int main() {
    BinarySearchTree<int> tree;
    
    auto node1 = std::make_shared<BinarySearchTree<int>::Node>(3);
    tree.insert(node1);
    
    std::cout << "Nodo con chiave 3 inserito.\nChiavi in ordine: [ ";
    tree.inorderWalk(tree.getRoot(), std::cout);
    std::cout << "].\n\n";
    
    auto node2 = std::make_shared<BinarySearchTree<int>::Node>(8);
    tree.insert(node2);
    
    std::cout << "Nodo con chiave 8 inserito.\nChiavi in ordine: [ ";
    tree.inorderWalk(tree.getRoot(), std::cout);
    std::cout << "].\n\n";
    
    auto node3 = std::make_shared<BinarySearchTree<int>::Node>(4);
    tree.insert(node3);
    
    std::cout << "Nodo con chiave 4 inserito.\nChiavi in ordine: [ ";
    tree.inorderWalk(tree.getRoot(), std::cout);
    std::cout << "].\n\n";
    
    auto node4 = std::make_shared<BinarySearchTree<int>::Node>(5);
    tree.insert(node4);
    
    std::cout << "Nodo con chiave 5 inserito.\nChiavi in ordine: [ ";
    tree.inorderWalk(tree.getRoot(), std::cout);
    std::cout << "].\n\n";

    auto node5 = std::make_shared<BinarySearchTree<int>::Node>(1);
    tree.insert(node5);
    
    std::cout << "Nodo con chiave 1 inserito.\nChiavi in ordine: [ ";
    tree.inorderWalk(tree.getRoot(), std::cout);
    std::cout << "].\n\n";
    
    std::cout << "L'elemento minimo e': " << tree.getMin()
        << "\nL'elemento massimo e': " << tree.getMax() << ".\n\n";
    
    std::cout << "Cerco il nodo con chiave 4 con la ricerca ricorsiva.\n"
        << "Nodo con chiave 4 " 
        << (tree.find(tree.getRoot(), 4) != nullptr ? "trovato" 
            : "non trovato") << ".\n\n";
            
    std::cout << "Cerco il nodo con chiave 9 con la ricerca ricorsiva.\n"
        << "Nodo con chiave 9 " 
        << (tree.find(tree.getRoot(), 9) != nullptr ? "trovato" 
            : "non trovato") << ".\n\n";
            
    std::cout << "Cerco il nodo con chiave 4 con la ricerca iterativa.\n"
        << "Nodo con chiave 4 " 
        << (tree.find(4) != nullptr ? "trovato" 
            : "non trovato") << ".\n\n";
            
    std::cout << "Cerco il nodo con chiave 9 con la ricerca iterativa.\n"
        << "Nodo con chiave 9 " 
        << (tree.find(9) != nullptr ? "trovato" 
            : "non trovato") << ".\n\n";
}