#include <iostream>
#include <stdexcept>

namespace org {
namespace example {

class BankAccount {
private:
    int balance;

public:
    BankAccount(int balance) : balance(balance) {}

    BankAccount() : balance(0) {}

    int deposit(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Invalid amount");
        }
        this->balance += amount;
        return this->balance;
    }

    int withdraw(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Invalid amount");
        }
        if (amount > this->balance) {
            throw std::invalid_argument("Insufficient balance.");
        }
        this->balance -= amount;
        return this->balance;
    }

    int viewBalance() const {
        return this->balance;
    }

    // Pass by reference to mimic Java's pass-by-reference-value behavior for objects.
    // If passed by value, the deposit would only affect a local copy, altering the behavior.
    void transfer(BankAccount& otherAccount, int amount) {
        this->withdraw(amount);
        otherAccount.deposit(amount);
    }
};

} // namespace example
} // namespace org

int main() {
    org::example::BankAccount account1;
    org::example::BankAccount account2;
    account1.deposit(1000);
    account1.transfer(account2, 300);
    std::cout << "account1.balance = " << account1.viewBalance() << std::endl;
    std::cout << "account2.balance = " << account2.viewBalance() << std::endl;
    return 0;
}