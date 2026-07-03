#include <fstream>
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CookiesUtil {
public:
    explicit CookiesUtil(const std::string& cookies_file) : cookies_file(cookies_file), cookies(nullptr) {}

    bool get_cookies(const json& response) {
        if (!response.contains("cookies") || !response["cookies"].is_object()) {
            return false;
        }
        cookies = response["cookies"];
        return _save_cookies();
    }

    json load_cookies() {
        std::ifstream file(cookies_file);
        if (!file.is_open()) {
            return json({});
        }
        try {
            return json::parse(file);
        } catch (const std::exception&) {
            return json({});
        }
    }

    bool set_cookies(json& request) {
        if (!cookies) {
            return false;
        }
        std::string cookie_str;
        for (auto& [key, value] : cookies->items()) {
            cookie_str += key + "=" + std::string(value);
            if (&[key, value] != &cookies->back()) {
                cookie_str += '; ';
            }
        }
        request["cookies"] = cookie_str;
        return true;
    }

private:
    bool _save_cookies() {
        std::ofstream file(cookies_file);
        if (!file.is_open() || !cookies) {
            return false;
        }
        file << cookies->dump(4);
        return true;
    }

    std::string cookies_file;
    std::optional<json> cookies;
};