#include <map>
#include <stdexcept>

class BookManagement {
private:
    std::map<std::string, int> inventory;

public:
    void add_book(const std::string& title, int quantity = 1) {
        if (inventory.find(title) != inventory.end()) {
            inventory[title] += quantity;
        } else {
            inventory[title] = quantity;
        }
    }

    void remove_book(const std::string& title, int quantity) {
        if (inventory.find(title) == inventory.end() || inventory[title] < quantity) {
            throw std::runtime_error("Invalid operation: Book not found or insufficient quantity");
        }
        inventory[title] -= quantity;
        if (inventory[title] == 0) {
            inventory.erase(title);
        }
    }

    std::map<std::string, int> view_inventory() const {
        return inventory;
    }

    int view_book_quantity(const std::string& title) const {
        auto it = inventory.find(title);
        return (it != inventory.end()) ? it->second : 0;
    }
};