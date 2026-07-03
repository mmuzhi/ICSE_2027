#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <optional>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

struct User {
    std::string name;
    int level;
    std::string address;
};

struct Authorization {
    User user;
    std::string jwt;
};

struct Request {
    std::string path;
    std::string method;
    std::map<std::string, Authorization> headers;
};

class AccessGatewayFilter {
public:
    AccessGatewayFilter() = default;

    bool filter(const Request& request) {
        const std::string& request_uri = request.path;
        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            std::optional<Authorization> token = get_jwt_user(request);
            if (!token) {
                return false;
            }
            const User& user = token->user;
            if (user.level > 2) {
                set_current_user_info_and_log(user);
                return true;
            } else {
                return false;
            }
        } catch (...) {
            return false;
        }
    }

    bool is_start_with(const std::string& request_uri) const {
        static const std::vector<std::string> prefixes = {"/api", "/login"};
        for (const std::string& prefix : prefixes) {
            if (request_uri.size() >= prefix.size() && request_uri.substr(0, prefix.size()) == prefix) {
                return true;
            }
        }
        return false;
    }

    std::optional<Authorization> get_jwt_user(const Request& request) const {
        Authorization auth = request.headers.at("Authorization");
        const User& user = auth.user;
        const std::string& jwt = auth.jwt;

        if (jwt.find(user.name) == 0) {
            std::string jwt_str_date = jwt.substr(user.name.length());
            std::tm tm = {};
            std::istringstream ss(jwt_str_date);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            if (ss.fail()) {
                throw std::runtime_error("Failed to parse date");
            }
            tm.tm_isdst = -1;
            std::time_t tt = std::mktime(&tm);
            if (tt == -1) {
                throw std::runtime_error("mktime failed");
            }
            auto jwt_time = std::chrono::system_clock::from_time_t(tt);
            auto now = std::chrono::system_clock::now();
            auto diff = now - jwt_time;
            if (diff >= std::chrono::hours(24 * 3)) {
                return std::nullopt;
            }
        }
        return auth;
    }

    void set_current_user_info_and_log(const User& user) const {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time_t);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
        std::string now_str(buffer);

        std::string message = user.name + user.address + now_str;
        std::clog << message << std::endl;
    }
};