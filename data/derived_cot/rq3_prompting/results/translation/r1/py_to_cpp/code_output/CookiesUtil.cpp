#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CookiesUtil {
private:
    std::string cookies_file;
    std::optional<std::map<std::string, std::string>> cookies;

public:
    CookiesUtil(const std::string& cookies_file)
        : cookies_file(cookies_file), cookies(std::nullopt) {}

    void get_cookies(const json& reponse) {
        cookies = reponse.at("cookies").get<std::map<std::string, std::string>>();
        _save_cookies();
    }

    std::map<std::string, std::string> load_cookies() {
        std::ifstream file(cookies_file);
        if (!file.is_open()) {
            return {};
        }
        json j;
        try {
            file >> j;
            if (j.is_object()) {
                return j.get<std::map<std::string, std::string>>();
            }
        } catch (...) {
            // parse error, fall through
        }
        return {};
    }

    bool _save_cookies() {
        if (!cookies.has_value()) {
            return false;
        }
        try {
            std::ofstream file(cookies_file);
            if (!file.is_open()) {
                return false;
            }
            json j = cookies.value();
            file << j.dump(); // compact output, same as Python json.dump without indent
            file.close();
            return true;
        } catch (...) {
            return false;
        }
    }

    void set_cookies(json& request) {
        if (!cookies.has_value()) {
            throw std::runtime_error("'NoneType' object has no attribute 'items'");
        }
        std::ostringstream oss;
        bool first = true;
        for (const auto& [key, value] : cookies.value()) {
            if (!first) {
                oss << "; ";
            }
            oss << key << "=" << value;
            first = false;
        }
        request["cookies"] = oss.str();
    }
};