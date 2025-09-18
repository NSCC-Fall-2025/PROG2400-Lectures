#include <iostream>
#include <memory>

class LinkedList {
    struct Node {
        int _data {-1};
        std::unique_ptr<Node> _next {nullptr};
    };

    std::unique_ptr<Node> _start {nullptr};

public:
#if NOT_NEEDED
    virtual ~LinkedList() {
        auto node = _start;
        while (node != nullptr) {
            const auto temp = node->_next;
            delete node;
            node = temp;
        }
    }
#endif

    void add(int num) {
        // auto node = new Node({num});
        auto node = std::make_unique<Node>(num);

        // are we adding the first node?
        if (_start == nullptr) {
            // add first node to chain
            _start = std::move(node);
        } else {
            // add more nodes to the chain

            // find the end of the chain to connect to

            auto prev = static_cast<Node*>(nullptr);
            auto curr = _start.get();

            // keep iterating through each node
            // until the end of the chain is found
            // "prev" will point to the last node in the chain
            while (curr != nullptr) {
                prev = curr;
                curr = curr->_next.get();
            }

            // did I find the end of the chain?
            if (prev != nullptr) {
                // if so, connect last node to new node
                prev->_next = std::move(node);
            }
        }
    }

    /// insert a new node
    /// @param num the value to insert
    /// @param before the value of the node to insert before
    void insert(int num, int before) {
        auto new_node = new Node({num});

        // find the node to insert before
        auto node = _start;
        auto prev = static_cast<Node*>(nullptr);

        while (node != nullptr) {
            // find node based on criteria
            if (node->_data == before) {
                // found the node!
                break;
            }
            prev = node;
            node = node->_next;
        }

        // did we find the node we were looking for?
        if (node != nullptr) {
            if (prev == nullptr) {
                // the node found is the start node
                new_node->_next = _start;
                _start = new_node;
            } else {
                // the found is not the start node
                new_node->_next = prev->_next;
                prev->_next = new_node;
            }
        } else {
            // didn't find the node, so add the end
            add(num);
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

    // Test 3: insert a node at the beginning of the chain

    std::cout << "Test 3: insert a node at the beginning" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    // insert the value 0 before a node that contains the value 1
    list.insert(0, 1);

    std::cout << list << std::endl;

    // Test 4: insert a node in the middle of the chain

    std::cout << "Test 4: insert a node in the middle" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // insert the value 9 before a node that contains the value 3
    list.insert(9, 3);

    std::cout << list << std::endl;

    // Test 5: insert a node before a non-existent node

    std::cout << "Test 5: insert a node before an non-existent node" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    // insert the value 10 before a node that contains the value 100
    list.insert(10, 100);

    std::cout << list << std::endl;

    return 0;
}
