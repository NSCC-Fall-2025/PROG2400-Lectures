#include <iostream>

class LinkedList {
    struct Node {
        int _data {-1};
        Node* _next {nullptr};
    };

    Node* _start {nullptr};

public:
    virtual ~LinkedList() {
        auto node = _start;
        while (node != nullptr) {
            const auto temp = node->_next;
            delete node;
            node = temp;
        }
    }

    void add(int num) {
        auto node = new Node({num});

        // are we adding the first node?
        if (_start == nullptr) {
            // add first node to chain
            _start = node;
        } else {
            // add more nodes to the chain

            // find the end of the chain to connect to

            auto prev = static_cast<Node*>(nullptr);
            auto curr = _start;

            // keep iterating through each node
            // until the end of the chain is found
            // "prev" will point to the last node in the chain
            while (curr != nullptr) {
                prev = curr;
                curr = curr->_next;
            }

            // did I find the end of the chain?
            if (prev != nullptr) {
                // if so, connect last node to new node
                prev->_next = node;
            }
        }
    }

    void remove(int num) {
        auto prev = static_cast<Node*>(nullptr);
        auto node = _start;

        // find the node to delete
        while (node != nullptr) {
            // look for a node with a particular value
            if (node->_data == num) {
                // we found the node
                break;
            }
            prev = node;
            node = node->_next;
        }

        // did we find the node to delete?
        if (node != nullptr) {
            // yes! we did!

            // is this the first node?
            if (prev == nullptr) {
                // yes, it is!
                _start = node->_next;
            } else {
                // nope...
                prev->_next = node->_next;
            }

            delete node;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list);
};

std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
    auto node = list._start;

    while (node != nullptr) {
        // display : 1 2 3 4 5...
        os << node->_data << " ";
        node = node->_next;
    }
    return os;
}

int main() {
    LinkedList list;

    // Test 1: add some data

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    std::cout << "Test 1: add some data" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << list << std::endl;

    // Test 2: delete a node at the end

    std::cout << "Test 2: delete node at end" << std::endl;
    std::cout << "--------------------------" << std::endl;

    list.remove(5);

    std::cout << list << std::endl;

    return 0;
}
