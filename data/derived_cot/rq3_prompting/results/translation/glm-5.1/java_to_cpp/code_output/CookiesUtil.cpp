#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <fstream>
#include <nlohmann/json.hpp>

class CookiesUtil {
private:
    std::string cookiesFile;
    std::optional<std::unordered_map<std::string, std::string>> cookies;

    bool _saveCookies() {
        try {
            std::ofstream file(cookiesFile);
            if (!file.is_open()) return false;
            nlohmann::json jsonObject = nlohmann::json::object();
            if (cookies.has_value()) {
                for (const auto& [key, value] : cookies.value()) {
                    jsonObject[key] = value;
                }
            }
            file << jsonObject.dump();
            file.flush();
            return true;
        } catch (...) {
            return false;
        }
    }

public:
    CookiesUtil(const std::string& cookiesFile)
        : cookiesFile(cookiesFile), cookies(std::nullopt) {}

    void getCookies(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& response) {
        auto it = response.find("cookies");
        if (it != response.end()) {
            this->cookies = it->second;
        } else {
            this->cookies = std::nullopt;
        }
        _saveCookies();
    }

    std::unordered_map<std::string, std::string> loadCookies() {
        try {
            std::ifstream reader(cookiesFile);
            if (!reader.is_open()) return {};
            nlohmann::json jsonObject = nlohmann::json::parse(reader);
            std::unordered_map<std::string, std::string> cookiesData;
            for (auto& [key, value] : jsonObject.items()) {
                cookiesData[key] = value.get<std::string>();
            }
            return cookiesData;
        } catch (...) {
            return {};
        }
    }

    void setCookies(std::unordered_map<std::string, std::string>& request) {
        std::string cookiesString;
        if (cookies.has_value()) {
            bool first = true;
            for (const auto& [key, value] : cookies.value()) {
                if (!first) {
                    cookiesString += "; ";
                }
                cookiesString += key + "=" + value;
                first = false;
            }
        }
        request["cookies"] = cookiesString;
    }
};