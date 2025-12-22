#include <charconv>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace {

std::optional<int> getInputInt();
std::optional<double> getInputDouble();
void showBalance(double balance_cents);
double deposit();
double withdraw(const double balance);
std::string formatFixed(double value, int precision);

}  // namespace

int main() {

    double balance = 0;
    int choice = 0;

    while (choice != 4) {
        std::cout << "********************\n";
        std::cout << "Enter your choise number:\n";
        std::cout << "********************\n";
        std::cout << "1. Show balance:\n";
        std::cout << "2. Deposit Money:\n";
        std::cout << "3. Withdraw Money:\n";
        std::cout << "4. Exit:\n";

        auto input = getInputInt();
        if (!input) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        choice = *input;

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
    }

    return 0;
}

namespace {

std::optional<int> getInputInt() {
    std::string input;
    if (!std::getline(std::cin, input)) {
        return std::nullopt;
    }

    int value{};

    const char* begin = input.data();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    const char* end = begin + input.size();
    auto [ptr, ec] = std::from_chars(begin, end, value);

    if (ec != std::errc{} || ptr != end) {
        return std::nullopt;
    }

    return value;
}

std::optional<double> getInputDouble() {
    std::string input;
    if (!std::getline(std::cin, input)) {
        return std::nullopt;
    }

    try {
        size_t pos = 0;
        double value = std::stod(input, &pos);

        // Check if the entire string was consumed
        if (pos != input.length()) {
            return std::nullopt;
        }

        return value;
    } catch (...) {
        return std::nullopt;
    }
}

void showBalance(const double balance) {
    std::cout << "Your balance is: $" << formatFixed(balance, 2) << "\n";
}

double deposit() {
    std::cout << "Enter amount to be deposited: \n";

    auto input = getInputDouble();
    if (!input) {
        std::cout << "Invalid input. Please enter a valid number.\n";
        return 0;
    }

    double amount = *input;

    if (amount <= 0) {
        std::cout << "Amount must be positive.\n";
        return 0;
    }

    return amount;
}

double withdraw(const double balance) {
    std::cout << "How much: \n";

    auto input = getInputDouble();

    if (!input) {
        std::cout << "Invalid input. Please enter a valid number.\n";
        return 0;
    }

    const double amount = *input;

    if (amount < 0) {
        std::cout << "Amount cannot be negative.\n";
        return 0;
    }

    if (amount > balance) {
        std::cout << "Insufficient funds! You only have $" << formatFixed(balance, 2) << "\n";
        return 0;
    }

    return amount;
}

std::string formatFixed(double value, int precision) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

}  // namespace
