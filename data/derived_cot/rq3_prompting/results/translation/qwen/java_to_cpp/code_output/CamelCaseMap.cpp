#include <map>
#include <list>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <any>

class CamelCaseMap {
private:
    std::map<std::string, std::any> dataMap;
    std::list<std::string> insertionOrder;

    std::string _toCamelCase(const std::string& key) {
        if (key.empty()) {
            return key;
        }
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

        std::string camelCase = parts[0];
        for (int i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                camelCase += std::toupper(parts[i][0]);
                camelCase += parts[i].substr(1);
            }
        }
        return camelCase;
    }

public:
    Object get(const std::string& key) {
        if (key.empty()) {
            return Object(); // Assuming Object is a default constructible type
        }
        std::string camelKey = _toCamelCase(key);
        return dataMap[camelKey];
    }

    void put(const std::string& key, const Object& value) {
        if (key.empty()) {
            return;
        }
        std::string camelKey = _toCamelCase(key);
        if (dataMap.find(camelKey) == dataMap.end()) {
            dataMap[camelKey] = value;
            insertionOrder.push_back(camelKey);
        } else {
            dataMap[camelKey] = value;
        }
    }

    void remove(const std::string& key) {
        if (key.empty()) {
            return;
        }
        std::string camelKey = _toCamelCase(key);
        if (dataMap.find(camelKey) != dataMap.end()) {
            dataMap.erase(camelKey);
        }
    }

    std::vector<std::string> keySet() {
        std::vector<std::string> keys;
        for (const auto& key : insertionOrder) {
            keys.push_back(key);
        }
        return keys;
    }

    int size() {
        return dataMap.size();
    }
};