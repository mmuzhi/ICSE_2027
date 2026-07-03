#include <map>
#include <any>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <stdexcept>
#include <cstdio>
#include <sstream>
#include <iomanip>

class AccessGatewayFilter {
public:
    AccessGatewayFilter() = default;

    bool filter(const std::map<std::string, std::any>& request) {
        std::string requestUri;
        std::string method;
        try {
            requestUri = std::any_cast<std::string>(request.at("path"));
            method = std::any_cast<std::string>(request.at("method"));
        } catch (const std::exception& e) {
            return false;
        }

        if (isStartWith(requestUri)) {
            return true;
        }

        try {
            auto token = getJwtUser(request);
            auto user = std::any_cast<std::map<std::string, std::any>>(token.at("user"));
            int level = any_to_int(user.at("level"));
            if (level > 2) {
                setCurrentUserInfoAndLog(user);
                return true;
            }
        } catch (const std::exception& e) {
            return false;
        }
        return false;
    }

private:
    bool isStartWith(const std::string& requestUri) {
        std::vector<std::string> startWith = {"/api", "/login"};
        for (const auto& s : startWith) {
            if (requestUri.starts_with(s)) {
                return true;
            }
        }
        return false;
    }

    std::map<std::string, std::any> getJwtUser(const std::map<std::string, std::any>& request) {
        auto headers = std::any_cast<std::map<std::string, std::any>>(request.at("headers"));
        auto token_map = std::any_cast<std::map<std::string, std::any>>(headers.at("Authorization"));
        auto user = std::any_cast<std::map<std::string, std::any>>(token_map.at("user"));
        std::string jwt = std::any_cast<std::string>(token_map.at("jwt"));

        std::string username = std::any_cast<std::string>(user.at("name"));

        if (jwt.starts_with(username)) {
            std::string jwtStrDate = jwt.substr(username.length());
            int year, month, day;
            if (std::sscanf(jwtStrDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
                throw std::runtime_error("Invalid date format");
            }
            std::chrono::year_month_day jwt_date{std::chrono::year(year), std::chrono::month(month), std::chrono::day(day)};

            std::time_t t = std::time(nullptr);
            std::tm local_tm;
#if defined(_WIN32)
            if (localtime_s(&local_tm, &t) != 0) {
                throw std::runtime_error("Failed to get local time");
            }
#else
            if (localtime_r(&t, &local_tm) == nullptr) {
                throw std::runtime_error("Failed to get local time");
            }
#endif
            std::chrono::year_month_day current_date{
                std::chrono::year(local_tm.tm_year + 1900),
                std::chrono::month(local_tm.tm_mon + 1),
                std::chrono::day(local_tm.tm_mday)
            };

            auto current_sys = std::chrono::sys_days(current_date);
            auto jwt_sys = std::chrono::sys_days(jwt_date);

            if (jwt_sys < current_sys - std::chrono::days(3)) {
                return {};
            }
        }
        return token_map;
    }

    void setCurrentUserInfoAndLog(const std::map<std::string, std::any>& user) {
        std::string host = std::any_cast<std::string>(user.at("address"));
        std::string username = std::any_cast<std::string>(user.at("name"));

        std::time_t t = std::time(nullptr);
        std::tm local_tm;
#if defined(_WIN32)
        if (localtime_s(&local_tm, &t) != 0) {
            throw std::runtime_error("Failed to get local time");
        }
#else
        if (localtime_r(&t, &local_tm) == nullptr) {
            throw std::runtime_error("Failed to get local time");
        }
#endif
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &local_tm);
        std::string today_str(buffer);

        std::string message = username + host + today_str;
        std::cout << message << std::endl;
    }

    int any_to_int(const std::any& a) {
        if (a.type() == typeid(int)) {
            return std::any_cast<int>(a);
        } else if (a.type() == typeid(long)) {
            return static_cast<int>(std::any_cast<long>(a));
        } else if (a.type() == typeid(long long)) {
            return static_cast<int>(std::any_cast<long long>(a));
        } else if (a.type() == typeid(short)) {
            return static_cast<int>(std::any_cast<short>(a));
        } else if (a.type() == typeid(unsigned int)) {
            return static_cast<int>(std::any_cast<unsigned int>(a));
        } else if (a.type() == typeid(unsigned long)) {
            return static_cast<int>(std::any_cast<unsigned long>(a));
        } else if (a.type() == typeid(unsigned long long)) {
            return static_cast<int>(std::any_cast<unsigned long long>(a));
        } else if (a.type() == typeid(unsigned short)) {
            return static_cast<int>(std::any_cast<unsigned short>(a));
        }
        throw std::bad_any_cast();
    }
};