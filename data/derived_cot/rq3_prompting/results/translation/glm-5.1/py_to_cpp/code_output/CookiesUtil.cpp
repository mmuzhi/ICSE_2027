#include <string>
#include <map>
#include <fstream>
#include <optional>
#include <nlohmann/json.hpp>

class CookiesUtil {
public:
    std::string cookies_file;
    std::optional<std::map<std::string, std::string>> cookies;

    CookiesUtil(const std::string& cookies_file)
        : cookies_file(cookies_file), cookies(std::nullopt) {}

    void get_cookies(const nlohmann::json& response) {
        auto& cookies_json = response["cookies"];
        cookies = std::map<std::string, std::string>();
        for (auto& [key, value] : cookies_json.items()) {
            cookies.value()[key] = value.get<std::string>();
        }
        _save_cookies();
    }

    std::map<std::string, std::string> load_cookies() {
        std::ifstream file(cookies_file);
        if (!file.is_open()) {
            return {};
        }
        nlohmann::json j = nlohmann::json::parse(file);
        std::map<std::string, std::string> result;
        for (auto& [key, value] : j.items()) {
            result[key] = value.get<std::string>();
        }
        return result;
    }

    bool _save_cookies() {
        try {
            std::ofstream file(cookies_file);
            if (!file.is_open()) {
                return false;
            }
            nlohmann::json j = cookies.value();
            file << j.dump();
            return true;
        } catch (...) {
            return false;
        }
    }

    void set_cookies(nlohmann::json& request) {
        std::string cookie_str;
        for (auto it = cookies.value().begin(); it != cookies.value().end(); ++it) {
            if (it != cookies.value().begin()) {
                cookie_str += "; ";
            }
            cookie_str += it->first + "=" + it->second;
        }
        request["cookies"] = cookie_str;
    }
};