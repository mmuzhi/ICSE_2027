#include <fstream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CookiesUtil {
private:
    std::string cookiesFile;
    std::optional<std::unordered_map<std::string, std::string>> cookies;

    bool _save_cookies() {
        json j;
        if (cookies) {
            j = *cookies;
        }

        try {
            std::ofstream file(cookiesFile);
            if (!file) {
                return false;
            }
            file << j.dump();
            return true;
        } catch (...) {
            return false;
        }
    }

public:
    CookiesUtil(const std::string& cookiesFile) : cookiesFile(cookiesFile), cookies(std::nullopt) {}

    template <typename OuterMap>
    void get_cookies(const OuterMap& response) {
        auto it = response.find("cookies");
        if (it != response.end()) {
            const auto& innerMap = it->second;
            std::unordered_map<std::string, std::string> tempMap;
            for (const auto& [key, value] : innerMap) {
                tempMap[key] = value;
            }
            cookies = std::move(tempMap);
        } else {
            cookies = std::nullopt;
        }
        _save_cookies();
    }

    std::unordered_map<std::string, std::string> loadCookies() {
        try {
            std::ifstream in(cookiesFile);
            if (!in) {
                return {};
            }
            json j = json::parse(in);
            try {
                return j.get<std::unordered_map<std::string, std::string>>();
            } catch (const json::type_error&) {
                return {};
            }
        } catch (const json::parse_error&) {
            return {};
        } catch (const std::exception&) {
            return {};
        }
    }

    template <typename RequestMap>
    void set_cookies(RequestMap& request) {
        std::ostringstream oss;
        if (cookies) {
            bool first = true;
            for (const auto& [key, value] : *cookies) {
                if (!first) {
                    oss << "; ";
                } else {
                    first = false;
                }
                oss << key << "=" << value;
            }
        }
        request["cookies"] = oss.str();
    }
};