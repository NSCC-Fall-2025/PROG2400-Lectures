#include <iostream>
#include <sstream>

int main() {
    std::string user_input;
    std::string command;

    std::cout << "Enter some text: ";
    std::getline(std::cin, user_input);

    // put user input into a stringstream for parsing
    std::stringstream ss(user_input);

    ss >> command;

    // check for a single letter command
    if (command.length() == 1) {
        std::cout << "I think you entered a command." << std::endl;

        // see if the command has a parameter
        auto start = -1;
        auto end = -1;
        ss >> start;
        if (ss.fail()) {
            std::cout << "The command has no start number." << std::endl;
            ss.clear();
        } else {
            // I received a start, how about an end?
            ss >> end;
            if (ss.fail()) {
                std::cout << "The command has no end number." << std::endl;
                ss.clear();
            }
        }

        std::cout << "command: " << command;
        std::cout << ", start: " << start;
        std::cout << ", end: " << end << std::endl;
    } else {
        // any command longer than a single letter is not a command
        std::cout << "You typed in text!" << std::endl;
    }

    return 0;
}
