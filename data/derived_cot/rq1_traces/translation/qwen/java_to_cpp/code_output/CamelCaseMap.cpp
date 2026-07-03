#include <map>
#include <list>
#include <string>
#include <cctype>
#include <algorithm>

class CamelCaseMap {
private:
    std::map<std::string, Object> data;
    std::list<std::string> insertionOrder;

    std::string _convertKey(const std::string& key) {
        if (key.empty()) {
            return "";
        }
        std::string camelCase;
        bool nextUpper = false;
        for (char c : key) {
            if (c == '_') {
                nextUpper = true;
            } else {
                if (nextUpper) {
                    camelCase.push_back(std::toupper(c));
                    nextUpper = false;
                } else {
                    camelCase.push_back(std::tolower(c));
                }
            }
        }
        return camelCase;
    }

public:
    Object get(const std::string& key) {
        std::string camelKey = _convertKey(key);
        auto it = data.find(camelKey);
        if (it != data.end()) {
            return it->second;
        }
        return Object();
    }

    void put(const std::string& key, Object value) {
        std::string camelKey = _convertKey(key);
        auto it = data.find(camelKey);
        if (it == data.end()) {
            insertionOrder.push_back(camelKey);
        }
        data[camelKey] = value;
    }

    void remove(const std::string& key) {
        std::string camelKey = _convertKey(key);
        if (!camelKey.empty()) {
            data.erase(camelKey);
            // Do not remove from insertionOrder to maintain insertion order
        }
    }

    std::list<std::string> keySet() {
        return insertionOrder;
    }

    int size() {
        return data.size();
    }
};