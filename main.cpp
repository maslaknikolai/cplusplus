#include <iostream>
#include <vector>
#include <cmath>

void foo(std::string name, int age);

int main() {
    std::string v = "n";
    foo(v, (int)12);

    return 0;
}

void foo(std::string aname, int age) {
    std::cout << aname << age;
}