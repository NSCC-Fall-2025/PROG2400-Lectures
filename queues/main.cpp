#include <iostream>
#include <memory>

struct Student {
    std::string _name {"Invalid Bob"};
    std::string _id {"W000000"};
};

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << student._name << " (" << student._id << " )";
    return os;
}

class Queue {
    struct Node {
        Student _data;
        std::unique_ptr<Node> _next {nullptr};
    };

    std::unique_ptr<Node> _front {nullptr};
    Node* _back {nullptr};
    size_t _size {0};

public:
    void push_back(const Student& data) {
        auto node = std::make_unique<Node>(data);

        // are we adding to an empty queue?
        if (_front == nullptr) {
            // yes!
            _front = std::move(node);
            _back = _front.get();
        } else {
            // no.
            _back->_next = std::move(node);
            _back = _back->_next.get();
        }

        _size++;
    }

    void pop_front() {
        // needed if an empty queue
        if (_front == nullptr) return;

        _front = std::move(_front->_next);

        // needed if removing last node
        if (_front == nullptr) _back = nullptr;

        _size--;
    }

    [[nodiscard]] Student peek() {
        return _front != nullptr ? _front->_data : Student();
    }

    [[nodiscard]] Student front() { return peek(); }

    [[nodiscard]] bool empty() { return _front == nullptr; }

    [[nodiscard]] size_t size() { return _size; }

    friend std::ostream& operator<<(std::ostream& output, const Queue& queue);
};

std::ostream& operator<<(std::ostream& output, const Queue& queue) {
    auto node = queue._front.get();
    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next.get();
    }
    return output;
}

int main() {
    Queue queue;

    // test 1 : add some nodes to the queue
    std::cout << "Test 1: push nodes to end of the queue" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    queue.push_back({"John Smith", "W111111"});
    queue.push_back({"Jane Doe", "W222222"});
    queue.push_back({"Jill Hill", "W333333"});
    queue.push_back({"Jack Sprat", "W444444"});
    queue.push_back({"Bill Hill", "W555555"});

    std::cout << queue << std::endl;

    // test 2 : evaluate the data at the front of the queue
    std::cout << "Test 2: Peek at a node" << std::endl;
    std::cout << "----------------------" << std::endl;

    std::cout << queue.peek() << std::endl;
    std::cout << queue.front() << std::endl;

    // test 3 : remove a node from the front of the queue
    std::cout << "Test 3: Pop off the first node" << std::endl;
    std::cout << "------------------------------" << std::endl;

    queue.pop_front();
    std::cout << queue << std::endl;

    // test 4 : remove all nodes from the queue
    std::cout << "Test 4: Remove all nodes from the queue" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    while (!queue.empty()) {
        queue.pop_front();
        std::cout << queue << "[" << queue.size() << " remaining]" << std::endl;
    }

    return 0;
}
