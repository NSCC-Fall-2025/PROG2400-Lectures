#include <iostream>
#include <iomanip>

class BST {
    struct Node;

    using NodePtr = Node*;

    struct Node {
        int _data {-1};
        NodePtr _left {nullptr};
        NodePtr _right {nullptr};
    };

    NodePtr _root {nullptr};

public:
    void insert(int data) {
        insert(data, _root);
    }

    void remove(const int data) {
        auto node = _root;
        auto parent = static_cast<NodePtr>(nullptr);

        // find the node to delete
        while (node != nullptr) {
            // look left and right until its found
            if (data < node->_data) {
                // go left
                parent = node;
                node = node->_left;
            } else if (data > node->_data) {
                // go right
                parent = node;
                node = node->_right;
            } else {
                // found!
                break;
            }
        }

        // did I find the node?
        if (node == nullptr) return; // nope.

        // does this node have two children?
        if (node->_left != nullptr && node->_right != nullptr) {
            // yes! so find a "successor" to replace me

            // start on the left side
            auto successor = node->_left;

            // go as far right as possible
            parent = node;
            while (successor->_right != nullptr) {
                parent = successor;
                successor = successor->_right;
            }

            // move the successor data into node
            node->_data = successor->_data;

            // the successor is now the node to delete
            node = successor;
        }

        // assume there is a left child
        NodePtr child = node->_left;

        // if no left child, maybe a right child
        if (child == nullptr) {
            child = node->_right;
        }

        // disconnect node from parent

        // am I the root node?
        if (parent == nullptr) {
            // yes!
            _root = child;
        } else if (node == parent->_left) {
            // node is the left of parent
            parent->_left = child;
        } else if (node == parent->_right) {
            // node is the right of parent
            parent->_right = child;
        }

        delete node;
    }

private:
    void insert(int data, NodePtr& node) {
        if (node == nullptr) {
            node = new Node({data});
        } else if (data < node->_data) {
            // insert to the left
            insert(data, node->_left);
        } else if (data > node->_data) {
            // insert to the right
            insert(data, node->_right);
        } else {
            std::cout << data << " already exists\n";
        }
    }

    void print_tree(std::ostream& os, NodePtr& node, int indent) {
        if (node == nullptr) return;
        print_tree(os, node->_right, indent + 8);
        os << std::setw(indent) << node->_data << std::endl;
        print_tree(os, node->_left, indent + 8);
    }

    friend std::ostream& operator<<(std::ostream& os, BST& tree);
};

std::ostream& operator<<(std::ostream& os, BST& tree) {
    tree.print_tree(os, tree._root, 0);
    return os;
}

int main() {
    BST bst;

    // test 1 - add some nodes
    std::cout << "Test 1: add nodes to search tree" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    std::cout << bst << std::endl;

    // test 2 - remove a node with no children
    std::cout << "Test 2: remove a node with no child" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    bst.remove(2);

    std::cout << bst << std::endl;

    // test 3 - remove a node with one child
    std::cout << "Test 3: remove a node with one child" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    bst.remove(3);

    std::cout << bst << std::endl;

    // test 4 - remove a node with two children
    std::cout << "Test 4: remove a node with two children" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    bst.remove(7);

    std::cout << bst << std::endl;

    // test 5 - remove the root node
    std::cout << "Test 5: remove the root node" << std::endl;
    std::cout << "----------------------------" << std::endl;

    bst.remove(5);

    std::cout << bst << std::endl;

    // test 6 - remove the remaining nodes
    std::cout << "Test 6: remove the other nodes" << std::endl;
    std::cout << "------------------------------" << std::endl;

    bst.remove(4);
    std::cout << bst << std::endl;

    bst.remove(6);
    std::cout << bst << std::endl;

    bst.remove(8);
    std::cout << bst << std::endl;

    return 0;
}
