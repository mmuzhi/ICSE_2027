#include <string>
#include <vector>
#include <unordered_map>
#include <any>
#include <cctype>
#include <stdexcept>

class CamelCaseMap {
private:
    std::vector<std::string> keyOrder;
    std::unordered_map<std::string, std::any> data;

    static std::string _toCamelCase(const std::string& key) {
        // Split by '_', matching Java's split("_") behavior
        // (trailing empty strings are discarded)
        std::vector<std::string> parts;
        std::string part;
        for (char c : key) {
            if (c == '_') {
                parts.push_back(part);
                part.clear();
            } else {
                part += c;
            }
        }
        parts.push_back(part);

        // Remove trailing empty strings (Java split with limit 0 behavior)
        while (!parts.empty() && parts.back().empty()) {
            parts.pop_back();
        }

        if (parts.empty()) {
            throw std::out_of_range("Key results in empty parts after split");
        }

        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); i++) {
            if (parts[i].empty()) {
                // Java's substring(0,1) on empty string throws IndexOutOfBoundsException
                throw std::out_of_range("Empty segment in key");
            }
            result += static_cast<char>(std::toupper(static_cast<unsigned char>(parts[i][0])));
            for (size_t j = 1; j < parts[i].size(); j++) {
                result += static_cast<char>(std::tolower(static_cast<unsigned char>(parts[i][j])));
            }
        }
        return result;
    }

    std::string _convertKey(const std::string& key) const {
        return _toCamelCase(key);
    }

public:
    // Returns pointer to value, or nullptr if key not found
    // (mirrors Java's nullable Object return)
    std::any* get(const std::string& key) {
        std::string converted = _convertKey(key);
        auto it = data.find(converted);
        if (it != data.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    const std::any* get(const std::string& key) const {
        std::string converted = _convertKey(key);
        auto it = data.find(converted);
        if (it != data.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    void put(const std::string& key, std::any value) {
        std::string converted = _convertKey(key);
        auto it = data.find(converted);
        if (it != data.end()) {
            it->second = std::move(value);
        } else {
            keyOrder.push_back(converted);
            data.emplace(converted, std::move(value));
        }
    }

    void remove(const std::string& key) {
        std::string converted = _convertKey(key);
        auto it = data.find(converted);
        if (it != data.end()) {
            data.erase(it);
            for (auto kit = keyOrder.begin(); kit != keyOrder.end(); ++kit) {
                if (*kit == converted) {
                    keyOrder.erase(kit);
                    break;
                }
            }
        }
    }

    // Returns keys in insertion order (mirrors LinkedHashMap.keySet())
    std::vector<std::string> keySet() const {
        return keyOrder;
    }

    int size() const {
        return static_cast<int>(data.size());
    }
};