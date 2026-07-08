#include <string>
#include <vector>
#include <optional>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class AccessGatewayFilter {
public:
    AccessGatewayFilter() {}

    // Returns: true if allowed, false if denied, nullopt if implicit None return
    std::optional<bool> filter(const json& request) {
        std::string request_uri = request["path"];
        std::string method = request["method"];
        (void)method; // extracted but unused, matching Python behavior

        if (is_start_with(request_uri)) {
            return true;
        }

        try {
            auto token_opt = get_jwt_user(request);
            // .value() throws std::bad_optional_access if nullopt,
            // mimicking Python's TypeError when accessing None['user']
            json token = token_opt.value();
            json user = token["user"];
            if (user["level"].get<int>() > 2) {
                set_current_user_info_and_log(user);
                return true;
            }
            return std::nullopt; // Python implicit None
        } catch (...) {
            return false;
        }
    }

    bool is_start_with(const std::string& request_uri) {
        std::vector<std::string> start_with = {"/api", "/login"};
        for (const auto& s : start_with) {
            if (request_uri.rfind(s, 0) == 0) { // equivalent to str.startswith
                return true;
            }
        }
        return false;
    }

    std::optional<json> get_jwt_user(const json& request) {
        json token = request["headers"]["Authorization"];
        json user = token["user"];
        std::string user_name = user["name"];
        std::string jwt = token["jwt"];

        if (jwt.rfind(user_name, 0) == 0) { // jwt.startswith(user_name)
            // Replicate Python's jwt.split(user_name)[1]
            std::string jwt_str_date = jwt.substr(user_name.length());

            std::tm tm = {};
            std::istringstream ss(jwt_str_date);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            if (ss.fail()) {
                throw std::runtime_error("Failed to parse date");
            }

            auto now = std::chrono::system_clock::now();
            auto now_time_t = std::chrono::system_clock::to_time_t(now);
            auto jwt_time_t = std::mktime(&tm);

            double diff_seconds = std::difftime(now_time_t, jwt_time_t);
            if (diff_seconds >= 3.0 * 24.0 * 60.0 * 60.0) { // timedelta(days=3)
                return std::nullopt;
            }
        }
        return token;
    }

    void set_current_user_info_and_log(const json& user) {
        std::string host = user["address"];
        std::string name = user["name"];

        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(
            now.time_since_epoch() % std::chrono::seconds(1)).count();

        std::tm* now_tm = std::localtime(&now_time_t);
        std::ostringstream oss;
        oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S")
            << "." << std::setfill('0') << std::setw(6) << us;

        std::string msg = name + host + oss.str();
        // Python logging.log(level=1, msg=...) — level 1 is a custom level below DEBUG
        std::cerr << "Level 1:root:" << msg << std::endl;
    }
};