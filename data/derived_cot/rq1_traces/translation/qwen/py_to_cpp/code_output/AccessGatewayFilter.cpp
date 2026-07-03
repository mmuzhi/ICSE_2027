#include <map>
#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

// Structure to represent a User
struct User {
    std::string name;
    std::string address;
    int level;
};

// Structure to represent the Authorization token
struct Auth {
    User user;
    std::string jwt;
};

// Structure to represent the entire request
struct Request {
    std::string path;
    std::string method;
    std::map<std::string, Auth> headers;
};

// Class definition for the AccessGatewayFilter
class AccessGatewayFilter {
public:
    // Filter method
    bool filter(const Request& request) {
        std::string request_uri = request.path;
        std::string method = request.method;

        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            auto token = get_jwt_user(request);
            if (!token.has_value()) {
                return false;
            }

            const User& user = token.value().user;
            if (user.level > 2) {
                set_current_user_info_and_log(user);
                return true;
            }
        } catch (...) {
            return false;
        }

        return false;
    }

    // Method to check if the request URI starts with certain prefixes
    bool is_start_with(const std::string& request_uri) {
        std::vector<std::string> prefixes = {"/api", "/login"};
        for (const auto& prefix : prefixes) {
            if (request_uri.substr(0, prefix.size()) == prefix) {
                return true;
            }
        }
        return false;
    }

    // Method to get the user information from the JWT token
    std::optional<User> get_jwt_user(const Request& request) {
        try {
            if (request.headers.find("Authorization") == request.headers.end()) {
                return std::nullopt;
            }

            const Auth& auth = request.headers["Authorization"];
            if (auth.jwt.empty() || auth.user.name.empty()) {
                return std::nullopt;
            }

            if (!auth.jwt.starts_with(auth.user.name)) {
                return std::nullopt;
            }

            size_t pos = auth.jwt.find(auth.user.name);
            std::string jwt_date_str = auth.jwt.substr(pos + auth.user.name.size());

            std::istringstream ss(jwt_date_str);
            std::string date_str;
            std::getline(ss, date_str, '-'); // Split by first '-'
            if (date_str != "") {
                std::tm time = {};
                std::istringstream ss_day(date_str);
                if (!getline(ss_day, date_str, '-')) return std::nullopt;
                time.tm_year = std::stoi(date_str) - 1900; // tm_year is years since 1900
                if (!getline(ss_day, date_str, '-')) return std::nullopt;
                time.tm_mon = std::stoi(date_str) - 1; // tm_mon is 0-based
                if (!getline(ss_day, date_str, '-')) return std::nullopt;
                time.tm_mday = std::stoi(date_str);
                std::istringstream ss_time(date_str); // Assuming the rest of the string is time part
                if (!getline(ss_time, date_str, ' ')) return std::nullopt;
                time.tm_hour = std::stoi(date_str);
                if (!getline(ss_time, date_str, ':')) return std::nullopt;
                time.tm_min = std::stoi(date_str);
                if (!getline(ss_time, date_str, ':')) return std::nullopt;
                time.tm_sec = std::stoi(date_str);

                std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::tm* now_tm = std::localtime(&current_time);

                std::time_t jwt_time = std::mktime(const_cast<std::tm*>(&time));
                if (jwt_time == -1) return std::nullopt;

                std::time_t diff = std::difftime(current_time, jwt_time);
                if (diff >= 3 * 24 * 60 * 60) { // More than 3 days
                    return std::nullopt;
                }
            }
            return auth.user;
        } catch (...) {
            return std::nullopt;
        }
    }

    // Method to set the current user information and log the access
    void set_current_user_info_and_log(const User& user) {
        std::string host = user.address;
        std::string time_str = get_formatted_time();
        std::cout << user.name << host << time_str << std::endl;
    }

private:
    // Helper function to get formatted time string
    std::string get_formatted_time() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};