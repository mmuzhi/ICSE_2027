#include <string>
#include <map>

class BookManagement {
private:
    std::map<std::string, int> inventory;

public:
    BookManagement() {}

    void add_book(const std::string& title, int quantity = 1) {
        inventory[title] += quantity;
    }

    void remove_book(const std::string& title, int quantity) {
        if (inventory.find(title) == inventory.end() || inventory[title] < quantity) {
            throw false;
        }
        inventory[title] -= quantity;
        if (inventory[title] == 0) {
            inventory.erase(title);
        }
    }

    std::map<std::string, int> view_inventory() {
        return inventory;
    }

    int view_book_quantity(const std::string& title) {
        auto it = inventory.find(title);
        if (it == inventory.end()) {
            return 0;
        }
        return it->second;
    }
};