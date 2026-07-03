#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CookiesUtil {
public:
    std::string cookies_file;
    json cookies;

    CookiesUtil(const std::string& cookies_file)
        : cookies_file(cookies_file), cookies(nullptr) {}

    void get_cookies(const json& reponse) {
        cookies = reponse.at("cookies");
        _save_cookies();
    }

    json load_cookies() {
        std::ifstream file(cookies_file);
        if (!file.is_open()) {
            return json::object();
        }
        return json::parse(file);
    }

    bool _save_cookies() {
        try {
            std::ofstream file(cookies_file);
            if (!file.is_open()) {
                return false;
            }
            file << cookies.dump();
            return true;
        } catch (...) {
            return false;
        }
    }

    void set_cookies(json& request) {
        std::string cookie_str;
        for (auto it = cookies.begin(); it != cookies.end(); ++it) {
            if (!cookie_str.empty()) {
                cookie_str += "; ";
            }
            cookie_str += it.key() + "=" + it.value().get<std::string>();
        }
        request["cookies"] = cookie_str;
    }
};