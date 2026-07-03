#include <map>
#include <string>
#include <exception>

class BookManagementException : public std::exception {
private:
    bool error;
public:
    explicit BookManagementException(bool e) : error(e) {}
    const char* what() const noexcept override {
        return "Operation failed";
    }
};

class BookManagement {
private:
    std::map<std::string, int> inventory;

public:
    BookManagement() = default;

    void add_book(const std::string& title, int quantity = 1) {
        if (inventory.find(title) != inventory.end()) {
            inventory[title] += quantity;
        } else {
            inventory[title] = quantity;
        }
    }

    void remove_book(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it == inventory.end() || it->second < quantity) {
            throw BookManagementException(false);
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
        if (it == inventory.end()) {
            return 0;
        }
        return it->second;
    }
};