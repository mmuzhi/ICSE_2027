#ifndef BOOK_MANAGEMENT_HPP
#define BOOK_MANAGEMENT_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>

class BookManagement {
private:
    std::unordered_map<std::string, int> inventory;

public:
    BookManagement() = default;

    void addBook(const std::string& title, int quantity) {
        if (inventory.count(title)) {
            inventory[title] += quantity;
        } else {
            inventory[title] = quantity;
        }
    }

    void removeBook(const std::string& title, int quantity) {
        if (!inventory.count(title) || inventory[title] < quantity) {
            throw std::runtime_error("Invalid operation");
        }
        int newQuantity = inventory[title] - quantity;
        if (newQuantity == 0) {
            inventory.erase(title);
        } else {
            inventory[title] = newQuantity;
        }
    }

    std::unordered_map<std::string, int> viewInventory() {
        return inventory;
    }

    int viewBookQuantity(const std::string& title) {
        auto it = inventory.find(title);
        if (it != inventory.end()) {
            return it->second;
        }
        return 0;
    }
};

#endif // BOOK_MANAGEMENT_HPP