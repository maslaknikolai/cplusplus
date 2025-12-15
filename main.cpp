#include <iostream>
#include <vector>
#include <cmath>


int main() {
    int n = 0;

    do {
        std::cout << "Enter positive number: ";
        std::cin >> n;
    } while (n < 0);

    std::cout << "The # is: " << n;

    return 0;
}