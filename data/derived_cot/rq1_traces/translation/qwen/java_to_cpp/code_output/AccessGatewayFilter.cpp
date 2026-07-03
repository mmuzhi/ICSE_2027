#include <unordered_map>
#include <any>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

// Helper function to safely retrieve and cast values from a map
template <typename T>
T getFromMap(const std::unordered_map<std::string, std::any>& map, const std::string& key) {
    auto it = map.find(key);
    if (it == map.end()) {
        throw std::runtime_error("Key not found: " + key);
    }
    try {
        return std::any_cast<T>(it->second);
    } catch (const std::bad_any_cast& e) {
        throw std::runtime_error("Invalid type for key '" + key + "': expected type of " + 
                               typeid(T).name());
    }
}

class AccessGatewayFilter {
public:
    AccessGatewayFilter() {}

    bool filter(std::unordered_map<std::string, std::any> request) {
        try {
            std::string requestUri = getFromMap<std::string>(request, "path");
            std::string method = getFromMap<std::string>(request, "method");

            if (isStartWith(requestUri)) {
                return true;
            }

            try {
                std::unordered_map<std::string, std::any> token = getJwtUser(request);
                std::unordered_map<std::string, std::any> user = getFromMap<std::unordered_map<std::string, std::any>>(token, "user");
                int level = getFromMap<int>(user, "level");
                if (level > 2) {
                    setCurrentUserInfoAndLog(user);
                    return true;
                }
            } catch (...) {
                return false;
            }
            return false;
        } catch (...) {
            return false;
        }
    }

    bool isStartWith(const std::string& requestUri) {
        std::vector<std::string> startWith = {"/api", "/login"};
        for (const auto& s : startWith) {
            if (requestUri.substr(0, s.length()) == s) {
                return true;
            }
        }
        return false;
    }

    std::unordered_map<std::string, std::any> getJwtUser(const std::unordered_map<std::string, std::any>& request) {
        try {
            std::unordered_map<std::string, std::any> headers = getFromMap<std::unordered_map<std::string, std::any>>(request, "headers");
            std::unordered_map<std::string, std::any> tokenMap = getFromMap<std::unordered_map<std::string, std::any>>(headers, "Authorization");
            std::unordered_map<std::string, std::any> user = getFromMap<std::unordered_map<std::string, std::any>>(tokenMap, "user");
            std::string jwt = getFromMap<std::string>(tokenMap, "jwt");
            std::string name = getFromMap<std::string>(user, "name");

            if (jwt.substr(0, name.length()) == name) {
                std::string jwtDateStr = jwt.substr(name.length());
                std::tm t = {};
                char* ptr = std::strptime(jwtDateStr.c_str(), "%Y-%m-%d", &t);
                if (ptr == nullptr || ptr != jwtDateStr.c_str() + jwtDateStr.size()) {
                    return {};
                }

                std::time_t time_val = std::mktime(&t);
                std::time_t now = std::time(nullptr);
                std::tm today = *std::localtime(&now);
                today.tm_mday -= 3;
                std::mktime(&today); // Normalize
                std::time_t three_days_ago = std::mktime(&today);

                if (time_val < three_days_ago) {
                    return {};
                }
            }
            return tokenMap;
        } catch (...) {
            return {};
        }
    }

    void setCurrentUserInfoAndLog(const std::unordered_map<std::string, std::any>& user) {
        std::string host = getFromMap<std::string>(user, "address");
        std::string name = getFromMap<std::string>(user, "name");
        std::string currentDate = getCurrentDate();
        std::cout << name << host << currentDate << std::endl;
    }

    std::string getCurrentDate() {
        std::time_t now = std::time(nullptr);
        std::tm* now_tm = std::localtime(&now);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", now_tm);
        return std::string(buffer);
    }
};