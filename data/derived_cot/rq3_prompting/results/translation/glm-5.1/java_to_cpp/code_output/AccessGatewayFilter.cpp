#include <iostream>
#include <string>
#include <map>
#include <any>
#include <chrono>
#include <ctime>
#include <vector>
#include <cstdio>
#include <stdexcept>

class AccessGatewayFilter {
public:
    AccessGatewayFilter() {}

    bool filter(std::map<std::string, std::any>& request) {
        std::string requestUri = std::any_cast<std::string>(request.at("path"));
        std::string method = std::any_cast<std::string>(request.at("method"));

        if (isStartWith(requestUri)) {
            return true;
        }

        try {
            auto token = std::any_cast<std::map<std::string, std::any>>(getJwtUser(request));
            auto user = std::any_cast<std::map<std::string, std::any>>(token.at("user"));
            if (std::any_cast<int>(user.at("level")) > 2) {
                setCurrentUserInfoAndLog(user);
                return true;
            }
        } catch (...) {
            return false;
        }
        return false;
    }

    bool isStartWith(const std::string& requestUri) {
        std::vector<std::string> startWith = {"/api", "/login"};
        for (const auto& s : startWith) {
            if (requestUri.rfind(s, 0) == 0) {
                return true;
            }
        }
        return false;
    }

    std::any getJwtUser(std::map<std::string, std::any>& request) {
        auto headers = std::any_cast<std::map<std::string, std::any>>(request.at("headers"));
        auto token = std::any_cast<std::map<std::string, std::any>>(headers.at("Authorization"));
        auto user = std::any_cast<std::map<std::string, std::any>>(token.at("user"));
        std::string jwt = std::any_cast<std::string>(token.at("jwt"));
        std::string name = std::any_cast<std::string>(user.at("name"));

        if (jwt.rfind(name, 0) == 0) {
            std::string jwtStrDate = jwt.substr(name.length());
            int year, month, day;
            if (std::sscanf(jwtStrDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
                throw std::runtime_error("Invalid date format");
            }

            std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm now_tm = *std::localtime(&now_time);
            now_tm.tm_hour = 0;
            now_tm.tm_min = 0;
            now_tm.tm_sec = 0;
            now_tm.tm_isdst = -1;
            std::mktime(&now_tm);

            std::tm three_days_ago_tm = now_tm;
            three_days_ago_tm.tm_mday -= 3;
            three_days_ago_tm.tm_isdst = -1;
            std::time_t three_days_ago = std::mktime(&three_days_ago_tm);

            std::tm jwt_tm = {};
            jwt_tm.tm_year = year - 1900;
            jwt_tm.tm_mon = month - 1;
            jwt_tm.tm_mday = day;
            jwt_tm.tm_isdst = -1;
            std::time_t jwt_time = std::mktime(&jwt_tm);

            if (three_days_ago > jwt_time) {
                return {};
            }
        }
        return token;
    }

    void setCurrentUserInfoAndLog(std::map<std::string, std::any>& user) {
        std::string host = std::any_cast<std::string>(user.at("address"));
        std::string name = std::any_cast<std::string>(user.at("name"));

        std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm now_tm = *std::localtime(&now_time);
        char date_buf[16];
        std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &now_tm);

        std::cout << name << host << date_buf << std::endl;
    }
};