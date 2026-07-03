#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <any>

template <typename V = std::any>
class CamelCaseMap {
private:
    std::map<std::string, V> _data;

    static std::string _to_camel_case(const std::string& key) {
        std::vector<std::string> parts;
        std::stringstream ss(key);
        std::string part;
        
        // Split string by '_'
        while (std::getline(ss, part, '_')) {
            parts.push_back(part);
        }

        if (parts.empty()) {
            return "";
        }

        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                // Convert to title case: first letter uppercase, rest lowercase
                // (Mimics Python's str.title() for ASCII)
                parts[i][0] = std::toupper(static_cast<unsigned char>(parts[i][0]));
                for (size_t j = 1; j < parts[i].size(); ++j) {
                    parts[i][j] = std::tolower(static_cast<unsigned char>(parts[i][j]));
                }
            }
            result += parts[i];
        }
        return result;
    }

    std::string _convert_key(const std::string& key) const {
        // In C++, we enforce string keys for this map, so the isinstance check is inherently satisfied.
        return _to_camel_case(key);
    }

public:
    CamelCaseMap() = default;

    // __getitem__
    // Equivalent to Python's `map[key]`. Throws std::out_of_range if missing, similar to KeyError.
    V& at(const std::string& key) {
        return _data.at(_convert_key(key));
    }

    const V& at(const std::string& key) const {
        return _data.at(_convert_key(key));
    }

    // __setitem__
    // Equivalent to Python's `map[key] = value`. Creates the key if it doesn't exist.
    V& operator[](const std::string& key) {
        return _data[_convert_key(key)];
    }

    // __delitem__
    // Equivalent to Python's `del map[key]`. Throws std::out_of_range if missing, similar to KeyError.
    void erase(const std::string& key) {
        std::string converted = _convert_key(key);
        if (_data.find(converted) == _data.end()) {
            throw std::out_of_range("KeyError");
        }
        _data.erase(converted);
    }

    // __iter__
    // Note: Iterating over a C++ map yields std::pair<const Key, Value>, 
    // unlike Python which yields only the keys.
    auto begin() const {
        return _data.begin();
    }

    auto begin() {
        return _data.begin();
    }

    auto end() const {
        return _data.end();
    }

    auto end() {
        return _data.end();
    }

    // __len__
    size_t size() const {
        return _data.size();
    }
};