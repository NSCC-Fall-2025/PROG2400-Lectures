#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& output, const std::vector<int>& v) {
    for (auto& n : v) {
        output << n << " ";
    }
    return output;
}

void operator<<(std::vector<int>& v, const std::vector<int>& in_vec) {
    for (auto& n : in_vec) {
        v.push_back(n);
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};

    // standard array
    for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) {
        std::cout << nums[i] << std::endl;
    }

    std::vector v = {1, 2, 3, 4, 5};

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v.push_back(6);

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v << std::vector({7, 8, 9, 10, 11});

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v.shrink_to_fit();

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v.reserve(25);

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    return 0;
}
