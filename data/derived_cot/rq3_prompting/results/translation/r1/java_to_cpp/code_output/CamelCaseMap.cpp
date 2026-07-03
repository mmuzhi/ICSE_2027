#include <vector>
#include <string>
#include <optional>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <utility>

class CamelCaseMap {
private:
    // Each entry: optional key (nullopt for null key), value
    std::vector<std::pair<std::optional<std::string>, std::string>> entries;

    // Convert user-provided raw key (possibly null) to the internal key (camelCase or nullopt)
    static std::optional<std::string> _convertKey(const char* key) {
        if (key == nullptr) {
            return std::nullopt;
        }
        return _toCamelCase(std::string(key));
    }

    // Convert snake_case to camelCase (replicates Java's _toCamelCase)
    static std::string _toCamelCase(const std::string& key) {
        // Split by '_', mimicking Java's String.split("_") (trailing empties removed)
        std::vector<std::string> parts;
        std::istringstream stream(key);
        std::string segment;
        while (std::getline(stream, segment, '_')) {
            parts.push_back(segment);
        }
        // Remove trailing empty strings (Java's default split behavior for limit=0)
        while (!parts.empty() && parts.back().empty()) {
            parts.pop_back();
        }

        if (parts.empty()) {
            return "";
        }

        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            const std::string& part = parts[i];
            if (!part.empty()) {
                result += static_cast<char>(std::toupper(static_cast<unsigned char>(part[0])));
                for (size_t j = 1; j < part.size(); ++j) {
                    result += static_cast<char>(std::tolower(static_cast<unsigned char>(part[j])));
                }
            }
        }
        return result;
    }

public:
    // Get value for key (nullptr for null). Returns std::nullopt if not found.
    std::optional<std::string> get(const char* key) {
        std::optional<std::string> internalKey = _convertKey(key);
        for (const auto& entry : entries) {
            if (entry.first == internalKey) {
                return entry.second;
            }
        }
        return std::nullopt;
    }

    // Insert or update key-value pair. Key can be nullptr for null key.
    void put(const char* key, const std::string& value) {
        std::optional<std::string> internalKey = _convertKey(key);
        // Search for existing key
        for (auto& entry : entries) {
            if (entry.first == internalKey) {
                entry.second = value; // Update value, preserve order
                return;
            }
        }
        // Not found: add new entry at the end
        entries.emplace_back(std::move(internalKey), value);
    }

    // Remove key-value pair (if present). Key can be nullptr.
    void remove(const char* key) {
        std::optional<std::string> internalKey = _convertKey(key);
        auto it = std::remove_if(entries.begin(), entries.end(),
                                 [&](const auto& entry) {
                                     return entry.first == internalKey;
                                 });
        entries.erase(it, entries.end());
    }

    // Return keys in insertion order (optional to represent null key)
    std::vector<std::optional<std::string>> keySet() const {
        std::vector<std::optional<std::string>> keys;
        keys.reserve(entries.size());
        for (const auto& entry : entries) {
            keys.push_back(entry.first);
        }
        return keys;
    }

    // Number of entries
    int size() const {
        return static_cast<int>(entries.size());
    }
};