#ifndef COOKIES_UTIL_H
#define COOKIES_UTIL_H

#include <string>
#include <map>
#include <optional>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

class CookiesUtil {
private:
    std::string cookiesFile;
    std::optional<std::map<std::string, std::string>> cookies;

    bool _saveCookies() {
        try {
            std::ofstream file(cookiesFile);
            if (!file.is_open()) {
                return false;
            }
            nlohmann::json jsonObject = nlohmann::json::object();
            if (cookies.has_value()) {
                for (const auto& [key, value] : cookies.value()) {
                    jsonObject[key] = value;
                }
            }
            file << jsonObject.dump();
            file.flush();
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

public:
    CookiesUtil(const std::string& cookiesFile)
        : cookiesFile(cookiesFile) {}

    void getCookies(std::map<std::string, std::map<std::string, std::string>>& response) {
        auto it = response.find("cookies");
        if (it != response.end()) {
            cookies = it->second;
        } else {
            cookies = std::nullopt;
        }
        _saveCookies();
    }

    std::map<std::string, std::string> loadCookies() {
        try {
            std::ifstream file(cookiesFile);
            if (!file.is_open()) {
                return {};
            }
            nlohmann::json jsonObject;
            file >> jsonObject;
            std::map<std::string, std::string> cookiesData;
            for (auto& [key, value] : jsonObject.items()) {
                cookiesData[key] = value.get<std::string>();
            }
            return cookiesData;
        } catch (const std::exception& e) {
            return {};
        }
    }

    void setCookies(std::map<std::string, std::string>& request) {
        std::ostringstream cookiesString;
        bool first = true;
        if (cookies.has_value()) {
            for (const auto& [key, value] : cookies.value()) {
                if (!first) {
                    cookiesString << "; ";
                }
                cookiesString << key << "=" << value;
                first = false;
            }
        }
        request["cookies"] = cookiesString.str();
    }
};

#endif // COOKIES_UTIL_H