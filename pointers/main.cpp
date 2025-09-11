#include <iostream>

typedef void (*FUNCPTR)(int*) ;

void pass_by_pointer(int* ptr) {
    std::cout << "pass_by_pointer" << std::endl;
    std::cout << *ptr << std::endl;
}

void pass_by_reference(int& ref) {
    std::cout << "pass_by_reference" << std::endl;
    std::cout << ref << std::endl;
}

void pass_by_double_pointer(int** dbl_ptr) {
    std::cout << "pass_by_double_pointer" << std::endl;
    std::cout << *dbl_ptr << std::endl;

    *dbl_ptr = new int[10];
}

void pass_int_by_pointer(int* ptr) {
    std::cout << "pass_int_by_pointer" << std::endl;
    *ptr = 10;
    ptr = new int[10];
}

int main() {
    // basic integers
    auto word = 0x1234ul;

    std::cout << std::hex << std::showbase;
    std::cout << "word: " << word;
    std::cout << ", address: " << &word << std::endl;

    // basic pointer
    auto a_ptr = (void*)0xFF;
    auto b_ptr = (void*)0x1234'5678ul;
    auto c_ptr = (void*)0x1122'3344'5566'7788ull;

    std::cout << "a_ptr = " << a_ptr << std::endl;
    std::cout << "b_ptr = " << b_ptr << std::endl;
    std::cout << "c_ptr = " << c_ptr << std::endl;

    // pointer usage
    int num = 0x1234;
    auto ptr = &num; // a valid address
    std::cout << "ptr = " << ptr << std::endl;

    // pointers in functions
    pass_by_pointer(ptr);
    pass_by_pointer(&num);
    //pass_by_pointer((int*)0x5ffecc);
    //pass_by_pointer((int*)num);

    pass_by_reference(num);
    // pass_by_reference((int&)0x5ffecc); // ERROR!

    pass_by_double_pointer(&ptr);

    int num2 = 0x1234;
    pass_int_by_pointer(&num2);
    std::cout << "num2 = " << num2 << std::endl;

    void (*func_ptr)(int*) = nullptr;
    FUNCPTR f = nullptr;

    return 0;
}
