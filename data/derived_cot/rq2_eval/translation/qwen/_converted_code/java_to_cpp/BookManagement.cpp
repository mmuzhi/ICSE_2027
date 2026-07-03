#include <map>
#include <string>
#include <stdexcept>

class BookManagement {
private:
    std::map<std::string, int> inventory;

public:
    BookManagement() = default;

    void add_book(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it != inventory.end()) {
            it->second += quantity;
        } else {
            inventory.insert({title, quantity});
        }
    }

    void remove_book(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it == inventory.end() || it->second < quantity) {
            throw std::runtime_error("Invalid operation");
        }
        it->second -= quantity;
        if (it->second == 0) {
            inventory.erase(it);
        }
    }

    std::map<std::string, int> viewInventory() const {
        return inventory;
    }

    int view_book_quantity(const std::string& title) const {
        auto it = inventory.find(title);
        if (it != inventory.end()) {
            return it->second;
        }
        return 0;
    }
};