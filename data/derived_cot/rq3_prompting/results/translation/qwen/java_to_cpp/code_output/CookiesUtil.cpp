#include <fstream>
#include <map>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

namespace org {
namespace example {

class CookiesUtil {
private:
    std::string cookiesFile;
    std::optional<std::map<std::string, std::string>> cookies;

    bool _saveCookies() {
        try {
            std::ofstream file(cookiesFile);
            if (!file.is_open()) return false;
            
            nlohmann::json json;
            if (cookies.has_value()) {
                for (const auto& [key, value] : *cookies) {
                    json[key] = value;
                }
            }
            file << json.dump();
            file.flush();
            return true;
        } catch (...) {
            return false;
        }
    }

public:
    explicit CookiesUtil(const std::string& cookiesFile) : cookiesFile(cookiesFile) {}

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
        std::ifstream file(cookiesFile);
        if (!file.is_open()) {
            return std::map<std::string, std::string>();
        }

        try {
            nlohmann::json json = nlohmann::json::parse(file);
            std::map<std::string, std::string> cookiesData;
            for (const auto& [key, value] : json.items()) {
                if (value.is_string()) {
                    cookiesData[key] = value.get<std::string>();
                }
            }
            return cookiesData;
        } catch (...) {
            return std::map<std::string, std::string>();
        }
    }

    void setCookies(std::map<std::string, std::string>& request) {
        std::string cookiesString;
        if (cookies.has_value()) {
            bool first = true;
            for (const auto& [key, value] : *cookies) {
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

} // namespace example
} // namespace org