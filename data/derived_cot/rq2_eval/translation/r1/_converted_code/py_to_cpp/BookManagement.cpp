#include <unordered_map>
#include <string>

class BookManagement {
private:
    std::unordered_map<std::string, int> inventory;

public:
    BookManagement() = default;

    void add_book(const std::string& title, int quantity = 1) {
        auto it = inventory.find(title);
        if (it != inventory.end()) {
            it->second += quantity;
        } else {
            inventory[title] = quantity;
        }
    }

    void remove_book(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it == inventory.end() || it->second < quantity) {
            throw false;
        }
        it->second -= quantity;
        if (it->second == 0) {
            inventory.erase(it);
        }
    }

    std::unordered_map<std::string, int>& view_inventory() {
        return inventory;
    }

    int view_book_quantity(const std::string& title) const {
        auto it = inventory.find(title);
        if (it == inventory.end()) {
            return 0;
        }
        return it->second;
    }
};