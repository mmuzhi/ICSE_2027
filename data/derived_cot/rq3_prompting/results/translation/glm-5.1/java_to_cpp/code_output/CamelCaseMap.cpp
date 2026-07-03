#pragma once

#include <string>
#include <vector>
#include <any>
#include <optional>
#include <algorithm>
#include <cctype>

class CamelCaseMap {
private:
    std::vector<std::pair<std::optional<std::string>, std::any>> data;

    std::optional<std::string> _convertKey(const std::optional<std::string>& key) {
        if (!key.has_value()) {
            return std::nullopt;
        }
        return _toCamelCase(key.value());
    }

    static std::vector<std::string> split_(const std::string& s) {
        std::vector<std::string> parts;
        size_t start = 0;
        size_t end;
        bool found = false;
        while ((end = s.find('_', start)) != std::string::npos) {
            found = true;
            parts.push_back(s.substr(start, end - start));
            start = end + 1;
        }
        parts.push_back(s.substr(start));
        if (found) {
            while (!parts.empty() && parts.back().empty()) {
                parts.pop_back();
            }
        }
        return parts;
    }

    static std::string _toCamelCase(const std::string& key) {
        std::vector<std::string> parts = split_(key);
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); i++) {
            std::string first = parts[i].substr(0, 1);
            first[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(first[0])));
            std::string rest = parts[i].substr(1);
            for (char& c : rest) {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
            result += first + rest;
        }
        return result;
    }

public:
    std::any* get(const std::optional<std::string>& key) {
        auto converted = _convertKey(key);
        auto it = std::find_if(data.begin(), data.end(),
            [&](const auto& p) { return p.first == converted; });
        if (it != data.end()) return &(it->second);
        return nullptr;
    }

    void put(const std::optional<std::string>& key, std::any value) {
        auto converted = _convertKey(key);
        auto it = std::find_if(data.begin(), data.end(),
            [&](const auto& p) { return p.first == converted; });
        if (it != data.end()) {
            it->second = std::move(value);
        } else {
            data.emplace_back(converted, std::move(value));
        }
    }

    void remove(const std::optional<std::string>& key) {
        auto converted = _convertKey(key);
        auto it = std::find_if(data.begin(), data.end(),
            [&](const auto& p) { return p.first == converted; });
        if (it != data.end()) {
            data.erase(it);
        }
    }

    std::vector<std::optional<std::string>> keySet() {
        std::vector<std::optional<std::string>> keys;
        keys.reserve(data.size());
        for (const auto& [k, v] : data) {
            keys.push_back(k);
        }
        return keys;
    }

    int size() {
        return static_cast<int>(data.size());
    }
};