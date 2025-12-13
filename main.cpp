#include <iostream>

namespace first {
    int x = 1;
}

int main(){
    using namespace first;

    std::cout << x << "\n";
    std::cout << x << "\n";

    return 0;
}