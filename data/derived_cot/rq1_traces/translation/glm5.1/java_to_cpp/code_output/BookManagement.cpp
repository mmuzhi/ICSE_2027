#include <unordered_map>
#include <string>
#include <stdexcept>

class BookManagement {
private:
    std::unordered_map<std::string, int> inventory;

public:
    BookManagement() = default;

    void addBook(const std::string& title, int quantity) {
        // operator[] inserts the key with a value-initialized int (0) if it doesn't exist,
        // which perfectly matches the behavior of Java's containsKey/put logic.
        inventory[title] += quantity;
    }

    void removeBook(const std::string& title, int quantity) {
        auto it = inventory.find(title);
        if (it == inventory.end() || it->second < quantity) {
            throw std::runtime_error("Invalid operation");
        }
        
        int newQuantity = it->second - quantity;
        if (newQuantity == 0) {
            inventory.erase(it);
        } else {
            it->second = newQuantity;
        }
    }

    std::unordered_map<std::string, int> viewInventory() const {
        // Returning by value creates a copy, identical to `new HashMap<>(inventory)` in Java
        return inventory;
    }

    int viewBookQuantity(const std::string& title) const {
        auto it = inventory.find(title);
        if (it != inventory.end()) {
            return it->second;
        }
        return 0;
    }
};