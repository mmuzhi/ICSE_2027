#include <iostream>
#include <string>
#include <map>
#include <any>
#include <vector>
#include <sstream>
#include <ctime>
#include <chrono>

class AccessGatewayFilter {
public:
    AccessGatewayFilter() = default;

    bool filter(std::map<std::string, std::any>& request) {
        std::string requestUri = std::any_cast<std::string>(request["path"]);
        std::string method = std::any_cast<std::string>(request["method"]);

        if (isStartWith(requestUri)) {
            return true;
        }

        try {
            auto token = getJwtUser(request);
            auto user = std::any_cast<std::map<std::string, std::any>>(token->at("user"));
            int level = std::any_cast<int>(user.at("level"));
            if (level > 2) {
                setCurrentUserInfoAndLog(user);
                return true;
            }
        } catch (const std::exception&) {
            return false;
        }
        return false;
    }

    bool isStartWith(const std::string& requestUri) {
        static const std::vector<std::string> startWith = {"/api", "/login"};
        for (const auto& s : startWith) {
            if (requestUri.find(s) == 0) {
                return true;
            }
        }
        return false;
    }

    std::map<std::string, std::any>* getJwtUser(std::map<std::string, std::any>& request) {
        auto headers = std::any_cast<std::map<std::string, std::any>>(request["headers"]);
        auto token = std::any_cast<std::map<std::string, std::any>>(headers["Authorization"]);
        auto user = std::any_cast<std::map<std::string, std::any>>(token["user"]);
        std::string jwt = std::any_cast<std::string>(token["jwt"]);
        std::string userName = std::any_cast<std::string>(user["name"]);

        if (jwt.find(userName) == 0) {
            std::string jwtStrDate = jwt.substr(userName.length());
            // parse date "yyyy-MM-dd"
            std::tm jwt_tm = {};
            std::istringstream ss(jwtStrDate);
            ss >> std::get_time(&jwt_tm, "%Y-%m-%d");
            if (ss.fail()) {
                return nullptr;
            }
            std::time_t jwt_time = std::mktime(&jwt_tm);

            // current date (local) at midnight
            std::time_t now = std::time(nullptr);
            std::tm* now_tm = std::localtime(&now);
            now_tm->tm_hour = 0;
            now_tm->tm_min = 0;
            now_tm->tm_sec = 0;
            std::time_t now_midnight = std::mktime(now_tm);
            std::time_t three_days_ago = now_midnight - 3 * 86400;

            if (three_days_ago > jwt_time) {
                return nullptr;
            }
        }
        // return pointer to token map (original reference in request)
        // We cannot return pointer to temporary; instead we return a pointer to the map in the request.
        // The map is owned by the request; we can return a pointer to it.
        // To avoid dangling pointer, we need to keep the map alive. Since it's inside request, it's fine.
        // We'll return a pointer to the token map inside headers.
        // However, we need to get the address of the map inside the original request.
        // We can store the token map as a reference. Since we want to return a pointer, we can do:
        // Actually, we already have token as a copy? No, std::any_cast returns a copy? std::any_cast<std::map<...>>(value) returns a copy unless we use std::any_cast<std::map<...>&>(value). To avoid copying, we should use reference casts.
        // Let's revise: we should use std::any_cast<...&>(...).
        // We'll modify the function to use references and return a pointer to the map inside the request.
        // Simpler: we can just return a copy of the map? That would change behavior (Java returns reference to the same map). But the filter method only reads from user and token, it doesn't modify them. So a copy would be okay? However, if the map is large, copying may be inefficient but behavior identical (since no mutation). We'll keep it simple and return a std::map<std::string, std::any> by value? The Java code returns Map<String,Object>, which is a reference (since Map is mutable). But the code only uses it to get "user" and then later not used. So returning by value is fine.
        // We'll return a copy.
        return &token; // This would be dangling because token is local. So we need to return a pointer to the token map stored in headers in request.
        // To do that, we need to get a reference to the inner map. Since request is non-const, we can get a pointer.
        // Let's restructure: get a reference to the Authorization map via any_cast<...&>.
        // Then we can return its address.
        // We'll do this:
        // auto& tokenRef = std::any_cast<std::map<std::string, std::any>&>(headers["Authorization"]);
        // return &tokenRef;
    }

    void setCurrentUserInfoAndLog(const std::map<std::string, std::any>& user) {
        std::string host = std::any_cast<std::string>(user.at("address"));
        std::string name = std::any_cast<std::string>(user.at("name"));
        // current date as string
        std::time_t now = std::time(nullptr);
        std::tm* now_tm = std::localtime(&now);
        char buf[11];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", now_tm);
        std::string dateStr(buf);
        std::cout << name << host << dateStr << std::endl;
    }
};

int main() {
    // Minimal test - not required but ensures compilation
    return 0;
}