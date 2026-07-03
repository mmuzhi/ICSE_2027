#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <functional>
#include <list>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cmath>
#include <cmath>
#include <cmath>

// Helper function to format current datetime
std::string get_current_datetime_string() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm now_tm = *std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
    return std::string(buffer);
}

struct User {
    std::string name;
    int level;
    std::string address;
};

struct Token {
    std::string jwt;
    User user;
};

class AccessGatewayFilter {
public:
    bool filter(const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& request) {
        std::string request_uri = request["path"];
        std::string method = request["method"];

        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            Token* token = get_jwt_user(request);
            if (token == nullptr) {
                return false;
            }

            if (token->user.level > 2) {
                set_current_user_info_and_log(token->user);
                return true;
            }
        } catch (...) {
            return false;
        }

        return false;
    }

    bool is_start_with(const std::string& request_uri) {
        std::vector<std::string> prefixes = {"/api", "/login"};
        for (const auto& s : prefixes) {
            if (request_uri.substr(0, s.length()) == s) {
                return true;
            }
        }
        return false;
    }

    Token* get_jwt_user(const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>& request) {
        auto it = request.find("headers");
        if (it == request.end()) {
            return nullptr;
        }

        auto& headers = it->second;
        auto auth_it = headers.find("Authorization");
        if (auth_it == headers.end()) {
            return nullptr;
        }

        auto& auth = auth_it->second;
        auto user_it = auth.find("user");
        if (user_it == auth.end()) {
            return nullptr;
        }

        auto& user_dict = user_it->second;
        auto name_it = user_dict.find("name");
        if (name_it == user_dict.end()) {
            return nullptr;
        }

        User user;
        user.name = name_it->second;

        auto level_it = user_dict.find("level");
        if (level_it == user_dict.end()) {
            return nullptr;
        }

        try {
            user.level = std::stoi(level_it->second);
        } catch (...) {
            return nullptr;
        }

        auto address_it = user_dict.find("address");
        if (address_it != user_dict.end()) {
            user.address = address_it->second;
        }

        auto jwt_it = auth.find("jwt");
        if (jwt_it == auth.end()) {
            return nullptr;
        }

        std::string jwt = jwt_it->second;
        if (!jwt.starts_with(user.name)) {
            return nullptr;
        }

        std::string jwt_str_date = jwt.substr(user.name.length());
        std::istringstream iss(jwt_str_date);
        std::tm date_tm = {};
        iss >> std::get_time(&date_tm, "%Y-%m-%d");
        if (iss.fail() || iss.eof() || iss.peek() != EOF) {
            return nullptr;
        }

        std::time_t date_time_t = std::mktime(&date_tm);
        if (date_time_t == std::tm()) {
            return nullptr;
        }

        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::chrono::days diff = std::chrono::duration_cast<std::chrono::days>(now - date_time_t);

        if (diff.count() >= 3) {
            return nullptr;
        }

        Token* token = new Token();
        token->jwt = jwt;
        token->user = user;
        return token;
    }

    void set_current_user_info_and_log(const User& user) {
        std::string log_message = user.name + user.address + get_current_datetime_string();
        std::cerr << log_message << std::endl;
    }
};