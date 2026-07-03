#include <stdexcept>

class BankAccount {
private:
    int balance;

public:
    // Default constructor
    BankAccount() : balance(0) {}

    // Parameterized constructor
    explicit BankAccount(int initial_balance) : balance(initial_balance) {}

    // Deposit money into the account
    void deposit(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Invalid amount");
        }
        balance += amount;
    }

    // Withdraw money from the account
    void withdraw(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Invalid amount");
        }
        if (amount > balance) {
            throw std::out_of_range("Insufficient balance.");
        }
        balance -= amount;
    }

    // View current balance
    int view_balance() const {
        return balance;
    }

    // Transfer money to another account
    void transfer(BankAccount& other_account, int amount) {
        withdraw(amount);
        other_account.deposit(amount);
    }
};