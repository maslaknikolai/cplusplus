#include <iostream>
#include <vector>
#include <cmath>


int main()
{
    std::string name;

    while (name.empty()) {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    }


    return 0;
}