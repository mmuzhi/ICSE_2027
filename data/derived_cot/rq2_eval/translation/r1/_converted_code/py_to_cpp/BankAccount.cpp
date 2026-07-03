#include <stdexcept>

class BankAccount {
private:
    int balance;

public:
    BankAccount(int initial_balance = 0) : balance(initial_balance) {}

    int deposit(int amount) {
        if (amount < 0) {
            throw std::runtime_error("Invalid amount");
        }
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount < 0) {
            throw std::runtime_error("Invalid amount");
        }
        if (amount > balance) {
            throw std::runtime_error("Insufficient balance.");
        }
        balance -= amount;
        return balance;
    }

    int view_balance() const {
        return balance;
    }

    void transfer(BankAccount& other_account, int amount) {
        withdraw(amount);
        other_account.deposit(amount);
    }
};