#include <map>
#include <string>
#include <any>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
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
            std::map<std::string, std::any> token = getJwtUser(request);
            std::map<std::string, std::any>& user = std::any_cast<std::map<std::string, std::any>&>(token.at("user"));
            if (std::any_cast<int>(user.at("level")) > 2) {
                setCurrentUserInfoAndLog(user);
                return true;
            }
        } catch (const std::exception& e) {
            return false;
        }
        return false;
    }

    bool isStartWith(const std::string& requestUri) {
        std::string startWith[] = {"/api", "/login"};
        for (const auto& s : startWith) {
            if (requestUri.substr(0, s.size()) == s) {
                return true;
            }
        }
        return false;
    }

    std::map<std::string, std::any> getJwtUser(std::map<std::string, std::any>& request) {
        std::map<std::string, std::any>& headers = std::any_cast<std::map<std::string, std::any>&>(request.at("headers"));
        std::map<std::string, std::any>& token = std::any_cast<std::map<std::string, std::any>&>(headers.at("Authorization"));
        std::map<std::string, std::any>& user = std::any_cast<std::map<std::string, std::any>&>(token.at("user"));
        std::string jwt = std::any_cast<std::string>(token.at("jwt"));
        std::string name = std::any_cast<std::string>(user.at("name"));

        if (jwt.substr(0, name.size()) == name) {
            std::string jwtStrDate = jwt.substr(name.size());
            std::tm tm = {};
            std::istringstream ss(jwtStrDate);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            if (ss.fail()) {
                throw std::runtime_error("Failed to parse date");
            }
            tm.tm_hour = 0;
            tm.tm_min = 0;
            tm.tm_sec = 0;
            std::time_t jwtTime = std::mktime(&tm);

            auto now = std::time(nullptr);
            std::tm nowTm = *std::localtime(&now);
            nowTm.tm_hour = 0;
            nowTm.tm_min = 0;
            nowTm.tm_sec = 0;
            nowTm.tm_mday -= 3;
            std::time_t threeDaysAgo = std::mktime(&nowTm);

            if (threeDaysAgo > jwtTime) {
                return {};
            }
        }
        return token;
    }

    void setCurrentUserInfoAndLog(std::map<std::string, std::any>& user) {
        std::string host = std::any_cast<std::string>(user.at("address"));
        std::string name = std::any_cast<std::string>(user.at("name"));

        auto now = std::time(nullptr);
        std::tm nowTm = *std::localtime(&now);
        std::ostringstream dateStream;
        dateStream << std::put_time(&nowTm, "%Y-%m-%d");

        std::string message = name + host + dateStream.str();
        std::cout << message << std::endl;
    }
};