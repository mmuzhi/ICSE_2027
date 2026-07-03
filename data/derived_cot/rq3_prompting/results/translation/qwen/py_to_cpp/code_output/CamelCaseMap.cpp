#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class CamelCaseMap {
private:
    std::map<std::string, std::string> _data;

    std::string convert_key(const std::string& key) {
        if (key.empty()) {
            return key;
        }
        std::vector<std::string> parts;
        size_t start = 0;
        size_t end = 0;

        while (end != std::string::npos) {
            end = key.find('_');
            if (end == std::string::npos) {
                parts.push_back(key.substr(start));
                break;
            }
            parts.push_back(key.substr(start, end - start));
            start = end + 1;
        }

        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                result += std::toupper(parts[i][0]) + parts[i].substr(1);
            }
        }
        return result;
    }

public:
    CamelCaseMap() {}

    // __getitem__
    std::string& operator[](const std::string& key) {
        std::string camel_key = convert_key(key);
        return _data[camel_key];
    }

    // __setitem__
    void setitem(const std::string& key, const std::string& value) {
        std::string camel_key = convert_key(key);
        _data[camel_key] = value;
    }

    // __delitem__
    void delitem(const std::string& key) {
        std::string camel_key = convert_key(key);
        if (_data.find(camel_key) == _data.end()) {
            throw std::out_of_range("key not found");
        }
        _data.erase(camel_key);
    }

    // __iter__
    std::map<std::string, std::string>::const_iterator begin() const {
        return _data.begin();
    }

    std::map<std::string, std::string>::const_iterator end() const {
        return _data.end();
    }

    // __len__
    size_t size() const {
        return _data.size();
    }
};