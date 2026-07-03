#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <iterator>

class CamelCaseMap {
private:
    std::unordered_map<std::string, std::string> _data;

    static std::string _to_camel_case(const std::string& key) {
        std::vector<std::string> parts;
        size_t start = 0;
        for (size_t i = 0; i <= key.size(); ++i) {
            if (i == key.size() || key[i] == '_') {
                parts.push_back(key.substr(start, i - start));
                start = i + 1;
            }
        }
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            std::string& part = parts[i];
            if (!part.empty()) {
                part[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(part[0])));
                for (size_t j = 1; j < part.size(); ++j) {
                    part[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(part[j])));
                }
            }
            result += part;
        }
        return result;
    }

    std::string _convert_key(const std::string& key) const {
        return _to_camel_case(key);
    }

public:
    CamelCaseMap() = default;

    // __getitem__: raises KeyError if not found
    std::string& at(const std::string& key) {
        return _data.at(_convert_key(key));
    }

    const std::string& at(const std::string& key) const {
        return _data.at(_convert_key(key));
    }

    // __setitem__
    std::string& operator[](const std::string& key) {
        return _data[_convert_key(key)];
    }

    // __delitem__
    void erase(const std::string& key) {
        _data.erase(_convert_key(key));
    }

    // __len__
    size_t size() const {
        return _data.size();
    }

    // __iter__: iterate over keys (matching Python dict key iteration)
    std::vector<std::string> keys() const {
        std::vector<std::string> result;
        result.reserve(_data.size());
        for (const auto& kv : _data) {
            result.push_back(kv.first);
        }
        return result;
    }

    // Standard map iteration (key-value pairs)
    auto begin() { return _data.begin(); }
    auto end() { return _data.end(); }
    auto begin() const { return _data.begin(); }
    auto end() const { return _data.end(); }

    // Python `in` operator equivalent
    bool contains(const std::string& key) const {
        return _data.find(_convert_key(key)) != _data.end();
    }
};