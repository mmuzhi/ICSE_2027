#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using json = nlohmann::json;

class CookiesUtil {
public:
    std::string cookies_file;
    json cookies;

    CookiesUtil(const std::string& file) : cookies_file(file), cookies(nullptr) {}

    void get_cookies(const json& reponse) {
        cookies = reponse["cookies"];
        _save_cookies();
    }

    json load_cookies() const {
        std::ifstream file(cookies_file);
        if (file.is_open()) {
            try {
                return json::parse(file);
            } catch (...) {
                throw;
            }
        }
        return json::object();
    }

    void set_cookies(json& request) {
        if (!cookies.is_object()) {
            throw std::runtime_error("cookies must be an object");
        }
        std::string cookie_str;
        for (auto& el : cookies.items()) {
            if (!cookie_str.empty()) {
                cookie_str += "; ";
            }
            std::string value_str;
            if (el.value().is_string()) {
                value_str = el.value().get<std::string>();
            } else if (el.value().is_boolean()) {
                value_str = el.value().get<bool>() ? "True" : "False";
            } else if (el.value().is_null()) {
                value_str = "None";
            } else {
                value_str = el.value().dump(-1);
            }
            cookie_str += el.key() + "=" + value_str;
        }
        request["cookies"] = cookie_str;
    }

private:
    bool _save_cookies() {
        try {
            std::ofstream file(cookies_file);
            if (!file.is_open()) {
                return false;
            }
            file << cookies.dump(-1);
            return true;
        } catch (...) {
            return false;
        }
    }
};