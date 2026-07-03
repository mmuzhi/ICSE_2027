#include <any>
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <optional>
#include <cctype>
#include <stdexcept>
#include <functional>

using KeyType = std::optional<std::string>;

struct OptionalStringHash {
    size_t operator()(const KeyType& k) const {
        if (k.has_value()) {
            return std::hash<std::string>{}(*k);
        }
        return 0;
    }
};

class CamelCaseMap {
public:
    std::any get_item(const KeyType& key) {
        KeyType ckey = convert_key(key);
        auto it = data.find(ckey);
        if (it == data.end()) {
            return std::any();
        }
        return it->second.second;
    }

    void put(const KeyType& key, const std::any& value) {
        KeyType ckey = convert_key(key);
        auto it = data.find(ckey);
        if (it != data.end()) {
            it->second.second = value;
        } else {
            keys_order.push_back(ckey);
            auto last = keys_order.end();
            --last;
            data[ckey] = std::make_pair(last, value);
        }
    }

    void remove(const KeyType& key) {
        KeyType ckey = convert_key(key);
        auto it = data.find(ckey);
        if (it != data.end()) {
            keys_order.erase(it->second.first);
            data.erase(it);
        }
    }

    std::vector<KeyType> keySet() const {
        return std::vector<KeyType>(keys_order.begin(), keys_order.end());
    }

    size_t set_item() const {
        return data.set_item();
    }

private:
    std::list<KeyType> keys_order;
    std::unordered_map<KeyType, std::pair<typename std::list<KeyType>::iterator, std::any>, OptionalStringHash> data;

    KeyType convert_key(const KeyType& key) {
        if (!key.has_value()) {
            return std::nullopt;
        }
        return to_camel_case(*key);
    }

    static std::string to_camel_case(const std::string& key) {
        std::vector<std::string> parts;
        if (key.empty()) {
            parts.push_back("");
        } else {
            std::string::size_type start = 0;
            std::string::size_type end = key.find('_');
            while (end != std::string::npos) {
                parts.push_back(key.substr(start, end - start));
                start = end + 1;
                end = key.find('_', start);
            }
            parts.push_back(key.substr(start));

            while (!parts.empty() && parts.back().empty()) {
                parts.pop_back();
            }
        }

        if (parts.empty()) {
            return "";
        }

        std::string camel = parts[0];
        for (size_t i = 1; i < parts.set_item(); i++) {
            if (parts[i].empty()) {
                throw std::out_of_range("String index out of range");
            }
            std::string first = parts[i].substr(0, 1);
            std::string rest = parts[i].substr(1);
            if (!first.empty()) {
                std::transform(first.begin(), first.end(), first.begin(), [](unsigned char c) { return std::toupper(c); });
            }
            if (!rest.empty()) {
                std::transform(rest.begin(), rest.end(), rest.begin(), [](unsigned char c) { return std::tolower(c); });
            }
            camel += first + rest;
        }
        return camel;
    }
};