#include <iostream>
#include <vector>
#include <cmath>

void foo(std::string name, int age);
void foo(std::string name);

int main() {
    std::string v = "n";
    foo(v);
    foo(v, (int)12);

    return 0;
}

void foo(std::string aname) {
    std::cout << aname;
}

void foo(std::string aname, int age) {
    std::cout << aname << age;
}