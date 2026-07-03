#include <string>
#include <map>

class BookManagement {
private:
    std::map<std::string, int> inventory;

public:
    BookManagement() = default;

    void add_book(const std::string& title, int quantity = 1) {
        inventory[title] += quantity;
    }

    void remove_book(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it == inventory.end() || it->second < quantity) {
            // Python code uses `raise False`, which throws a TypeError at runtime. 
            // We translate this literally to `throw false;` to match the source's intent.
            throw false; 
        }
        it->second -= quantity;
        if (it->second == 0) {
            inventory.erase(it);
        }
    }

    std::map<std::string, int>& view_inventory() {
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