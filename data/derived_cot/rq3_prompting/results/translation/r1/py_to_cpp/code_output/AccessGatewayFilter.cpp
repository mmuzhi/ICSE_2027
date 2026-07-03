#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

struct User {
    std::string name;
    int level = 0;
    std::string address;
};

struct Authorization {
    User user;
    std::string jwt;
};

struct Headers {
    Authorization authorization;
};

struct Request {
    std::string path;
    std::string method;
    Headers headers;
};

class AccessGatewayFilter {
public:
    bool filter(const Request& request) {
        std::string request_uri = request.path;
        std::string method = request.method;

        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            Authorization token = get_jwt_user(request);
            User user = token.user;
            if (user.level > 2) {
                set_current_user_info_and_log(user);
                return true;
            }
        } catch (...) {
            return false;
        }
        return false;
    }

    bool is_start_with(const std::string& request_uri) {
        std::vector<std::string> prefixes = {"/api", "/login"};
        for (const auto& prefix : prefixes) {
            if (request_uri.substr(0, prefix.size()) == prefix) {
                return true;
            }
        }
        return false;
    }

    Authorization get_jwt_user(const Request& request) {
        const Headers& headers = request.headers;
        const Authorization& token = headers.authorization;   // assume present
        const User& user = token.user;

        if (token.jwt.find(user.name) == 0) {
            std::string date_str = token.jwt.substr(user.name.size());
            std::tm tm = {};
            std::stringstream ss(date_str);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            if (ss.fail()) {
                throw std::runtime_error("invalid date format");
            }
            auto jwt_date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            auto today = std::chrono::system_clock::now();
            auto diff = today - jwt_date;
            if (diff >= std::chrono::hours(3 * 24)) {
                throw std::runtime_error("token expired");
            }
        }
        return token;
    }

    void set_current_user_info_and_log(const User& user) {
        std::string host = user.address;
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        std::string timestamp = ss.str();
        std::cout << user.name << host << timestamp << std::endl;
    }
};