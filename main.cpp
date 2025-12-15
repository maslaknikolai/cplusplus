#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void showBalance(double balanceCents);
double deposit();
double withdraw(double amount);

int main() {

    double balance = 0;
    int choice;

    do {
        std::cout << "********************\n";
        std::cout << "Enter your choise number:\n";
        std::cout << "********************\n";
        std::cout << "1. Show balance:\n";
        std::cout << "2. Deposit Money:\n";
        std::cout << "3. Withdraw Money:\n";
        std::cout << "4. Exit:\n";


        std::cin >> choice;
        std::cin.clear();
        fflush(stdin);

        switch (choice) {
            case 1:
                showBalance(balance);
                break;
            case 2:
                balance += deposit();
                showBalance(balance);
                break;
            case 3:
                balance -= withdraw(balance);
                showBalance(balance);
                break;
            case 4:
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
    } while (choice != 4);

    return 0;
}


void showBalance(double balance) {
    std::cout << "Your balance is: $" << std::setprecision(2) << std::fixed << balance;
}

double deposit() {

    double amount = 0;

    std::cout << "Enter amount to be deposited: \n";

    std::cin >> amount;
    std::cin.clear();
    fflush(stdin);

    if (amount <= 0) {
        std::cout << "no";
        return 0;
    }

    return amount;
}

double withdraw(double balance) {
    double amount = 0;

    std::cout << "How much: \n";

    std::cin >> amount;
    std::cin.clear();
    fflush(stdin);

    if (amount < 0) {
        std::cout << "Enter correct number: \n";
        return 0;
    }

    if (amount > balance) {

    }

    return 0;
}