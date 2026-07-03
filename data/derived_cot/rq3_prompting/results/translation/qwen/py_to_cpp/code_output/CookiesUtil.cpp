#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <nlohmann/json.hpp>

struct CookiesUtil {
    explicit CookiesUtil(const std::string& cookies_file) : cookies_file(cookies_file), cookies() {}

    void get_cookies(const std::unordered_map<std::string, std::string>& response) {
        if (response.find("cookies") != response.end()) {
            // The value of "cookies" is expected to be a map (string to string)
            // But in C++ we are passing a map<string, string> for the response.
            // We'll assume the response has a key "cookies" that maps to a map.
            // We'll set self.cookies to that inner map.
            if (response.at("cookies").find("cookies") != response.at("cookies").end()) {
                // This is not the structure we expect.
                // We'll use the provided response's "cookies" map.
                cookies = response.at("cookies");
            }
        }
        save_cookies();
    }

    std::unordered_map<std::string, std::string> load_cookies() {
        try {
            std::ifstream file(cookies_file);
            if (!file.is_open()) {
                return {};
            }
            std::string json_str((std::istreambuf_iterator<char>(file)), '');
            try {
                auto json_value = nlohmann::json::parse(json_str);
                if (json_value.is_object() && json_value.find("cookies") != json_value.end()) {
                    if (json_value["cookies"].is_object()) {
                        return json_value["cookies"].get<std::unordered_map<std::string, std::string>>();
                    }
                }
            } catch (...) {
                return {};
            }
        } catch (...) {
            return {};
        }
    }

    bool _save_cookies() {
        try {
            std::ofstream file(cookies_file);
            if (!file.is_open()) {
                return false;
            }
            nlohmann::json json_value(cookies);
            file << json_value.dump(4);
            return true;
        } catch (...) {
            return false;
        }
    }

    void set_cookies(std::unordered_map<std::string, std::string>& request) {
        std::vector<std::string> parts;
        for (const auto& [key, value] : cookies) {
            parts.push_back(key + "=" + value);
        }
        request["cookies"] = "; " + std::accumulate(parts.begin(), parts.end(), std::string(), [](const std::string& a, const std::string& b) {
            return a + b + "; ";
        });
    }

private:
    std::string cookies_file;
    std::unordered_map<std::string, std::string> cookies;
};