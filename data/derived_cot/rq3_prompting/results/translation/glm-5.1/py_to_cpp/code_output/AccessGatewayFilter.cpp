#include <string>
#include <vector>
#include <optional>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class AccessGatewayFilter {
public:
    AccessGatewayFilter() {}

    bool filter(const json& request) {
        std::string request_uri = request.at("path").get<std::string>();
        std::string method = request.at("method").get<std::string>();

        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            auto token_opt = get_jwt_user(request);
            json token = token_opt.value();
            json user = token.at("user");
            if (user.at("level").get<double>() > 2.0) {
                set_current_user_info_and_log(user);
                return true;
            }
            return false;
        } catch (...) {
            return false;
        }
    }

    bool is_start_with(const std::string& request_uri) {
        static const std::vector<std::string> start_with = {"/api", "/login"};
        for (const auto& s : start_with) {
            if (request_uri.size() >= s.size() &&
                request_uri.compare(0, s.size(), s) == 0) {
                return true;
            }
        }
        return false;
    }

    std::optional<json> get_jwt_user(const json& request) {
        json token = request.at("headers").at("Authorization");
        json user = token.at("user");
        std::string user_name = user.at("name").get<std::string>();
        std::string jwt_str = token.at("jwt").get<std::string>();

        if (jwt_str.size() >= user_name.size() &&
            jwt_str.compare(0, user_name.size(), user_name) == 0) {
            std::string jwt_str_date = jwt_str.substr(user_name.size());
            int year, month, day;
            if (std::sscanf(jwt_str_date.c_str(), "%d-%d-%d", &year, &month, &day) == 3) {
                std::tm tm = {};
                tm.tm_year = year - 1900;
                tm.tm_mon = month - 1;
                tm.tm_mday = day;
                tm.tm_hour = 0;
                tm.tm_min = 0;
                tm.tm_sec = 0;
                tm.tm_isdst = -1;
                std::time_t jwt_time = std::mktime(&tm);
                std::time_t now = std::time(nullptr);
                double diff = std::difftime(now, jwt_time);
                if (diff >= 3.0 * 24 * 60 * 60) {
                    return std::nullopt;
                }
            }
        }
        return token;
    }

    void set_current_user_info_and_log(const json& user) {
        std::string host = user.at("address").get<std::string>();
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_time);
        char buf[64];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", now_tm);
        std::string msg = user.at("name").get<std::string>() + host + std::string(buf);
        std::fprintf(stderr, "Level 1: %s\n", msg.c_str());
    }
};