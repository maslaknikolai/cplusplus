#include <iostream>
#include <vector>


int main()
{
    std::string name;
    std::string description;

    std::cout << "What's your name?: ";
    std::cin >> name;

    std::cout << "sup " << name << ". present yourself";
    // without " >> std::ws" it finishes program because prev >> left " \n" in the buffer so we clear it with whitespace;
    std::getline(std::cin >> std::ws, description);

    return 0;
}