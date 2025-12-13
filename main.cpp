#include <iostream>
#include <vector>

// typedef std::string text_t;
// Better way:
using text_t = std::string;


int main(){
    text_t firstName = "Bro";

    std::cout << firstName;

    return 0;
}